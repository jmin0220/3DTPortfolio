#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameFail : public GameEngineActor
{
public:
	// constrcuter destructer
	GameFail();
	~GameFail();

	// delete Function
	GameFail(const GameFail& _Other) = delete;
	GameFail(GameFail&& _Other) noexcept = delete;
	GameFail& operator=(const GameFail& _Other) = delete;
	GameFail& operator=(GameFail&& _Other) noexcept = delete;

	void TextRendererPop();
	void AlphaSet();
	void Reset();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
private:
	std::shared_ptr<GameEngineUIRenderer> SetRenderer_;
	std::shared_ptr<GameEngineUIRenderer> CrownRenderer_;
	std::shared_ptr<GameEngineUIRenderer> SideCircle1_;
	std::shared_ptr<GameEngineUIRenderer> SideCircle2_;
	std::shared_ptr<GameEngineUIRenderer> SideCircle3_;
	std::shared_ptr<GameEngineUIRenderer> SideCircle4_;
	std::shared_ptr<GameEngineUIRenderer> Text_;

	bool IsPop_;
	bool IsOut_;
	bool IsBoing_;
	float PopUpTime_;

	float4 SlicePos_;
};

