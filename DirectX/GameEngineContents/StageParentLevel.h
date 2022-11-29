#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "VirtualPhysXLevel.h"
#include "CameraArm.h"

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
	DoorBlock,
	MovingBar,
	Chevron,
	// STAGE02
	// STAGE03
	// STAGE04
	HexAGoneMap,
	HexTile,
	// TEST
	Rainbow,
	TestMap,



	//Collision
	Col_StartPos,
	Col_CheckPoint,
	Col_Trigger,
	Col_Goal,
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

	static float4 PlayerPos;

	// 카메라 암
	std::shared_ptr<CameraArm> CameraArm_;

private:
	std::vector<StageObject> StageObjects_;
	void LevelStartLoad();

	// FSM : 321 땅, 경기종료, 등의 레벨 상태(점점 많아질 수 있음 feat.서버)
protected:
	GameEngineStateManager StageStateManager_;

	// FSM관련 엑터들
	std::shared_ptr<class InGameSetUI> UIs_;

	// 321땅 이전에 플레이어가 준비가 됬는지(서버..)
	virtual void IdleStart(const StateInfo& _Info);
	virtual void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	// 321땅
	virtual void ReadyStart(const StateInfo& _Info);
	virtual void ReadyUpdate(float _DeltaTime, const StateInfo& _Info);

	// 경기중 : 체크포인트 저장, 리스폰 등
	virtual void RaceStart(const StateInfo& _Info);
	virtual void RaceUpdate(float _DeltaTime, const StateInfo& _Info);

	// 경기종료 : 정리
	virtual void EndStart(const StateInfo& _Info);
	virtual void EndUpdate(float _DeltaTime, const StateInfo& _Info);

};

