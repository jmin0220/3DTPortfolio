#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXBoxGeometryComponent.h"
#include "PhysXConvexGeometryComponent.h"
#include "PhysXTriMeshGeometryComponent.h"

// 물리를 사용해야하는 Actor는 GameEngineActor대신
// VirtualPhysXHexgonTest를 상속
class PhysXHexgonTest : public VirtualPhysXActor
{
public:
	// constrcuter destructer
	PhysXHexgonTest();
	~PhysXHexgonTest();

	// delete Function
	PhysXHexgonTest(const PhysXHexgonTest& _Other) = delete;
	PhysXHexgonTest(PhysXHexgonTest&& _Other) noexcept = delete;
	PhysXHexgonTest& operator=(const PhysXHexgonTest& _Other) = delete;
	PhysXHexgonTest& operator=(PhysXHexgonTest&& _Other) noexcept = delete;

protected:
	void Start() override;

	void LevelStartEvent() override;

	// ★반드시 생성해야함★★★★★★★★★★
	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) override;

	void CreateHexaTileActor(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot);

private:
	std::shared_ptr<PhysXConvexGeometryComponent> PhysXHexTileGeometry_;
	//std::shared_ptr<PhysXTriMeshGeometryComponent> PhysXHexTileGeometry_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;

};

