#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
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


	void FontSizeAnimation();
	void LogoSizeAnimation();
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;

private:
	std::shared_ptr<GameEngineTextureRenderer> Logo_;
	std::shared_ptr<GameEngineFontRenderer> Font_;

	float FontSize_;
	bool Swap_;
};

