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

	// �θ� ���ͷκ��� ��ġ ����
	physx::PxTransform localTm(physx::PxVec3(ParentActor_.lock()->GetTransform().GetWorldPosition().x
		, ParentActor_.lock()->GetTransform().GetWorldPosition().y
		, ParentActor_.lock()->GetTransform().GetWorldPosition().z),
		physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w));

	// ����, ź�����
	material_ = _physics->createMaterial(0.6f, 0.6f, 0.0f);

	// TODO::������ ������ ��� ���� �ڵ带 ���
	//float4 tmpMagnification = { SIZE_MAGNIFICATION_RATIO };
	//physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * tmpMagnification.x * 0.5f, 
	//							   _GeoMetryScale.y * tmpMagnification.y * 0.5f, 
	//							   _GeoMetryScale.z * tmpMagnification.z * 0.5f);

	GeoMetryScale_ = _GeoMetryScale;

	physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * 0.5f,
		_GeoMetryScale.y * 0.5f,
		_GeoMetryScale.z * 0.5f);

	//// �浹ü�� ����
	dynamic_ = _physics->createRigidDynamic(localTm);

	// TODO::�����ӷ¿� ������ ��ħ. �������� �ۼ��� �ڼ��� ��ġ�� ���߿� ����
	// �÷��̾� �ִ� �ӷ�
	// dynamic_->setMaxLinearVelocity(PLAYER_MAX_SPEED);

	dynamic_->setRigidDynamicLockFlags(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

	// �浹ü�� ����
	// �浹ü�� ũ��� ������ ũ�⸦ �����ϹǷ� ���� Renderer�� �������� �浹ü�� 2��� �����Ǿ�� ��
	// TODO::�θ� ������ RenderUnit���κ��� Mesh�� Scale �� WorldScale�� ������ ����� ������Ʈ���� Scale�� �����ؾ���.
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.z * 0.5f * 0.25f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.z * 0.5f * 0.25f, 0)));
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.z * 0.5f * 0.25f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.z * 0.5f * 0.75f, 0)));
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.z * 0.5f * 0.25f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.z * 0.5f * 1.25f, 0)));
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.z * 0.5f * 0.25f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.z * 0.5f * 1.75f, 0)));

	// Note. �� Shape�� ũ��, updateMassAndInertia�� ������ ������Ʈ�ϴ� ������ ��� Shape�� ��ü �����߽ɿ� �� ����� ������.
	// ����, �ʿ信 ���� ���� ũ�⸦ �����ϰ�, ������ ������Ʈ�ؼ� �����߽��� �����ؾ���.
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(.2f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, -.1f, 0)));

	// RigidDynamic�� �е��� ����
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
	// �浹���� �ݹ��� ���� ����
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


	
	//// Note. �� Shape�� ũ��, updateMassAndInertia�� ������ ������Ʈ�ϴ� ������ ��� Shape�� ��ü �����߽ɿ� �� ����� ������.
	//// ����, �ʿ信 ���� ���� ũ�⸦ �����ϰ�, ������ ������Ʈ�ؼ� �����߽��� �����ؾ���.
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(.5f), *material_);
	////shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, -.29, 0)));

	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(.4f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, .6f, 0)));
	//shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(.3f), *material_);
	//shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, 1.1f, 0)));

	//// RigidDynamic�� �е��� ����
	//const physx::PxVec3 localPos = physx::PxVec3(0, -.5, 0);
	//physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 500.0f, &localPos);

	// ����?
	dynamic_->setLinearDamping(physx::PxReal(1.f));

	// Scene�� ���� �߰�
	_Scene->addActor(*dynamic_);
	
	// TODO::virtualPhysXLevel���� Callback �Լ��� ȣ���ϱ� ���� Dynamic ����
	return dynamic_;
}

void PhysXDynamicActorComponent::SetMoveSpeed(float4 _MoveSpeed)
{
	// RigidDynamic�� ���� �����ϴ� Flag -> ĳ���Ͱ� �������� �ʰ� ������ �� �ֵ���
	// ���𰡿� �浹�ؼ� �������� �Ұ�쿡�� setRigidDynamicLockFlag({flag}, false)�� flag�� �����ؾ���.
	dynamic_->setRigidDynamicLockFlags(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y | 
		physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

	// ĳ������ ������ ������ ����
	dynamic_->addForce(physx::PxVec3(_MoveSpeed.x, _MoveSpeed.y, _MoveSpeed.z), physx::PxForceMode::eFORCE);


#pragma region Unused
	// �ӵ�üũ�� ����� �ڵ�
	//std::string tmp = "x >> " + std::to_string(dynamic_->getLinearVelocity().x) + " y >> " + std::to_string(dynamic_->getLinearVelocity().y) + " z >> " + std::to_string(dynamic_->getLinearVelocity().z);
	//GameEngineDebug::OutPutString(tmp);


	// SetLinearVelocity�� ������ ���� �����ϴ� �����̹Ƿ�, �߷�, �浹���� ������ ������
	//dynamic_->setLinearVelocity(physx::PxVec3(_MoveSpeed.x, _MoveSpeed.y, _MoveSpeed.z));


	// Kinematic�ɼ��� ����� �ڵ�####################
	//physx::PxVec3 DynamicVec3(dynamic_->getGlobalPose().p);
	//physx::PxVec3 MoveSpeedVec3(_MoveSpeed.x, _MoveSpeed.y, _MoveSpeed.z);
	//physx::PxVec3 ResultVec3(DynamicVec3 + MoveSpeedVec3 + Scene_->getGravity() * GameEngineTime::GetDeltaTime());
	
	// Kinematic ���¿����� �߷��� ������ ���� �����Ƿ� ������ �߷��� �־������
	//_MoveSpeed.y += PHYSX_GRAVITY * (1.0f / 60.0f);

	// Kinematic Flag On
	//dynamic_->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, true);
	
	// static�� Kinematic�� ��ȣ�ۿ� �ϴ� �÷��� (�������� ����, FileterPair�� �����ؾ� �ϴµ�?)
	//dynamic_->setRigidBodyFlag(physx::PxRigidBodyFlag::eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES, true);
	//dynamic_->setRigidBodyFlag(physx::PxRigidBodyFlag::eFORCE_STATIC_KINE_NOTIFICATIONS, true);

	// Kinematic ������ �� RigidDynamic�� �����̰� ����� �ڵ�
	// Static�� ��ȣ�ۿ����� �ʴ� ������ ����.
	//dynamic_->setKinematicTarget(physx::PxTransform(physx::PxVec3(ResultVec3)));
	// Kinematic�ɼ��� ����� �ڵ� ��####################
#pragma endregion


}

void PhysXDynamicActorComponent::SetMoveJump()
{
	dynamic_->addForce(physx::PxVec3(0.0f, 10.0f, 0.0f), physx::PxForceMode::eIMPULSE);
}

void PhysXDynamicActorComponent::SetDynamicIdle()
{
	// ������ ���� ����
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, false);
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, false);
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, false);
	


	// Kinematic�� ������� ���, RigidDynamic���� ���ư� �� �ֵ��� Flag����
	//dynamic_->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, false);
}

void PhysXDynamicActorComponent::Start()
{
	// �θ��� ������ ����
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetParent());
}

void PhysXDynamicActorComponent::Update(float _DeltaTime)
{
	// PhysX Actor�� ���¿� ���缭 �θ��� Transform������ ����
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
	// ������ ���� ����
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, false);
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, false);

	dynamic_->addForce(physx::PxVec3(_ImpulsePower.x, _ImpulsePower.y, _ImpulsePower.z), physx::PxForceMode::eIMPULSE);
}

void PhysXDynamicActorComponent::SetPlayerStartPos(float4 _Pos)
{
	physx::PxTransform tmpPxTransform(_Pos.x, _Pos.y, _Pos.z);

	// �θ��� Transform������ �������� PhysX Actor�� Ʈ�������� ����
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