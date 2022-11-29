#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� : �¸��Ͽ� ȯȣ�ϴ� ����
class Winner;
class LobbyPlayer;
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
};

