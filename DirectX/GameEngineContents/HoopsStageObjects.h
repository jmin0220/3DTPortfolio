#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXTriMeshGeometryComponent.h"

// ???? :
class HoopsStageObjects : public VirtualPhysXActor
{
public:
	// constrcuter destructer
	HoopsStageObjects();
	~HoopsStageObjects();

	// delete Function
	HoopsStageObjects(const HoopsStageObjects& _Other) = delete;
	HoopsStageObjects(HoopsStageObjects&& _Other) noexcept = delete;
	HoopsStageObjects& operator=(const HoopsStageObjects& _Other) = delete;
	HoopsStageObjects& operator=(HoopsStageObjects&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) override;
private:
	std::shared_ptr<PhysXTriMeshGeometryComponent> WallPhysXTriMeshGeometry_;
	std::shared_ptr<PhysXTriMeshGeometryComponent> FloorPhysXTriMeshGeometry_;
	std::shared_ptr<PhysXTriMeshGeometryComponent> PlatformPhysXTriMeshGeometry_;

	std::shared_ptr<GameEngineFBXStaticRenderer> WallRenderer_;
	std::shared_ptr<GameEngineFBXStaticRenderer> PlatformRenderer_;
	std::shared_ptr<GameEngineFBXStaticRenderer> FloorRenderer_;

	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;

};

