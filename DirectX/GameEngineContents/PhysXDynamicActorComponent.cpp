#include "PreCompile.h"
#include "PhysXDynamicActorComponent.h"

PhysXDynamicActorComponent::PhysXDynamicActorComponent() 
{
}

PhysXDynamicActorComponent::~PhysXDynamicActorComponent() 
{
}

void PhysXDynamicActorComponent::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot)
{
	Scene_ = _Scene;
	physics_ = _physics;

	float4 tmpQuat = _GeoMetryRot.DegreeRotationToQuaternionReturn();

	// 부모 액터로부터 위치 생성
	physx::PxTransform localTm(physx::PxVec3(ParentActor_.lock()->GetTransform().GetWorldPosition().x
		, ParentActor_.lock()->GetTransform().GetWorldPosition().y
		, ParentActor_.lock()->GetTransform().GetWorldPosition().z),
		physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w));

	// 마찰, 탄성계수
	material_ = _physics->createMaterial(0.6f, 0.6f, 0.0f);

	// TODO::배율을 적용할 경우 이쪽 코드를 사용
	//float4 tmpMagnification = { SIZE_MAGNIFICATION_RATIO };
	//physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * tmpMagnification.x * 0.5f, 
	//							   _GeoMetryScale.y * tmpMagnification.y * 0.5f, 
	//							   _GeoMetryScale.z * tmpMagnification.z * 0.5f);

	GeoMetryScale_ = _GeoMetryScale;

	physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * 0.5f,
		_GeoMetryScale.y * 0.5f,
		_GeoMetryScale.z * 0.5f);

	//// 충돌체의 종류
	dynamic_ = _physics->createRigidDynamic(localTm);

	// 플레이어 최대 속력
	dynamic_->setMaxLinearVelocity(PLAYER_MAX_SPEED);

	// 충돌체의 형태
	// 충돌체의 크기는 절반의 크기를 설정하므로 실제 Renderer의 스케일은 충돌체의 2배로 설정되어야 함
	// TODO::부모 액터의 RenderUnit으로부터 Mesh의 Scale 과 WorldScale의 연산의 결과를 지오메트리의 Scale로 세팅해야함.
	shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.x * 0.5f * 0.25f), *material_);
	shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.x * 0.5f * 0.25f, 0)));
	shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.x * 0.5f * 0.25f), *material_);
	shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.x * 0.5f * 0.75f, 0)));
	shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.x * 0.5f * 0.25f), *material_);
	shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.x * 0.5f * 1.25f, 0)));
	shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.x * 0.5f * 0.25f), *material_);
	shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.x * 0.5f * 1.75f, 0)));

	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxBoxGeometry(physx::PxVec3(_GeoMetryScale.x * 0.5f * 0.25f)), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.x * 0.5f * 0.25f, 0)));
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxBoxGeometry(physx::PxVec3(_GeoMetryScale.x * 0.5f * 0.25f)), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.x * 0.5f * 0.75f, 0)));
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxBoxGeometry(physx::PxVec3(_GeoMetryScale.x * 0.5f * 0.25f)), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.x * 0.5f * 1.25f, 0)));
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxBoxGeometry(physx::PxVec3(_GeoMetryScale.x * 0.5f * 0.25f)), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.x * 0.5f * 1.75f, 0)));

	dynamic_->attachShape(*shape_);

	// RigidDynamic의 밀도를 설정
	physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 1000.0f);

	// Scene에 액터 추가
	_Scene->addActor(*dynamic_);
}

void PhysXDynamicActorComponent::SetMoveSpeed(float4 _MoveSpeed)
{
	// RigidDynamic의 축을 고정하는 Flag -> 캐릭터가 쓰러지지 않고 서있을 수 있도록
	// 무언가와 충돌해서 쓰러져야 할경우에는 setRigidDynamicLockFlag({flag}, false)로 flag를 해제해야함.
	dynamic_->setRigidDynamicLockFlags(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

	// 캐릭터의 방향을 힘으로 조절
	dynamic_->addForce(physx::PxVec3(_MoveSpeed.x, _MoveSpeed.y, _MoveSpeed.z), physx::PxForceMode::eFORCE);


#pragma region Unused
	// 속도체크용 디버깅 코드
	//std::string tmp = "x >> " + std::to_string(dynamic_->getLinearVelocity().x) + " y >> " + std::to_string(dynamic_->getLinearVelocity().y) + " z >> " + std::to_string(dynamic_->getLinearVelocity().z);
	//GameEngineDebug::OutPutString(tmp);


	// SetLinearVelocity는 강제로 힘을 조절하는 연산이므로, 중력, 충돌등의 영향을 무시함
	//dynamic_->setLinearVelocity(physx::PxVec3(_MoveSpeed.x, _MoveSpeed.y, _MoveSpeed.z));


	// Kinematic옵션을 사용한 코드####################
	//physx::PxVec3 DynamicVec3(dynamic_->getGlobalPose().p);
	//physx::PxVec3 MoveSpeedVec3(_MoveSpeed.x, _MoveSpeed.y, _MoveSpeed.z);
	//physx::PxVec3 ResultVec3(DynamicVec3 + MoveSpeedVec3 + Scene_->getGravity() * GameEngineTime::GetDeltaTime());
	
	// Kinematic 상태에서는 중력의 영향을 받지 않으므로 강제로 중력을 넣어줘야함
	//_MoveSpeed.y += PHYSX_GRAVITY * (1.0f / 60.0f);

	// Kinematic Flag On
	//dynamic_->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, true);
	
	// static과 Kinematic을 상호작용 하는 플래그 (동작하지 않음, FileterPair를 설정해야 하는듯?)
	//dynamic_->setRigidBodyFlag(physx::PxRigidBodyFlag::eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES, true);
	//dynamic_->setRigidBodyFlag(physx::PxRigidBodyFlag::eFORCE_STATIC_KINE_NOTIFICATIONS, true);

	// Kinematic 세팅이 된 RigidDynamic을 움직이게 만드는 코드
	// Static과 상호작용하지 않는 문제가 있음.
	//dynamic_->setKinematicTarget(physx::PxTransform(physx::PxVec3(ResultVec3)));
	// Kinematic옵션을 사용한 코드 끝####################
#pragma endregion


}

void PhysXDynamicActorComponent::SetMoveJump()
{
	// 
	dynamic_->addForce(physx::PxVec3(0.0f, 50.0f, 0.0f), physx::PxForceMode::eIMPULSE);
}

void PhysXDynamicActorComponent::SetDynamicIdle()
{
	// 고정된 축을 해제
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, false);
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, false);
	


	// Kinematic을 사용했을 경우, RigidDynamic으로 돌아갈 수 있도록 Flag해제
	//dynamic_->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, false);
}

void PhysXDynamicActorComponent::Start()
{
	// 부모의 정보의 저장
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetParent());
}

void PhysXDynamicActorComponent::Update(float _DeltaTime)
{
	// PhysX Actor의 상태에 맞춰서 부모의 Transform정보를 갱신
	float4 tmpWorldPos = { dynamic_->getGlobalPose().p.x
	,dynamic_->getGlobalPose().p.y
	, dynamic_->getGlobalPose().p.z };

	float4 tmpWorldRot = { dynamic_->getGlobalPose().q.x
	,dynamic_->getGlobalPose().q.y
	, dynamic_->getGlobalPose().q.z };

	ParentActor_.lock()->GetTransform().SetWorldPosition(tmpWorldPos);
	ParentActor_.lock()->GetTransform().SetWorldRotation(tmpWorldRot);


}