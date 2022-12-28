#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 설명 : 중간 점검 점수 체크(커스텀)
class LobbyPlayer;
class FloorActor;
class GoalTipActor;
class MidScoreBGActor;
class FontActor;
class RankingActor;
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

	void QuickSort(int arr[], int _Up,int _Down);

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

	std::shared_ptr<FontActor> Font1st_;
	std::shared_ptr<FontActor> Font2nd_;


	std::vector<std::shared_ptr<FontActor>> Font_PlayerName;
	std::vector<std::shared_ptr<FontActor>> FontScore_;
	std::vector<int> PlayerScores_;
	std::vector<std::string> PlayerName_;

	std::vector<std::shared_ptr<LobbyPlayer>> LobbyPlayers_;
	std::vector<std::shared_ptr<FloorActor>> Chairs_;

	std::shared_ptr<RankingActor> Rank_;

	float BeforeScoreTime_;
	float FallingTime_;
	float LerpTime_;
	bool IsScoreOn_;
	bool Once_;

	// 서버
private:
	struct ServerPlayerInfo
	{
		unsigned int ID_;
		unsigned int Color_;
		unsigned int Score_;
	};

	static bool ScoreBigger(ServerPlayerInfo _Left, ServerPlayerInfo _Right)
	{
		return _Left.Score_ > _Right.Score_;
	}

	static bool IDSmaller(ServerPlayerInfo _Left, ServerPlayerInfo _Right)
	{
		return _Left.ID_ < _Right.ID_;
	}

	void ServerSetting();
	void NoServerSetting();

	std::vector<ServerPlayerInfo> AllServerPlayers_;

	int AllServerPlayersCount_;
	float MidScoreTime_;
	bool LevelChanged_;
	bool ScoreSetted_;
	float4 LastActorPos_;

};

