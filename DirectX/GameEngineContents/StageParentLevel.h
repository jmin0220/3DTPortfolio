#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "VirtualPhysXLevel.h"
#include "CameraArm.h"
#include "Cinemachine.h"

enum class Stage_MeshEnum
{
	START,	// ���� ����
	// STAGE01
	DoorBlock,
	MovingBar,
	Chevron,
	// STAGE02
	// STAGE03
	S04Chevron_low1_TopRotater_low_MainTriRotater2_low,
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
	END, // ���� ������
};

struct StageObject
{
	std::string Name_;
	std::string Dir_;
	std::weak_ptr<GameEngineActor> Actor_;
};

// ���� :
class StageParentLevel : public VirtualPhysXLevel
{
public:
	// ��Ʈ�� ������ �÷��̾�
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

	// ���� ���� ����
	virtual bool GameEndingFlag() { return false; };

	StageNum MyStage_;


	// ī�޶� ����
	std::shared_ptr<GameEngineCameraActor> MainCam_;
	std::shared_ptr<CameraArm> CameraArm_;

private:
	std::vector<StageObject> StageObjects_;
	void LevelStartLoad();

	// FSM : 321 ��, �������, ���� ���� ����(���� ������ �� ���� feat.����)
	// Ư�� �������� �ٸ��� �����ؾ� �ȴٸ�, Override�ؼ� ����� �� ����
protected:
	std::vector<float4>	StartPositions_;
	std::vector<float4> HoopsStartPos_;
	GameEngineStateManager StageStateManager_;
	std::shared_ptr<Cinemachine> CinemaCam_;

	std::shared_ptr<GameEngineLight> LightObject_;


	// FSM���� ���͵�
	std::shared_ptr<class InGameSetUI> UIs_;
	std::shared_ptr<class IntroduceGame> IntroduceGame_;

	// 321�� ������ �÷��̾ �غ� �����(����..)
	virtual void IdleStart(const StateInfo& _Info);
	virtual void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	// ī�޶� �ó׸�ƽ ���� + BGM
	virtual void StagePreviewStart(const StateInfo& _Info);
	virtual void StagePreviewUpdate(float _DeltaTime, const StateInfo& _Info);

	// 321��
	virtual void ReadyStart(const StateInfo& _Info);
	virtual void ReadyUpdate(float _DeltaTime, const StateInfo& _Info);

	// ����� : üũ����Ʈ ����, ������ ��
	virtual void RaceStart(const StateInfo& _Info);
	virtual void RaceUpdate(float _DeltaTime, const StateInfo& _Info);

	// ������� : ����
	virtual void EndStart(const StateInfo& _Info);
	virtual void EndUpdate(float _DeltaTime, const StateInfo& _Info);


	// ����
private:
	//virtual void SpawnMyServerPlayer() = 0;
	void SpawnServerObjects();
	void SetWatchCamNextPlayer();

	std::vector<std::shared_ptr<GameEngineActor>> NetPlayers_;
	std::vector<std::shared_ptr<GameEngineActor>> NetObstacles_;
	std::vector<std::shared_ptr<GameEngineActor>> WatchPlayers_;
	int WatchCamIdx;

protected:
	enum class GameScoreType
	{
		NONE,
		RACE,			// 1���� 100��
		SURVIVAL,		// 1���� 0��
		TIMEATTACK,		// ��������
	};

	GameScoreType GameScoreType_;

	// IsGoal�� �� ���� �ο� : RACE, SURVIVAL
	void GetGameScoreByCurrentType();

	// ��������
	std::shared_ptr<class TimerActor> TimerUI_;

public:

	std::shared_ptr<class TestGUI> GUI_;

};

