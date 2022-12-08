#include "PreCompile.h"
#include "PhysXBoxGeometryComponent.h"

PhysXBoxGeometryComponent::PhysXBoxGeometryComponent() 
	: PositionSetFromParentFlag_(false)
{
}

PhysXBoxGeometryComponent::~PhysXBoxGeometryComponent() 
{
}

void PhysXBoxGeometryComponent::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot)
{
	float4 tmpQuat = _GeoMetryRot.DegreeRotationToQuaternionReturn();

	// 부모 액터로부터 위치 생성
	physx::PxTransform localTm(physx::PxVec3(ParentActor_.lock()->GetTransform().GetWorldPosition().x
		, ParentActor_.lock()->GetTransform().GetWorldPosition().y
		, ParentActor_.lock()->GetTransform().GetWorldPosition().z),
		physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w));

	// 마찰, 탄성계수
	material_ = _physics->createMaterial(staticfriction_, dynamicfriction_, resitution_);

	// TODO::배율을 적용할 경우 이쪽 코드를 사용
	//float4 tmpMagnification = { SIZE_MAGNIFICATION_RATIO };
	//physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * tmpMagnification.x * 0.5f, 
	//							   _GeoMetryScale.y * tmpMagnification.y * 0.5f, 
	//							   _GeoMetryScale.z * tmpMagnification.z * 0.5f);

	physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * 0.5f,
								   _GeoMetryScale.y * 0.5f,
								   _GeoMetryScale.z * 0.5f);

	// 충돌체의 종류
	rigidDynamic_ = _physics->createRigidDynamic(localTm);

	// 중력이 적용되지 않도록
	// TODO::RigidStatic으로 변경해야
	rigidDynamic_->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);

	rigidDynamic_->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, true);

	// 충돌체의 형태
	// 충돌체의 크기는 절반의 크기를 설정하므로 실제 Renderer의 스케일은 충돌체의 2배로 설정되어야 함
	// TODO::부모 액터의 RenderUnit으로부터 Mesh의 Scale 과 WorldScale의 연산의 결과를 지오메트리의 Scale로 세팅해야함.
	shape_ = physx::PxRigidActorExt::createExclusiveShape(*rigidDynamic_, physx::PxBoxGeometry(tmpGeoMetryScale), *material_);

	// RigidDynamic의 밀도를 설정
	physx::PxRigidBodyExt::updateMassAndInertia(*rigidDynamic_, 0.1f);

	// 충돌시점 콜백을 위한 세팅
	shape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::Obstacle)
		, static_cast<physx::PxU32>(PhysXFilterGroup::Player), 0, 0));

	// Scene에 액터 추가
	_Scene->addActor(*rigidDynamic_);

	//// 충돌체의 종류
	//rigidStatic_ = _physics->createRigidStatic(localTm);
	//rigidStatic_->attachShape(*shape_);

	//// Scene에 액터 추가
	//_Scene->addActor(*rigidStatic_);
}

void PhysXBoxGeometryComponent::Start()
{
	// 부모의 정보의 저장
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetRoot());
}

void PhysXBoxGeometryComponent::Update(float _DeltaTime)
{
	if (false == PositionSetFromParentFlag_)
	{
		// PhysX Actor의 상태에 맞춰서 부모의 Transform정보를 갱신
		float4 tmpWorldPos = { rigidDynamic_->getGlobalPose().p.x
		, rigidDynamic_->getGlobalPose().p.y
		, rigidDynamic_->getGlobalPose().p.z };

		float4 EulerRot = PhysXCommonFunc::GetQuaternionEulerAngles(rigidDynamic_->getGlobalPose().q) * GameEngineMath::RadianToDegree;

		ParentActor_.lock()->GetTransform().SetWorldRotation(float4{ EulerRot.x, EulerRot.y, EulerRot.z });
		ParentActor_.lock()->GetTransform().SetWorldPosition(tmpWorldPos);
	}
	else
	{
		float4 tmpQuat = ParentActor_.lock()->GetTransform().GetWorldRotation().DegreeRotationToQuaternionReturn();

		physx::PxTransform tmpPxTransform(ParentActor_.lock()->GetTransform().GetWorldPosition().x,
			ParentActor_.lock()->GetTransform().GetWorldPosition().y,
			ParentActor_.lock()->GetTransform().GetWorldPosition().z, physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w));

		// 부모의 Transform정보를 바탕으로 PhysX Actor의 트랜스폼을 갱신
		rigidDynamic_->setKinematicTarget(tmpPxTransform);
		// TODO::회전도 처리해야함. DegreeToQuat
	}
}
