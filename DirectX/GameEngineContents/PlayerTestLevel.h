#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class PlayerTestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayerTestLevel();
	~PlayerTestLevel();

	// delete Function
	PlayerTestLevel(const PlayerTestLevel& _Other) = delete;
	PlayerTestLevel(PlayerTestLevel&& _Other) noexcept = delete;
	PlayerTestLevel& operator=(const PlayerTestLevel& _Other) = delete;
	PlayerTestLevel& operator=(PlayerTestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:

private:
	std::shared_ptr<GameEngineActor> Player;
	class TestActor_WaterPlane* Floor_;
	GameEngineActor* Player_;
};

