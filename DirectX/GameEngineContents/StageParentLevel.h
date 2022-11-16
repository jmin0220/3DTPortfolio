#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "VirtualPhysXLevel.h"

enum class StageNum
{
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE4,
};

enum class Stage_MeshEnum
{
	START,	// 가장 시작
	// STAGE01
	// STAGE02
	// STAGE03
	// STAGE04
	HexAGoneMap,
	HexTile,
	// TEST
	Rainbow,
	TestMap,
	END, // 가장 마지막
};

struct StageObject
{
	std::string Name_;
	std::string Dir_;
	std::weak_ptr<GameEngineActor> Actor_;
};

// 설명 :
class StageParentLevel : public VirtualPhysXLevel
{
public:
	// constrcuter destructer
	StageParentLevel();
	~StageParentLevel();

	// delete Function
	StageParentLevel(const StageParentLevel& _Other) = delete;
	StageParentLevel(StageParentLevel&& _Other) noexcept = delete;
	StageParentLevel& operator=(const StageParentLevel& _Other) = delete;
	StageParentLevel& operator=(StageParentLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

	StageNum MyStage_;

private:
	std::vector<StageObject> StageObjects_;
	void LevelStartLoad();
};

