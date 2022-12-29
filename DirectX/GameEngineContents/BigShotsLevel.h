#pragma once
#include "StageParentLevel.h"

// 설명 :
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

	// 게임 종료조건
	bool GameEndingFlag() override;
private:
	std::shared_ptr<GameEngineActor> BackGroundObj_;;
	std::shared_ptr<GameEngineActor> VFXWaterObj_;;
	std::shared_ptr<GameEngineActor> Stage_;

	// 서버
private:
	std::vector<std::shared_ptr<class BigShots_Cannon>> Cannons_;
	float SumShootingTime_;
	bool ServerActivated_;
};

