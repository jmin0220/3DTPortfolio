#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 인게임에 들어가는 UI들 뭉텅이
class CountDown;
class GameFail;
class GameSuccess;
class GoalTipActor;
class RoundEnd;
class StartGameTitleActor;
class SuccessCount;
class InGameSetUI : public GameEngineActor
{
public:
	void CountdownStart();

public:
	// constrcuter destructer
	InGameSetUI();
	~InGameSetUI();

	// delete Function
	InGameSetUI(const InGameSetUI& _Other) = delete;
	InGameSetUI(InGameSetUI&& _Other) noexcept = delete;
	InGameSetUI& operator=(const InGameSetUI& _Other) = delete;
	InGameSetUI& operator=(InGameSetUI&& _Other) noexcept = delete;

	std::shared_ptr<CountDown> GetCountDown()
	{
		return CountDown_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:
	std::shared_ptr<CountDown> CountDown_;
	std::shared_ptr<GameFail> GameFail_;
	std::shared_ptr<GameSuccess> GameSuccess_;
	std::shared_ptr<GoalTipActor> GoalTipActor_;
	std::shared_ptr<RoundEnd> RoundEnd_;
	std::shared_ptr<StartGameTitleActor> StartGameTitle_;
	std::shared_ptr<SuccessCount> SuccessCount_;

	bool CountDownStart_;
};

