#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class CameraTestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	CameraTestLevel();
	~CameraTestLevel();

	// delete Function
	CameraTestLevel(const CameraTestLevel& _Other) = delete;
	CameraTestLevel(CameraTestLevel&& _Other) noexcept = delete;
	CameraTestLevel& operator=(const CameraTestLevel& _Other) = delete;
	CameraTestLevel& operator=(CameraTestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:

private:
	std::shared_ptr<class TestActor_WaterPlane> Floor_;
	std::vector<std::shared_ptr<GameEngineActor>> Actors_;
};

