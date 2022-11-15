#pragma once
#include "StageParentLevel.h"

// Ό³Έν :
class StageTestLevel : public StageParentLevel
{
public:
	// constrcuter destructer
	StageTestLevel();
	~StageTestLevel();

	// delete Function
	StageTestLevel(const StageTestLevel& _Other) = delete;
	StageTestLevel(StageTestLevel&& _Other) noexcept = delete;
	StageTestLevel& operator=(const StageTestLevel& _Other) = delete;
	StageTestLevel& operator=(StageTestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:

};

