#pragma once
#include <GameEngineCore/GameEngineComponent.h>
#include <PhysX/foundation/PxVec3.h>


// 설명 :
class PhysXTriMeshGeometryComponent : public GameEngineComponent, public PhysXCommonFunc
{
public:
	// constrcuter destructer
	PhysXTriMeshGeometryComponent();
	~PhysXTriMeshGeometryComponent();

	// delete Function
	PhysXTriMeshGeometryComponent(const PhysXTriMeshGeometryComponent& _Other) = delete;
	PhysXTriMeshGeometryComponent(PhysXTriMeshGeometryComponent&& _Other) noexcept = delete;
	PhysXTriMeshGeometryComponent& operator=(const PhysXTriMeshGeometryComponent& _Other) = delete;
	PhysXTriMeshGeometryComponent& operator=(PhysXTriMeshGeometryComponent&& _Other) noexcept = delete;

	void CreatePhysXActors(const std::string& _MeshName, physx::PxScene* _Scene, physx::PxPhysics* _physics, 
		physx::PxCooking* _cooking, bool _InverseIndex = true, physx::PxVec3 _GeoMetryScale = physx::PxVec3(2.0f), float4 _GeoMetryRot = {0.0f});

	inline void ReleasePhysX()
	{
		if (true == rigidStatic_->isReleasable())
		{
			rigidStatic_->release();
			ParentActor_.lock()->Death();
		}
	}

	inline void SetPositionSetFromParentFlag(bool _Flag)
	{
		PositionSetFromParentFlag_ = _Flag;
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
	physx::PxShape* triggershape_;
	physx::PxRigidStatic* rigidStatic_;

	std::vector<std::vector<physx::PxVec3>> VertexVec;
	std::vector<std::vector<physx::PxU32>> IndexVec;

	physx::PxConvexMesh* convexMesh;
	std::shared_ptr<GameEngineFBXMesh> Mesh;

	// 이 컴포넌트를 가지고 있는 Parent에 대한 정보
	std::weak_ptr<GameEngineActor> ParentActor_;

	bool PositionSetFromParentFlag_;
};

