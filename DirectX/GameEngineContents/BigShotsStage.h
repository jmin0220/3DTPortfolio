#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXTriMeshGeometryComponent.h"
#include "PhysXConvexSeesawComponent.h"

// Ό³Έν :
class BigShotsStage : public VirtualPhysXActor
{
public:
	// constrcuter destructer
	BigShotsStage();
	~BigShotsStage();

	// delete Function
	BigShotsStage(const BigShotsStage& _Other) = delete;
	BigShotsStage(BigShotsStage&& _Other) noexcept = delete;
	BigShotsStage& operator=(const BigShotsStage& _Other) = delete;
	BigShotsStage& operator=(BigShotsStage&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) override;

private:
	std::shared_ptr<PhysXTriMeshGeometryComponent> PhysXSeesawGeometry_;

	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
};

