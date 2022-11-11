#pragma once
#include "PhysXCCTActorComponent.h"

// Ό³Έν :
class PlayerActor : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerActor();
	~PlayerActor();

	// delete Function
	PlayerActor(const PlayerActor& _Other) = delete;
	PlayerActor(PlayerActor&& _Other) noexcept = delete;
	PlayerActor& operator=(const PlayerActor& _Other) = delete;
	PlayerActor& operator=(PlayerActor&& _Other) noexcept = delete;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxControllerManager* _CtrManager);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelStartEvent() override;

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> FbxRenderer_;
	std::shared_ptr<PhysXCCTActorComponent> CCTActorComponent_;

};

