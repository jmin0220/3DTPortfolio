#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXTriMeshGeometryComponent.h"

// Ό³Έν :
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
	std::shared_ptr<PhysXTriMeshGeometryComponent> PhysXTriMeshGeometry_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
};

