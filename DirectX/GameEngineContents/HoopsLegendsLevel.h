#pragma once
#include "StageParentLevel.h"

// 설명 :
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

	// 게임 종료조건
	bool GameEndingFlag() override;
private:
	//std::shared_ptr<class TestGUI> GUI_;
	std::shared_ptr<GameEngineActor> Hoops_;

	void SpawnHoops();
	void SetHoopPosition();

	int Num_;
	int PrevPos[10];
	float4 Pos[10];

	bool SettingHoops_;
	bool ServerActivated_;
};

