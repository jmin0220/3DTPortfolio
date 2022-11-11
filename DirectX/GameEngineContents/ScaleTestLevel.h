#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class ScaleTestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	ScaleTestLevel();
	~ScaleTestLevel();

	// delete Function
	ScaleTestLevel(const ScaleTestLevel& _Other) = delete;
	ScaleTestLevel(ScaleTestLevel&& _Other) noexcept = delete;
	ScaleTestLevel& operator=(const ScaleTestLevel& _Other) = delete;
	ScaleTestLevel& operator=(ScaleTestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:

private:
	class TestActor_WaterPlane* Floor_;
	GameEngineActor* Player_;
};

