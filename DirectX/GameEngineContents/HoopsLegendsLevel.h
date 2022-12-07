#pragma once
#include "StageParentLevel.h"

// Ό³Έν :
class HoopsLegendsLevel	:	public StageParentLevel
{
public:
	// constrcuter destructer
	HoopsLegendsLevel();
	~HoopsLegendsLevel();

	// delete Function
	HoopsLegendsLevel(const HoopsLegendsLevel& _Other) = delete;
	HoopsLegendsLevel(HoopsLegendsLevel&& _Other) noexcept = delete;
	HoopsLegendsLevel& operator=(const HoopsLegendsLevel& _Other) = delete;
	HoopsLegendsLevel& operator=(HoopsLegendsLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:
	std::shared_ptr<class TestGUI> GUI_;
};

