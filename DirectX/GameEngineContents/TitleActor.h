#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class TitleActor : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleActor();
	~TitleActor();

	// delete Function
	TitleActor(const TitleActor& _Other) = delete;
	TitleActor(TitleActor&& _Other) noexcept = delete;
	TitleActor& operator=(const TitleActor& _Other) = delete;
	TitleActor& operator=(TitleActor&& _Other) noexcept = delete;

	GameEngineTextureRenderer* GetLogo()
	{
		return Logo;
	}

	GameEngineFontRenderer* GetFont()
	{
		return Font;
	}

	void FontSizeAnimation();
	void LogoSizeAnimation();
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;

private:
	GameEngineTextureRenderer* Logo;
	GameEngineFontRenderer* Font;

	float FontSize;
	bool Swap;
};

