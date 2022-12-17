#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "VirtualPhysXLevel.h"
#include "CameraArm.h"
#include "Cinemachine.h"

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
	HexProPeller,
	JumboTronProPeller,
	JumboTron1,
	JumboTron2,
	JumboTron3,
	JumboTron4,
	JumboTron5,
	JumboTron6,
	JumboTron7,

	// STAGE05
	WoodPlank,
	HoopsScythe,
	HoopsScoreRing,
	HoopsScoreRing2,
	HoopsBox,
	HoopsBox2,
	HoopsBox3,
	HoopsBox4,
	HoopsRamp,
	HoopsRamp2,

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
	// 컨트롤 가능한 플레이어
	static float4 PlayerPos;
	static std::vector<float4> HoopsPos;
	static std::vector<std::shared_ptr<GameEngineActor>> HoopsActor;
	// constrcuter destructer
	StageParentLevel();
	~StageParentLevel();

	// delete Function
	StageParentLevel(const StageParentLevel& _Other) = delete;
	StageParentLevel(StageParentLevel&& _Other) noexcept = delete;
	StageParentLevel& operator=(const StageParentLevel& _Other) = delete;
	StageParentLevel& operator=(StageParentLevel&& _Other) noexcept = delete;

	std::shared_ptr<CameraArm> GetCameraArm()
	{
		return CameraArm_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

	StageNum MyStage_;


	// 카메라 관련
	std::shared_ptr<GameEngineCameraActor> MainCam_;
	std::shared_ptr<CameraArm> CameraArm_;

private:
	std::vector<StageObject> StageObjects_;
	void LevelStartLoad();

	// FSM : 321 땅, 경기종료, 등의 레벨 상태(점점 많아질 수 있음 feat.서버)
	// 특정 레벨에만 다르게 동작해야 된다면, Override해서 사용할 수 있음
protected:
	GameEngineStateManager StageStateManager_;
	std::shared_ptr<Cinemachine> CinemaCam_;

	// FSM관련 엑터들
	std::shared_ptr<class InGameSetUI> UIs_;
	std::shared_ptr<class IntroduceGame> IntroduceGame_;

	// 321땅 이전에 플레이어가 준비가 됬는지(서버..)
	virtual void IdleStart(const StateInfo& _Info);
	virtual void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	// 카메라 시네마틱 무브 + BGM
	virtual void StagePreviewStart(const StateInfo& _Info);
	virtual void StagePreviewUpdate(float _DeltaTime, const StateInfo& _Info);

	// 321땅
	virtual void ReadyStart(const StateInfo& _Info);
	virtual void ReadyUpdate(float _DeltaTime, const StateInfo& _Info);

	// 경기중 : 체크포인트 저장, 리스폰 등
	virtual void RaceStart(const StateInfo& _Info);
	virtual void RaceUpdate(float _DeltaTime, const StateInfo& _Info);

	// 경기종료 : 정리
	virtual void EndStart(const StateInfo& _Info);
	virtual void EndUpdate(float _DeltaTime, const StateInfo& _Info);


	// 서버
private:
	void SpawnServerObjects();
	
public:
	static bool AllPlayersReady_;
};

