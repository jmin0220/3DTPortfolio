#pragma once

// ���� :
class PhysXDynamicActorComponent : public GameEngineComponent, public PhysXCommonFunc
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

	physx::PxRigidDynamic* CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f), float4 _GeoMetryRot = { 0.0f });

	void SetMoveSpeed(float4 _MoveSpeed);

	void SetMoveJump();
	void SetMoveDive(float _Rot);


	// RigidDynamic�� CCT���� �����ϴ� �Լ�
	void SetDynamicIdle();

	inline physx::PxVec3 GetLinearVelocity()
	{
		return dynamic_->getLinearVelocity();
	}

	inline void SetlockAxis()
	{
		dynamic_->setRigidDynamicLockFlags(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);
	}

	inline void SetUnlockAxis()
	{
		// ������ ���� ����
		dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, false);
		dynamic_->setRigidDynamicLockFlag(physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, false);

		dynamic_->addForce(physx::PxVec3(0.0f, 0.01f, 0.0f), physx::PxForceMode::eIMPULSE);
	}

	inline float4 GetWorldPosition()
	{
		return float4(dynamic_->getGlobalPose().p.x, dynamic_->getGlobalPose().p.y, dynamic_->getGlobalPose().p.z);
	}

	void SetPlayerStartPos(float4 _Pos);

	void PushImpulse(float4 _ImpulsePower);
	void PushImpulseAtLocalPos(float4 _ImpulsePower, float4 _Pos);
	
	bool PlayerStandUp(float _DeltaTime, bool _IsXAixisRotReady);
	bool StandUp2(float _DeltaTime, bool _IsXAixisRotReady);

	void TurnOffSpeedLimit()
	{
		IsSpeedLimit_ = false;
	}

	void TurnOnSpeedLimit()
	{
		IsSpeedLimit_ = true;
	}

	void SwitchSpeedLimit()
	{
		IsSpeedLimit_ = !IsSpeedLimit_;
	}

	float4 GetDynamicVelocity()
	{
		physx::PxVec3 Vec3 = dynamic_->getLinearVelocity();
		return float4{ Vec3.x, Vec3.y, Vec3.z };
	}

	//ȸ�� ������ �Լ�
	void SetChangedRot(float4 _Rot);

	//�߷²���
	void TurnOffGravity()
	{
		dynamic_->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);
	}

	//�߷�Ű��
	void TurnOnGravity()
	{
		dynamic_->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, false);
	}

	void LockAxis();

	inline void SetIsMain(bool _Flag)
	{
		IsMain_ = _Flag;
	}

	//�÷��̾� ���ߴ� �Լ�
	void FreezeDynamic();

	//�÷��̾� ���ߴ°� Ǫ�� �Լ�
	void WakeUpDynamic();

	//Reset �Լ�
	void ResetDynamic();

	//�Ͼ�� ��ǥ �������ϴ� �Լ�
	void InitializeStandUp2();

	void SetMainPlayerFlags()
	{
		shape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::PlayerDynamic),
			static_cast<physx::PxU32>(PhysXFilterGroup::Ground),
			static_cast<physx::PxU32>(PhysXFilterGroup::Obstacle), 0));
		Instshape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::Player), 0, 0, 0));
		faceshape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::PlayerFace), 0, 0, 0));
		headshape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::PlayerHead), 0, 0, 0));
	}
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
	physx::PxShape* Instshape_;
	physx::PxShape* faceshape_;
	physx::PxShape* headshape_;
	physx::PxShape* Flagshape_;
	physx::PxRigidDynamic* dynamic_;

	bool IsSpeedLimit_;

	// �� ������Ʈ�� ������ �ִ� Parent�� ���� ����
	std::weak_ptr<GameEngineActor> ParentActor_;

	physx::PxVec3 GeoMetryScale_;

	//�ӵ����� �Լ�
	void SpeedLimit();

	float StandUpTargetYAxisAngle_;
	float StandUpStartYAxisAngle_;
	float StandUpProgressYAxisAngle_;

	physx::PxVec3 InitVec3_;
	physx::PxVec3 TargetVec3_;
	physx::PxTransform RecentTransform_;

	// �����÷��̾� �÷���
	bool IsMain_;
};

