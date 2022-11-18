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

	// �÷��̾� �ִ� �ӷ�
	dynamic_->setMaxLinearVelocity(PLAYER_MAX_SPEED);

	// �浹ü�� ����
	// �浹ü�� ũ��� ������ ũ�⸦ �����ϹǷ� ���� Renderer�� �������� �浹ü�� 2��� �����Ǿ�� ��
	// TODO::�θ� ������ RenderUnit���κ��� Mesh�� Scale �� WorldScale�� ������ ����� ������Ʈ���� Scale�� �����ؾ���.
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

	// RigidDynamic�� �е��� ����
	physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 1000.0f);

	// Scene�� ���� �߰�
	_Scene->addActor(*dynamic_);
}

void PhysXDynamicActorComponent::SetMoveSpeed(float4 _MoveSpeed)
{
	// RigidDynamic�� ���� �����ϴ� Flag -> ĳ���Ͱ� �������� �ʰ� ������ �� �ֵ���
	// ���𰡿� �浹�ؼ� �������� �Ұ�쿡�� setRigidDynamicLockFlag({flag}, false)�� flag�� �����ؾ���.
	dynamic_->setRigidDynamicLockFlags(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

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
	// 
	dynamic_->addForce(physx::PxVec3(0.0f, 50.0f, 0.0f), physx::PxForceMode::eIMPULSE);
}

void PhysXDynamicActorComponent::SetDynamicIdle()
{
	// ������ ���� ����
	dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, false);
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

	float4 tmpWorldRot = { dynamic_->getGlobalPose().q.x
	,dynamic_->getGlobalPose().q.y
	, dynamic_->getGlobalPose().q.z };

	ParentActor_.lock()->GetTransform().SetWorldPosition(tmpWorldPos);
	ParentActor_.lock()->GetTransform().SetWorldRotation(tmpWorldRot);


}