#pragma once
#include "PhysXCCTActorComponent.h"

// Ό³Έν :
class PhysXTestPlayer : public GameEngineActor
{
public:
	// constrcuter destructer
	PhysXTestPlayer();
	~PhysXTestPlayer();

	// delete Function
	PhysXTestPlayer(const PhysXTestPlayer& _Other) = delete;
	PhysXTestPlayer(PhysXTestPlayer&& _Other) noexcept = delete;
	PhysXTestPlayer& operator=(const PhysXTestPlayer& _Other) = delete;
	PhysXTestPlayer& operator=(PhysXTestPlayer&& _Other) noexcept = delete;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxControllerManager* _CtrManager);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelStartEvent() override;

private:
	GameEngineFBXStaticRenderer* FbxRenderer_;
	PhysXCCTActorComponent* CCTActorComponent_;
};

