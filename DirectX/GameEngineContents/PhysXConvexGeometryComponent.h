#pragma once
#include <GameEngineCore/GameEngineComponent.h>
#include <PhysX/foundation/PxVec3.h>


// ���� :
class PhysXConvexGeometryComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	PhysXConvexGeometryComponent();
	~PhysXConvexGeometryComponent();

	// delete Function
	PhysXConvexGeometryComponent(const PhysXConvexGeometryComponent& _Other) = delete;
	PhysXConvexGeometryComponent(PhysXConvexGeometryComponent&& _Other) noexcept = delete;
	PhysXConvexGeometryComponent& operator=(const PhysXConvexGeometryComponent& _Other) = delete;
	PhysXConvexGeometryComponent& operator=(PhysXConvexGeometryComponent&& _Other) noexcept = delete;

	void CreatePhysXActors(const std::string& _MeshName, physx::PxScene* _Scene, physx::PxPhysics* _physics, 
		physx::PxCooking* _cooking, physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f), float4 _GeoMetryRot = {0.0f});

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
	void CustomFBXLoad(const std::string& _MeshName);

private:
	// Phys���� ������ �ʿ��� ����
	physx::PxPhysics* physics_;
	physx::PxScene* scene_;

	physx::PxMaterial* material_;
	physx::PxShape* shape_;
	physx::PxRigidDynamic* dynamic_;
	physx::PxRigidStatic* rigidStatic_;

	std::vector<physx::PxVec3> VertexVec;
	physx::PxConvexMesh* convexMesh;
	std::shared_ptr<GameEngineFBXMesh> Mesh;

	// �� ������Ʈ�� ������ �ִ� Parent�� ���� ����
	std::weak_ptr<GameEngineActor> ParentActor_;

};

