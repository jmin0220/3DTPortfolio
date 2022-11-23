#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class StartGameTitleActor : public GameEngineActor
{
public:
	// constrcuter destructer
	StartGameTitleActor();
	~StartGameTitleActor();

	// delete Function
	StartGameTitleActor(const StartGameTitleActor& _Other) = delete;
	StartGameTitleActor(StartGameTitleActor&& _Other) noexcept = delete;
	StartGameTitleActor& operator=(const StartGameTitleActor& _Other) = delete;
	StartGameTitleActor& operator=(StartGameTitleActor&& _Other) noexcept = delete;

	void TitlebarAnimation();

	void SetTitleText(std::string _TitleText, std::string _SubText, std::string _GameIcon)
	{
		TitleFont_->SetText(_TitleText, "Noto Sans CJK SC");
		SubTitleFont_->SetText(_SubText, "Noto Sans CJK SC");
		GameIcon_->SetTexture(_GameIcon);
	}

	void Reset();
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
private:
	std::shared_ptr<GameEngineUIRenderer> GreenTitle_;
	std::shared_ptr<GameEngineUIRenderer> WhiteTitle_;
	std::shared_ptr<GameEngineUIRenderer> BlackTitle_;
	std::shared_ptr<GameEngineUIRenderer> GameIcon_;
	std::shared_ptr<GameEngineFontRenderer> TitleFont_;
	std::shared_ptr<GameEngineFontRenderer> SubTitleFont_;
	bool Swap_;
	bool IsFirstAniEnd_;
	bool IsSecondAniEnd_;
};

