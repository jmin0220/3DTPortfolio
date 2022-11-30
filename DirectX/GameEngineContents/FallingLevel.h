#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� : ��ó�� ���� ���۽� �ε�

class LobbyPlayer;
class FallingLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	FallingLevel();
	~FallingLevel();

	// delete Function
	FallingLevel(const FallingLevel& _Other) = delete;
	FallingLevel(FallingLevel&& _Other) noexcept = delete;
	FallingLevel& operator=(const FallingLevel& _Other) = delete;
	FallingLevel& operator=(FallingLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:
	std::shared_ptr<LobbyPlayer> Player_;
};

