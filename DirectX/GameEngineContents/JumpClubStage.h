#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXTriMeshGeometryComponent.h"

// Ό³Έν :
class JumpClubStage : public VirtualPhysXActor
{
public:
	// constrcuter destructer
	JumpClubStage();
	~JumpClubStage();

	// delete Function
	JumpClubStage(const JumpClubStage& _Other) = delete;
	JumpClubStage(JumpClubStage&& _Other) noexcept = delete;
	JumpClubStage& operator=(const JumpClubStage& _Other) = delete;
	JumpClubStage& operator=(JumpClubStage&& _Other) noexcept = delete;

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

