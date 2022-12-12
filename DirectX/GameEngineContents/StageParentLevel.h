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

	// ��Ʈ�� ������ �÷��̾�
	static float4 PlayerPos;

	// ī�޶� ����
	std::shared_ptr<GameEngineCameraActor> MainCam_;
	std::shared_ptr<CameraArm> CameraArm_;

private:
	std::vector<StageObject> StageObjects_;
	void LevelStartLoad();

	// FSM : 321 ��, �������, ���� ���� ����(���� ������ �� ���� feat.����)
	// Ư�� �������� �ٸ��� �����ؾ� �ȴٸ�, Override�ؼ� ����� �� ����
protected:
	GameEngineStateManager StageStateManager_;
	std::shared_ptr<Cinemachine> CinemaCam_;

	// FSM���� ���͵�
	std::shared_ptr<class InGameSetUI> UIs_;

	// 321�� ������ �÷��̾ �غ� �����(����..)
	virtual void IdleStart(const StateInfo& _Info);
	virtual void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	// ī�޶� �ó׸�ƽ ���� + BGM
	virtual void StagePreViewStart(const StateInfo& _Info) {};
	virtual void StagePreViewUpdate(float _DeltaTime, const StateInfo& _Info) {};

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
	void SpawnServerObjects();
	int ServerSpawn = 0;
};

