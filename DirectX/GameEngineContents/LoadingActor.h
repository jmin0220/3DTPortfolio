#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 로딩화면용 액터
class GameEngineTextureRenderer;
class GameEngineUIRenderer;
class LoadingActor : public GameEngineActor
{
public:
	// constrcuter destructer
	LoadingActor();
	~LoadingActor();

	// delete Function
	LoadingActor(const LoadingActor& _Other) = delete;
	LoadingActor(LoadingActor&& _Other) noexcept = delete;
	LoadingActor& operator=(const LoadingActor& _Other) = delete;
	LoadingActor& operator=(LoadingActor&& _Other) noexcept = delete;
	
	void CreateGames();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	std::shared_ptr<GameEngineTextureRenderer> BG_;
	std::shared_ptr<GameEngineTextureRenderer> Games_[5];
	std::shared_ptr<GameEngineTextureRenderer> Game_;
	std::shared_ptr<GameEngineUIRenderer> Exit_;
	std::shared_ptr<GameEngineUIRenderer> ExitButton_;
	std::shared_ptr<GameEngineFontRenderer> Font_;
	std::shared_ptr<GameEngineFontRenderer> ExitFont_;
	float LastGamesPos_;
	float Time_;
	int RandomNum_;
};

