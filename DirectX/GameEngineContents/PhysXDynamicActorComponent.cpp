#include "PreCompile.h"
#include "PhysXDynamicActorComponent.h"

PhysXDynamicActorComponent::PhysXDynamicActorComponent() 
{
}

PhysXDynamicActorComponent::~PhysXDynamicActorComponent() 
{
}

physx::PxRigidDynamic* PhysXDynamicActorComponent::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot)
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

	// TODO::점프속력에 영향을 미침. 스테이지 작성후 자세한 수치는 나중에 조절
	// 플레이어 최대 속력
	// dynamic_->setMaxLinearVelocity(PLAYER_MAX_SPEED);

	dynamic_->setRigidDynamicLockFlags(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

	// 충돌체의 형태
	// 충돌체의 크기는 절반의 크기를 설정하므로 실제 Renderer의 스케일은 충돌체의 2배로 설정되어야 함
	// TODO::부모 액터의 RenderUnit으로부터 Mesh의 Scale 과 WorldScale의 연산의 결과를 지오메트리의 Scale로 세팅해야함.
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.z * 0.5f * 0.25f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.z * 0.5f * 0.25f, 0)));
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.z * 0.5f * 0.25f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.z * 0.5f * 0.75f, 0)));
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.z * 0.5f * 0.25f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.z * 0.5f * 1.25f, 0)));
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.z * 0.5f * 0.25f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.z * 0.5f * 1.75f, 0)));

	// Note. 각 Shape의 크기, updateMassAndInertia로 질량을 업데이트하는 순간이 모두 Shape의 전체 무게중심에 그 결과에 관여함.
	// 따라서, 필요에 따라 구의 크기를 조절하고, 질량을 업데이트해서 무게중심을 조절해야함.
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(.2f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, -.1f, 0)));

	// RigidDynamic의 밀도를 설정
	physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 1000.0f);

	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(.5f), *material_);

	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.x * 0.5f * 0.75f, 0)));
	/*shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(.4f), *material_);
	shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, .6, 0)));
	shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(.3f), *material_);
	shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, 1.1, 0)));*/
	float ScaledRadius = _GeoMetryScale.z;
	float ScaledHeight = _GeoMetryScale.y;
	
	shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxCapsuleGeometry(ScaledRadius * 1.3f, ScaledHeight * 0.9f), *material_);
	// 충돌시점 콜백을 위한 세팅
	shape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::Player)
		, static_cast<physx::PxU32>(PhysXFilterGroup::Ground), 0, 0));

	physx::PxTransform relativePose(physx::PxVec3(0.0f, +ScaledHeight * 0.9f + ScaledRadius * 1.3f, 0.0f), physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)));
	shape_->setLocalPose(relativePose);
	// 
	physx::PxTransform LocalPose = dynamic_->getCMassLocalPose();
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.z * 0.5f * 0.25f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.z * 0.5f * 1.75f, 0)));
	_GeoMetryScale;
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(.5f), *material_);
	////shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.x * 0.5f * 0.75f, 0)));
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(.4f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, .6, 0)));
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(.3f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, 1.1, 0)));


	
	//// Note. 각 Shape의 크기, updateMassAndInertia로 질량을 업데이트하는 순간이 모두 Shape의 전체 무게중심에 그 결과에 관여함.
	//// 따라서, 필요에 따라 구의 크기를 조절하고, 질량을 업데이트해서 무게중심을 조절해야함.
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(.5f), *material_);
	////shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, -.29, 0)));

	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(.4f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, .6f, 0)));
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(.3f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, 1.1f, 0)));

	//// RigidDynamic의 밀도를 설정
	//const physx::PxVec3 localPos = physx::PxVec3(0, -.5, 0);
	//physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 500.0f, &localPos);

	// 제동?
	dynamic_->setLinearDamping(physx::PxReal(1.f));

	// Scene에 액터 추가
	_Scene->addActor(*dynamic_);
	
	// TODO::virtualPhysXLevel에서 Callback 함수에 호출하기 위한 Dynamic 리턴
	return dynamic_;
}

void PhysXDynamicActorComponent::SetMoveSpeed(float4 _MoveSpeed)
{
	// RigidDynamic의 축을 고정하는 Flag -> 캐릭터가 쓰러지지 않고 서있을 수 있도록
	// 무언가와 충돌해서 쓰러져야 할경우에는 setRigidDynamicLockFlag({flag}, false)로 flag를 해제해야함.
	dynamic_->setRigidDynamicLockFlags(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y | 
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

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
	dynamic_->addForce(physx::PxVec3(0.0f, 10.0f, 0.0f), physx::PxForceMode::eIMPULSE);
}

void PhysXDynamicActorComponent::SetDynamicIdle()
{
	// 고정된 축을 해제
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, false);
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, false);
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

	//float4 tmpWorldRot = { dynamic_->getGlobalPose().q.x
	//,dynamic_->getGlobalPose().q.y
	//, dynamic_->getGlobalPose().q.z };

	float4 tmpWorldRot = { ToEulerAngles(dynamic_->getGlobalPose().q)};
	tmpWorldRot = tmpWorldRot * GameEngineMath::RadianToDegree;
	ParentActor_.lock()->GetTransform().SetWorldPosition(tmpWorldPos);
	ParentActor_.lock()->GetTransform().SetWorldRotation(tmpWorldRot);


}

void PhysXDynamicActorComponent::PushImpulse(float4 _ImpulsePower)
{
	// 고정된 축을 해제
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, false);
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, false);

	dynamic_->addForce(physx::PxVec3(_ImpulsePower.x, _ImpulsePower.y, _ImpulsePower.z), physx::PxForceMode::eIMPULSE);
}

void PhysXDynamicActorComponent::SetPlayerStartPos(float4 _Pos)
{
	physx::PxTransform tmpPxTransform(_Pos.x, _Pos.y, _Pos.z);

	// 부모의 Transform정보를 바탕으로 PhysX Actor의 트랜스폼을 갱신
	dynamic_->setGlobalPose(tmpPxTransform);
}

bool PhysXDynamicActorComponent::PlayerStandUp()
{
	return false;
}


float4 PhysXDynamicActorComponent::ToEulerAngles(const physx::PxQuat& q) {
	float4 angles;    //yaw pitch roll
	const float x = q.x;
	const float y = q.y;
	const float z = q.z;
	const float w = q.w;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (w * x + y * z);
	double cosr_cosp = 1 - 2 * (x * x + y * y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = 2 * (w * y - z * x);
	if (std::abs(sinp) >= 1)
	{
		angles.y = std::copysign(GameEngineMath::PI / 4, sinp); // use 90 degrees if out of range
	}

	else
	{
		angles.y = std::asin(sinp);
	}

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (w * z + x * y);
	double cosy_cosp = 1 - 2 * (y * y + z * z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);
	return angles;
}