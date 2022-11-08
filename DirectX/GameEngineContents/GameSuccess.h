#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
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
	GameEngineUIRenderer* SetRenderer_;
	GameEngineUIRenderer* SideCircle1_;
	GameEngineUIRenderer* SideCircle2_;
	GameEngineUIRenderer* SideCircle3_;
	GameEngineUIRenderer* SideCircle4_;
	GameEngineUIRenderer* Text_;

	bool IsPop_;
	bool IsOut_;
};

