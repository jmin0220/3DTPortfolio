#pragma once
#include "StageParentLevel.h"

// Ό³Έν :
class BigShotsLevel : public StageParentLevel
{
public:
	// constrcuter destructer
	BigShotsLevel();
	~BigShotsLevel();

	// delete Function
	BigShotsLevel(const BigShotsLevel& _Other) = delete;
	BigShotsLevel(BigShotsLevel&& _Other) noexcept = delete;
	BigShotsLevel& operator=(const BigShotsLevel& _Other) = delete;
	BigShotsLevel& operator=(BigShotsLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	std::shared_ptr<GameEngineActor> BackGroundObj_;;
	std::shared_ptr<GameEngineActor> VFXWaterObj_;;
	std::shared_ptr<PlayerActor> Player_;

};

