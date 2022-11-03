#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :3..2..1..GO!
class CountDown : public GameEngineActor
{
public:
	// constrcuter destructer
	CountDown();
	~CountDown();

	// delete Function
	CountDown(const CountDown& _Other) = delete;
	CountDown(CountDown&& _Other) noexcept = delete;
	CountDown& operator=(const CountDown& _Other) = delete;
	CountDown& operator=(CountDown&& _Other) noexcept = delete;

	void CountDownStart();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
private:
	GameEngineUIRenderer* Three_;
	GameEngineUIRenderer* Two_;
	GameEngineUIRenderer* One_;
	GameEngineUIRenderer* Go_;
	bool IsThreePop_;
	bool IsTwoPop_;
	bool IsOnePop_;
	bool IsGoPop_;

	bool IsThreeEnd_;
	bool IsTwoEnd_;
	bool IsOneEnd_;
	bool IsGoEnd_;
};

