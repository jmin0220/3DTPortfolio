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

	static int Score_;
	//static int Player1Score_;
	//static int Player2Score_;
	//static int Player3Score_;
	//static int Player4Score_;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	int MaxCount_;
	int CurrentCount_;
	
	std::shared_ptr<GameEngineFontRenderer> ScoreFont_;
	std::shared_ptr<GameEngineFontRenderer> MaxFont_;
	std::shared_ptr<GameEngineFontRenderer> CurrentFont_;
	std::shared_ptr<GameEngineFontRenderer> SlashFont_;
	std::shared_ptr<GameEngineFontRenderer> SuccessFont_;
	
	std::shared_ptr<GameEngineUIRenderer> Renderer_;
};

