#pragma once
//#include "PhysXCCTActorComponent.h"
#include "PhysXDynamicActorComponent.h"
#include "GameServerObject.h"

class CameraArm;
// ���� :
class PlayerActor : public GameEngineActor, public GameServerObject
{
	// ����
private:
	static bool IsMainPlayerSpawned_;
	bool IsPlayerble_;

public:
	// constrcuter destructer
	PlayerActor();
	~PlayerActor();

	// delete Function
	PlayerActor(const PlayerActor& _Other) = delete;
	PlayerActor(PlayerActor&& _Other) noexcept = delete;
	PlayerActor& operator=(const PlayerActor& _Other) = delete;
	PlayerActor& operator=(PlayerActor&& _Other) noexcept = delete;

	physx::PxRigidDynamic* CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	std::shared_ptr<GameEngineFBXAnimationRenderer> FbxRenderer_;
	std::shared_ptr<PhysXDynamicActorComponent> DynamicActorComponent_;

	//eventtrigger�� collision
	std::shared_ptr<GameEngineCollision> EventCol_;

	//CheckPoint Position
	float4 CheckPointPos_;
	bool CheckPointFlag_;

	//Race�ʿ������� Goal Check  ���������� IsGoal == true
	bool IsGoal_;

	// FSM
private:
	GameEngineStateManager PlayerStateManager_;

	void CreateFSMStates();

	// ���� ����
	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void IdleEnd(const StateInfo& _Info);

	void RunStart(const StateInfo& _Info);
	void RunUpdate(float _DeltaTime, const StateInfo& _Info);
	void RunEnd(const StateInfo& _Info);

	void JumpStart(const StateInfo& _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void JumpEnd(const StateInfo& _Info);

	// �Է�
	void InputController(float _DeltaTime);
	float4 MoveDir_;


	// TODO::�׽�Ʈ�ڵ�
	void ImpulseTest();
	void StandUp(float _DeltaTime);
	bool IsStanding_;
	float4 ResetCheckPointPos();


	// ĳ���� �ִϸ��̼� & ��Ų
private:
	void SetCharacterAnimation();
	void SetCharacterTexture();

	struct SkinData
	{
		float4 BodyColor;
	};

	SkinData SkinData_;

	//ĳ���� ī�޶� ���� ȸ������
private:
	float4 GetCameraBaseRotationAng(float4 _ActorRot, float4 _CamRot, float4 _MoveDir, float _DeltaTime);
public:
	//�÷��̾� ��ġ �缳���� ���� GEt�Լ�
	std::shared_ptr<PhysXDynamicActorComponent> GetDynamicActorComponent()
	{
		return DynamicActorComponent_;
	}

	inline void SetCheckPoint(float4 _Pos)
	{
		CheckPointPos_ = _Pos;
	}

	inline void SetIsGoal()
	{
		IsGoal_ = !IsGoal_;
	}

	inline void SetFlag()
	{
		CheckPointFlag_ = !CheckPointFlag_;
	}

	inline bool GetIsGoal()
	{
		return IsGoal_;
	}

	inline bool GetFlag()
	{
		return CheckPointFlag_;
	}

	float4 MeshBoundScale;

};

