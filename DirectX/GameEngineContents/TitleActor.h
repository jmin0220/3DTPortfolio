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

	void FontSizeAnimation();
	void LogoSizeAnimation();
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	GameEngineTextureRenderer* Logo;
	GameEngineTextureRenderer* Renderer2;
	GameEngineFontRenderer* Font;

	float FontSize;
	float XImageSize;
	float YImageSize;
	bool Swap;
};

