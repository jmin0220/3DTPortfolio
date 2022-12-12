#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 로딩 촤라락 끝나고 정해진 게임소개 창
class GameEngineUIRenderer;
class IntroduceGame : public GameEngineActor
{
public:
	// constrcuter destructer
	IntroduceGame();
	~IntroduceGame();

	// delete Function
	IntroduceGame(const IntroduceGame& _Other) = delete;
	IntroduceGame(IntroduceGame&& _Other) noexcept = delete;
	IntroduceGame& operator=(const IntroduceGame& _Other) = delete;
	IntroduceGame& operator=(IntroduceGame&& _Other) noexcept = delete;

	std::weak_ptr<GameEngineUIRenderer> GetRenderer()
	{
		return Game_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:
	std::shared_ptr<GameEngineUIRenderer> Game_;
	bool IsLoadingEnd_;
	float Time_;
};

