#pragma once

// 설명 :
class PhysXSpinBarComponent : public GameEngineComponent, public PhysXCommonFunc
{
public:
	// constrcuter destructer
	PhysXSpinBarComponent();
	~PhysXSpinBarComponent();

	// delete Function
	PhysXSpinBarComponent(const PhysXSpinBarComponent& _Other) = delete;
	PhysXSpinBarComponent(PhysXSpinBarComponent&& _Other) noexcept = delete;
	PhysXSpinBarComponent& operator=(const PhysXSpinBarComponent& _Other) = delete;
	PhysXSpinBarComponent& operator=(PhysXSpinBarComponent&& _Other) noexcept = delete;

	void CreatePhysXActors(const std::string& _MeshName, physx::PxScene* _Scene, physx::PxPhysics* _physics,
		physx::PxCooking* _cooking, bool _InverseIndex = true, physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f), float4 _GeoMetryRot = { 0.0f });

	inline void SetSpinSpeedRot(float _SpinSpeed)
	{
		SpinSpeed_ = _SpinSpeed;
	}

	// 서버
	inline void SetCurRot(float _Rot)
	{
		CurRot_ = _Rot;
	}

	inline float GetCurRot()
	{
		return CurRot_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void CustomFBXLoad(const std::string& _MeshName, bool _InverseIndex);

private:
	// Phys액터 생성에 필요한 정보
	physx::PxPhysics* physics_;
	physx::PxScene* scene_;

	physx::PxMaterial* material_;
	physx::PxShape* shape_;
	physx::PxRigidDynamic* dynamic_;

	std::vector<std::vector<physx::PxVec3>> VertexVec;
	std::vector<std::vector<physx::PxU32>> IndexVec;

	physx::PxConvexMesh* convexMesh;
	std::shared_ptr<GameEngineFBXMesh> Mesh;

	// 이 컴포넌트를 가지고 있는 Parent에 대한 정보
	std::weak_ptr<GameEngineActor> ParentActor_;

	float CurRot_;
	float SpinSpeed_;
};

