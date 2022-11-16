#pragma once
#include "StageParentLevel.h"
// Ό³Έν :

class HexAGoneLevel	:	public StageParentLevel
{
public:
	// constrcuter destructer
	HexAGoneLevel();
	~HexAGoneLevel();

	// delete Function
	HexAGoneLevel(const HexAGoneLevel& _Other) = delete;
	HexAGoneLevel(HexAGoneLevel&& _Other) noexcept = delete;
	HexAGoneLevel& operator=(const HexAGoneLevel& _Other) = delete;
	HexAGoneLevel& operator=(HexAGoneLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:

};

