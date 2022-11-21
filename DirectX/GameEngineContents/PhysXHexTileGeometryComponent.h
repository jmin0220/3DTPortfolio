#pragma once
#include <GameEngineCore/GameEngineComponent.h>
#include <PhysX/foundation/PxVec3.h>


// ���� :
class PhysXHexTileGeometryComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	PhysXHexTileGeometryComponent();
	~PhysXHexTileGeometryComponent();

	// delete Function
	PhysXHexTileGeometryComponent(const PhysXHexTileGeometryComponent& _Other) = delete;
	PhysXHexTileGeometryComponent(PhysXHexTileGeometryComponent&& _Other) noexcept = delete;
	PhysXHexTileGeometryComponent& operator=(const PhysXHexTileGeometryComponent& _Other) = delete;
	PhysXHexTileGeometryComponent& operator=(PhysXHexTileGeometryComponent&& _Other) noexcept = delete;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxCooking* _cooking, physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f), float4 _GeoMetryRot = {0.0f});

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	// Phys���� ������ �ʿ��� ����
	physx::PxPhysics* physics_;
	physx::PxScene* scene_;

	physx::PxMaterial* material_;
	physx::PxShape* shape_;
	physx::PxRigidDynamic* dynamic_;
	physx::PxRigidStatic* rigidStatic_;
	std::vector<physx::PxVec3> VertedxVec;
	physx::PxConvexMesh* convexMesh;
	GameEngineFBXMesh* Mesh;

	// �� ������Ʈ�� ������ �ִ� Parent�� ���� ����
	std::weak_ptr<GameEngineActor> ParentActor_;

};

