#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class RoundEnd;
class GameSuccess : public GameEngineActor
{
public:
	// constrcuter destructer
	GameSuccess();
	~GameSuccess();

	// delete Function
	GameSuccess(const GameSuccess& _Other) = delete;
	GameSuccess(GameSuccess&& _Other) noexcept = delete;
	GameSuccess& operator=(const GameSuccess& _Other) = delete;
	GameSuccess& operator=(GameSuccess&& _Other) noexcept = delete;

	void AlphaSet();
	void TextRendererPop();
	void UIOff();

	float PopUpTime_;

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

	float4 SlicePos_;
};

