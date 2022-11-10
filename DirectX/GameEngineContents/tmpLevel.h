#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class TitleActor;
class Cursor;
class FontActor;
class NamePlate;
class NoneButton;
class NoneMoney;
class SelectShowButton;
class PlayButton;
class TopMenu;
class CrownCount;
class StartGameTitleActor;
class GoalTipActor;
class CountDown;
class SuccessCount;
class GameSuccess;
class TestActor;
class RoundEnd;
class tmpLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	tmpLevel();
	~tmpLevel();

	// delete Function
	tmpLevel(const tmpLevel& _Other) = delete;
	tmpLevel(tmpLevel&& _Other) noexcept = delete;
	tmpLevel& operator=(const tmpLevel& _Other) = delete;
	tmpLevel& operator=(tmpLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	std::shared_ptr<TitleActor> TitleLogo;
	std::shared_ptr<Cursor> Mouse;
	std::shared_ptr<FontActor> Font;
	std::shared_ptr<NamePlate> Name;
	std::shared_ptr<NoneButton> Button;
	std::shared_ptr<NoneMoney> MoneyUI;
	std::shared_ptr<SelectShowButton> ShowButton;
	std::shared_ptr<PlayButton> StartButton;
	std::shared_ptr<TopMenu> Top;
	std::shared_ptr<CrownCount> Crown;
	std::shared_ptr<StartGameTitleActor> Startbar_;
	std::shared_ptr<GoalTipActor> Tip_;
	std::shared_ptr<CountDown> CountDownActor_;
	std::shared_ptr<SuccessCount> Success_;
	std::shared_ptr<GameSuccess> GameSuccess_;
	std::shared_ptr<RoundEnd> RoundEnd_;

	std::shared_ptr<TestActor> Test_;

	bool Swap;
};

