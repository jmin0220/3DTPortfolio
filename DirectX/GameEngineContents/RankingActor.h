#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :후프 인게임용 랭킹 체크UI

class RankingActor : public GameEngineActor
{
public:
	// constrcuter destructer
	RankingActor();
	~RankingActor();

	// delete Function
	RankingActor(const RankingActor& _Other) = delete;
	RankingActor(RankingActor&& _Other) noexcept = delete;
	RankingActor& operator=(const RankingActor& _Other) = delete;
	RankingActor& operator=(RankingActor&& _Other) noexcept = delete;

	void BubbleSort();
	void ChaseNameToScore();
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:
	std::shared_ptr<GameEngineUIRenderer> Renderer_[5];
	std::shared_ptr<GameEngineFontRenderer> Font_[5];
	std::shared_ptr<GameEngineFontRenderer> ScoreFont_[5];

	int Score_[5];
};

