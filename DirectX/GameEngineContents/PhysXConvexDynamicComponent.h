#pragma once

// 설명 :
class PhysXConvexDynamicComponent : public GameEngineComponent, public PhysXCommonFunc
{
public:
	// constrcuter destructer
	PhysXConvexDynamicComponent();
	~PhysXConvexDynamicComponent();

	// delete Function
	PhysXConvexDynamicComponent(const PhysXConvexDynamicComponent& _Other) = delete;
	PhysXConvexDynamicComponent(PhysXConvexDynamicComponent&& _Other) noexcept = delete;
	PhysXConvexDynamicComponent& operator=(const PhysXConvexDynamicComponent& _Other) = delete;
	PhysXConvexDynamicComponent& operator=(PhysXConvexDynamicComponent&& _Other) noexcept = delete;

	void CreatePhysXActors(const std::string& _MeshName, physx::PxScene* _Scene, physx::PxPhysics* _physics,
		physx::PxCooking* _cooking, bool _InverseIndex = true, physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f), float4 _GeoMetryRot = { 0.0f }, bool _Gravity = false);

	// 힘을 추가
	void AddForce(float4 _Force);

	void AddTorque(float4 _Torque);

	// 가속도를 추가
	void AddAngularVelocity(float4 _Velocity);

	// RigidBody->Actor || Actor->RigidBody 플래그
	inline void SetPositionSetFromParentFlag(bool _Flag)
	{
		PositionSetFromParentFlag_ = _Flag;
	}

	// RigidBody의 질량을 취득
	inline physx::PxReal GetMass()
	{
		return dynamic_->getMass();
	}

	inline void ReleaseRigidBody()
	{
		dynamic_->release();
		this->Death();
	}

	inline void SetUpdateForce(physx::PxVec3 _UpdateForce)
	{
		AddUpdateForce_ = _UpdateForce;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void CustomFBXLoad(const std::string& _MeshName);

private:
	// Phys액터 생성에 필요한 정보
	physx::PxPhysics* physics_;
	physx::PxScene* scene_;

	physx::PxMaterial* material_;
	physx::PxShape* shape_;
	physx::PxRigidDynamic* dynamic_;

	std::vector<physx::PxVec3> VertexVec;
	physx::PxConvexMesh* convexMesh;
	std::shared_ptr<GameEngineFBXMesh> Mesh;

	physx::PxVec3 SeesawPos_;

	// 이 컴포넌트를 가지고 있는 Parent에 대한 정보
	std::weak_ptr<GameEngineActor> ParentActor_;

	physx::PxVec3 AddUpdateForce_;

	bool PositionSetFromParentFlag_;
};

