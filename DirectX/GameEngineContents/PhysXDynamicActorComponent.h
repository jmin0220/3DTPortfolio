#pragma once

// ���� :
class PhysXDynamicActorComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	PhysXDynamicActorComponent();
	~PhysXDynamicActorComponent();

	// delete Function
	PhysXDynamicActorComponent(const PhysXDynamicActorComponent& _Other) = delete;
	PhysXDynamicActorComponent(PhysXDynamicActorComponent&& _Other) noexcept = delete;
	PhysXDynamicActorComponent& operator=(const PhysXDynamicActorComponent& _Other) = delete;
	PhysXDynamicActorComponent& operator=(PhysXDynamicActorComponent&& _Other) noexcept = delete;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f), float4 _GeoMetryRot = { 0.0f });

	void SetMoveSpeed(float4 _MoveSpeed);

	void SetMoveJump();

	// RigidDynamic�� CCT���� �����ϴ� �Լ�
	void SetDynamicIdle();

	inline physx::PxVec3 GetLinearVelocity()
	{
		return dynamic_->getLinearVelocity();
	}

	inline void SetlockAxis()
	{
		dynamic_->setRigidDynamicLockFlags(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);
	}

	inline void SetUnlockAxis()
	{
		// ������ ���� ����
		dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, false);
		dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, false);

		dynamic_->addForce(physx::PxVec3(0.0f, 0.01f, 0.0f), physx::PxForceMode::eIMPULSE);
	}

	void PushImpulse(float4 _ImpulsePower);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}

private:
	// Phys���� ������ �ʿ��� ����
	physx::PxScene* Scene_;
	physx::PxPhysics* physics_;
	physx::PxControllerManager* CtrManager_;

	physx::PxMaterial* material_;
	physx::PxShape* shape_;
	physx::PxRigidDynamic* dynamic_;

	// �� ������Ʈ�� ������ �ִ� Parent�� ���� ����
	std::weak_ptr<GameEngineActor> ParentActor_;

	physx::PxVec3 GeoMetryScale_;
};

