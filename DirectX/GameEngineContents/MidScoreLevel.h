#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 설명 : 중간 점검 점수 체크(커스텀)
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
	std::shared_ptr<FontActor> Font1Score_;
	std::shared_ptr<FontActor> Font2_;
	std::shared_ptr<FontActor> Font2Score_;

	std::string Player1Name_;
	std::string Player2Name_;

	float FallingTime_;
};

