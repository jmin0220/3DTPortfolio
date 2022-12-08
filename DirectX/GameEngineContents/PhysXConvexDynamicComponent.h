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

	void AddForce(float4 _Force);
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
};

