#pragma once

// 설명 :
class PhysXTriMeshDynamicGeometryComponent : public GameEngineComponent, public PhysXCommonFunc
{
public:
	// constrcuter destructer
	PhysXTriMeshDynamicGeometryComponent();
	~PhysXTriMeshDynamicGeometryComponent();

	// delete Function
	PhysXTriMeshDynamicGeometryComponent(const PhysXTriMeshDynamicGeometryComponent& _Other) = delete;
	PhysXTriMeshDynamicGeometryComponent(PhysXTriMeshDynamicGeometryComponent&& _Other) noexcept = delete;
	PhysXTriMeshDynamicGeometryComponent& operator=(const PhysXTriMeshDynamicGeometryComponent& _Other) = delete;
	PhysXTriMeshDynamicGeometryComponent& operator=(PhysXTriMeshDynamicGeometryComponent&& _Other) noexcept = delete;

	void CreatePhysXActors(const std::string& _MeshName, physx::PxScene* _Scene, physx::PxPhysics* _physics,
		physx::PxCooking* _cooking, bool _InverseIndex = true, physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f), float4 _GeoMetryRot = { 0.0f });

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
};

