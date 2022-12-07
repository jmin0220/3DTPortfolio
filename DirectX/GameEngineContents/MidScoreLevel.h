#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 설명 : 중간 점검 점수 체크(커스텀)
class LobbyPlayer;
class FloorActor;
class GoalTipActor;
class MidScoreLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MidScoreLevel();
	~MidScoreLevel();

	// delete Function
	MidScoreLevel(const MidScoreLevel& _Other) = delete;
	MidScoreLevel(MidScoreLevel&& _Other) noexcept = delete;
	MidScoreLevel& operator=(const MidScoreLevel& _Other) = delete;
	MidScoreLevel& operator=(MidScoreLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:
	std::shared_ptr<LobbyPlayer> Player_;
	std::shared_ptr<FloorActor> Chair_;
	std::shared_ptr<GoalTipActor> Score_;
};

