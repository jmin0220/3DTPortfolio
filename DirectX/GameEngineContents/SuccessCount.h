#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SuccessCount : public GameEngineActor
{
public:
	// constrcuter destructer
	SuccessCount();
	~SuccessCount();

	// delete Function
	SuccessCount(const SuccessCount& _Other) = delete;
	SuccessCount(SuccessCount&& _Other) noexcept = delete;
	SuccessCount& operator=(const SuccessCount& _Other) = delete;
	SuccessCount& operator=(SuccessCount&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	int MaxCount_;
	int CurrentCount_;
	
	GameEngineFontRenderer* MaxFont_;
	GameEngineFontRenderer* CurrentFont_;
	GameEngineFontRenderer* SlashFont_;
	GameEngineFontRenderer* SuccessFont_;
	
	GameEngineUIRenderer* Renderer_;
};

