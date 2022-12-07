#pragma once
//#include "PhysXCCTActorComponent.h"
#include "PhysXDynamicActorComponent.h"
#include "GameServerObject.h"

class CameraArm;
// 설명 :
class PlayerActor : public GameEngineActor, public GameServerObject
{
	// 서버
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

	//eventtrigger용 collision
	std::shared_ptr<GameEngineCollision> EventCol_;

	//CheckPoint Position
	float4 CheckPointPos_;
	bool CheckPointFlag_;

	//Race맵에서서의 Goal Check  골인했으면 IsGoal == true
	bool IsGoal_;

	// FSM
private:
	GameEngineStateManager PlayerStateManager_;

	void CreateFSMStates();

	// 상태 예시
	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void IdleEnd(const StateInfo& _Info);

	void RunStart(const StateInfo& _Info);
	void RunUpdate(float _DeltaTime, const StateInfo& _Info);
	void RunEnd(const StateInfo& _Info);

	void JumpStart(const StateInfo& _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void JumpEnd(const StateInfo& _Info);

	// 입력
	void InputController(float _DeltaTime);
	float4 MoveDir_;


	// TODO::테스트코드
	void ImpulseTest();
	void StandUp(float _DeltaTime);
	bool IsStanding_;
	float4 ResetCheckPointPos();


	// 캐릭터 애니메이션 & 스킨
private:
	void SetCharacterAnimation();
	void SetCharacterTexture();

	struct SkinData
	{
		float4 BodyColor;
	};

	SkinData SkinData_;

	//캐릭터 카메라 동기 회전관련
private:
	float4 GetCameraBaseRotationAng(float4 _ActorRot, float4 _CamRot, float4 _MoveDir, float _DeltaTime);
public:
	//플레이어 위치 재설정을 위한 GEt함수
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

