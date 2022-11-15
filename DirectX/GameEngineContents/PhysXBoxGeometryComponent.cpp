#include "PreCompile.h"
#include "PhysXBoxGeometryComponent.h"

PhysXBoxGeometryComponent::PhysXBoxGeometryComponent() 
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
	material_ = _physics->createMaterial(0.5f, 0.5f, 0.6f);

	// TODO::배율을 적용할 경우 이쪽 코드를 사용
	//float4 tmpMagnification = { SIZE_MAGNIFICATION_RATIO };
	//physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * tmpMagnification.x * 0.5f, 
	//							   _GeoMetryScale.y * tmpMagnification.y * 0.5f, 
	//							   _GeoMetryScale.z * tmpMagnification.z * 0.5f);

	physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * 0.5f,
								   _GeoMetryScale.y * 0.5f,
								   _GeoMetryScale.z * 0.5f);

	// 충돌체의 형태
	// 충돌체의 크기는 절반의 크기를 설정하므로 실제 Renderer의 스케일은 충돌체의 2배로 설정되어야 함
	// TODO::부모 액터의 RenderUnit으로부터 Mesh의 Scale 과 WorldScale의 연산의 결과를 지오메트리의 Scale로 세팅해야함.
	shape_ = _physics->createShape(physx::PxBoxGeometry(tmpGeoMetryScale), *material_);

	// 충돌체의 종류
	//dynamic_ = _physics->createRigidDynamic(localTm);
	//dynamic_->attachShape(*shape_);
	//// 중력이 적용되지 않도록
	//// TODO::RigidStatic으로 변경해야
	//dynamic_->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);

	//// RigidDynamic의 밀도를 설정
	//physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 10.0f);

	//// Scene에 액터 추가
	//_Scene->addActor(*dynamic_);

	// 충돌체의 종류
	rigidStatic_ = _physics->createRigidStatic(localTm);
	rigidStatic_->attachShape(*shape_);

	// Scene에 액터 추가
	_Scene->addActor(*rigidStatic_);
}

void PhysXBoxGeometryComponent::Start()
{
	// 부모의 정보의 저장
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetParent());
}

void PhysXBoxGeometryComponent::Update(float _DeltaTime)
{
	// TODO::static은 변경되지 않으니 Update할 필요가 없을지도
	// PhysX Actor의 상태에 맞춰서 부모의 Transform정보를 갱신
	float4 tmpWorldPos = { rigidStatic_->getGlobalPose().p.x
	, rigidStatic_->getGlobalPose().p.y
	, rigidStatic_->getGlobalPose().p.z };

	float4 tmpWorldRot = { rigidStatic_->getGlobalPose().q.x
	, rigidStatic_->getGlobalPose().q.y
	, rigidStatic_->getGlobalPose().q.z };

	ParentActor_.lock()->GetTransform().SetWorldPosition(tmpWorldPos);
	ParentActor_.lock()->GetTransform().SetWorldRotation(tmpWorldRot);
}
