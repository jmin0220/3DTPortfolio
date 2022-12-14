#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXTriMeshGeometryComponent.h"

// ???? :
class DoorDashStage	: public VirtualPhysXActor
{
public:
	// constrcuter destructer
	DoorDashStage();
	~DoorDashStage();

	// delete Function
	DoorDashStage(const DoorDashStage& _Other) = delete;
	DoorDashStage(DoorDashStage&& _Other) noexcept = delete;
	DoorDashStage& operator=(const DoorDashStage& _Other) = delete;
	DoorDashStage& operator=(DoorDashStage&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) override;
private:
	std::shared_ptr<PhysXTriMeshGeometryComponent> WallPhysXTriMeshGeometry_;
	std::shared_ptr<PhysXTriMeshGeometryComponent> PlatformPhysXTriMeshGeometry_;
	std::shared_ptr<PhysXTriMeshGeometryComponent> BlocksPhysXTriMeshGeometry_;

	std::shared_ptr<GameEngineFBXStaticRenderer> WallRenderer_;
	std::shared_ptr<GameEngineFBXStaticRenderer> PlatformRenderer_;
	std::shared_ptr<GameEngineFBXStaticRenderer> BlocksRenderer_;

	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
};

