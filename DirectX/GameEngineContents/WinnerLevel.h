#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 설명 : 승리하여 환호하는 레벨
class Winner;
class LobbyPlayer;
class WinnerBG;
class FloorActor;
class UISkyBoxActor;
class WinnerLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	WinnerLevel();
	~WinnerLevel();

	// delete Function
	WinnerLevel(const WinnerLevel& _Other) = delete;
	WinnerLevel(WinnerLevel&& _Other) noexcept = delete;
	WinnerLevel& operator=(const WinnerLevel& _Other) = delete;
	WinnerLevel& operator=(WinnerLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:
	std::shared_ptr<Winner> Winner_;
	std::shared_ptr<LobbyPlayer> Player_;
	std::shared_ptr<WinnerBG> BG_;
	std::shared_ptr<FloorActor> Chair_;
	std::shared_ptr<UISkyBoxActor> Sky_;

	float ChairTime_;
};

