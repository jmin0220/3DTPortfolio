#pragma once
#include "StageParentLevel.h"

// Ό³Έν :
class DoorDashStage;
class IntroduceGame;
class DoorDashLevel	:	public StageParentLevel
{
public:
	// constrcuter destructer
	DoorDashLevel();
	~DoorDashLevel();

	// delete Function
	DoorDashLevel(const DoorDashLevel& _Other) = delete;
	DoorDashLevel(DoorDashLevel&& _Other) noexcept = delete;
	DoorDashLevel& operator=(const DoorDashLevel& _Other) = delete;
	DoorDashLevel& operator=(DoorDashLevel&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:
	std::shared_ptr<GameEngineActor> Stage_;
	std::shared_ptr<GameEngineActor>BackGround_;

};

