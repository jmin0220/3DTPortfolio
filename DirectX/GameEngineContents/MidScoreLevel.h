#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� : �߰� ���� ���� üũ(Ŀ����)
class LobbyPlayer;
class FloorActor;
class GoalTipActor;
class MidScoreBGActor;
class FontActor;
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

	void RandomSocre();
	void BubbleSortLerp();
	void RenderBubbleSort();
	void ChaseNameToScore();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:
	std::shared_ptr<LobbyPlayer> Player1_;
	std::shared_ptr<FloorActor> Chair1_;

	std::shared_ptr<LobbyPlayer> Player2_;
	std::shared_ptr<FloorActor> Chair2_;

	std::shared_ptr<LobbyPlayer> Player3_;
	std::shared_ptr<FloorActor> Chair3_;

	std::shared_ptr<LobbyPlayer> Player4_;

	std::shared_ptr<GoalTipActor> Score_;
	std::shared_ptr<MidScoreBGActor> BG_;

	std::shared_ptr<FontActor> Font1_;

	std::shared_ptr<FontActor> Font2_;


	std::shared_ptr<FontActor> Font_PlayerName[5];
	std::shared_ptr<FontActor> FontScore_[5];

	int PlayerScores_[5];

	int Index_[5];

	std::string PlayerName_[5];

	float BeforeScoreTime_;
	float FallingTime_;
	float LerpTime_;
	bool IsScoreOn_;
	bool Once_;

	// ����
private:
	float MidScoreTime_;
	bool LevelChanged_;

};

