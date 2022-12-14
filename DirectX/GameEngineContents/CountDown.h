#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ???? :3..2..1..GO!
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
	bool CountDownEnd()
	{
		return IsCountDownEnd_;
	}
	void PopEnd();
	void Reset();
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};


	void LevelStartEvent() override;

private:
	std::shared_ptr<GameEngineUIRenderer> Three_;
	std::shared_ptr<GameEngineUIRenderer> Two_;
	std::shared_ptr<GameEngineUIRenderer> One_;
	std::shared_ptr<GameEngineUIRenderer> Go_;
	std::shared_ptr<GameEngineUIRenderer> PopAni1_;
	std::shared_ptr<GameEngineUIRenderer> PopAni2_;
	std::shared_ptr<GameEngineUIRenderer> PopAni3_;
	std::shared_ptr<GameEngineUIRenderer> PopAni4_;
	std::shared_ptr<GameEngineUIRenderer> PopAni5_;
	std::shared_ptr<GameEngineUIRenderer> PopAni6_;

	bool IsThreePop_;
	bool IsTwoPop_;
	bool IsOnePop_;
	bool IsGoPop_;

	bool IsThreeEnd_;
	bool IsTwoEnd_;
	bool IsOneEnd_;
	bool IsGoEnd_;
	bool IsAniOn_;

	bool Three_SoundOn_;
	bool Three_Once_;
	bool Two_SoundOn_;
	bool Two_Once_;
	bool One_SoundOn_;
	bool One_Once_;
	bool Go_SoundOn_;
	bool Go_Once_;

	bool IsCountDownEnd_;
};

