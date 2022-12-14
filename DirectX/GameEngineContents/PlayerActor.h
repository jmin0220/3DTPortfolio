#pragma once
//#include "PhysXCCTActorComponent.h"
#include "PhysXDynamicActorComponent.h"
#include "GameServerObject.h"

class CameraArm;

enum class PlayerActType
{
	Idle,
	Run,
	Jump,
	Dive,
	Ununcontrollable,
};

// 설명 :
class PlayerActor : public GameEngineActor, public GameServerObject
{
	// 서버 디버깅
public:
	static PlayerActor* MainPlayer;
	static bool IsMainPlayerSpawned_;
	static int GetPlayerID()
	{
		return MainPlayer->GetNetID();
	}

	void SetNetPlayerColor(unsigned int _Color);
	void SetNetPlayerAnimation(const std::string& _Animation);
	bool IsNetPlayerColorExist_;
	std::string PrevAnimation_;

private:
	bool IsPlayerble_;
	//인풋을 받는가
	bool IsInputOn_;
	//플레이어가 멈추는가
	bool IsPlayerFrozen_;

	bool IsNetDeath_;
	// 서버
public:
	void SetInputAvailable(bool _Value)
	{
		IsInputOn_ = _Value;
	}

	void SetPlayerForze(bool _Value)
	{
		IsPlayerFrozen_ = _Value;
	}

	void SetPlayerInvisible(bool _Value)
	{
		if (true == _Value)
		{
			FbxRenderer_->Off();
		}
		else
		{
			FbxRenderer_->On();
		}
	}

	void SetPlayerNetDeath(bool _Value)
	{
		IsNetDeath_ = _Value;
	}

	bool GetNetDeath()
	{
		return IsNetDeath_;
	}

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

	// 렌더러, 피직스 외부에서 초기화 시점 조절하도록
	void PlayerInit();
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
	std::shared_ptr<GameEngineCollision> Collision_;

	//CheckPoint Position
	float4 CheckPointPos_;
	bool CheckPointFlag_;

	//Race맵에서서의 Goal Check  골인했으면 IsGoal == true
	bool IsGoal_;

	// FSM
private:
	GameEngineStateManager PlayerStateManager_;
	GameEngineStateManager PlayerAniStateManager_;

	void CreateFSMStates();
	void CreateAnimationFSMStates();

	// PlayerStateFSM
	void ReadyStart(const StateInfo& _Info);
	void ReadyUpdate(float _DeltaTime, const StateInfo& _Info);
	void ReadyEnd(const StateInfo& _Info);

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void IdleEnd(const StateInfo& _Info);

	void RunStart(const StateInfo& _Info);
	void RunUpdate(float _DeltaTime, const StateInfo& _Info);
	void RunEnd(const StateInfo& _Info);

	void JumpStart(const StateInfo& _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void JumpEnd(const StateInfo& _Info);

	void DiveStart(const StateInfo& _Info);
	void DiveUpdate(float _DeltaTime, const StateInfo& _Info);
	void DiveEnd(const StateInfo& _Info);

	void DiveGetUpStart(const StateInfo& _Info);
	void DiveGetUpUpdate(float _DeltaTime, const StateInfo& _Info);
	void DiveGetUpEnd(const StateInfo& _Info);

	void CannotControlAniStart(const StateInfo& _Info);
	void CannotControlAniUpdate(float _DeltaTime, const StateInfo& _Info);
	void CannotControlAniEnd(const StateInfo& _Info);


	// PlayerAnimationFSM
	void IdleAniStart(const StateInfo& _Info);
	void IdleAniUpdate(float _DeltaTime, const StateInfo& _Info);
	void IdleAniEnd(const StateInfo& _Info);

	void RunAniStart(const StateInfo& _Info);
	void RunAniUpdate(float _DeltaTime, const StateInfo& _Info);
	void RunAniEnd(const StateInfo& _Info);

	void WalkAniStart(const StateInfo& _Info);
	void WalkAniUpdate(float _DeltaTime, const StateInfo& _Info);
	void WalkAniEnd(const StateInfo& _Info);

	void JumpStartAniStart(const StateInfo& _Info);
	void JumpStartAniUpdate(float _DeltaTime, const StateInfo& _Info);
	void JumpStartAniEnd(const StateInfo& _Info);

	void JumpMidAirAniStart(const StateInfo& _Info);
	void JumpMidAirAniUpdate(float _DeltaTime, const StateInfo& _Info);
	void JumpMidAirAniEnd(const StateInfo& _Info);

	void JumpLandingAniStart(const StateInfo& _Info);
	void JumpLandingAniUpdate(float _DeltaTime, const StateInfo& _Info);
	void JumpLandingAniEnd(const StateInfo& _Info);

	void DiveLoopAniStart(const StateInfo& _Info);
	void DiveLoopAniUpdate(float _DeltaTime, const StateInfo& _Info);
	void DiveLoopAniEnd(const StateInfo& _Info);

	void DiveGetUpAniStart(const StateInfo& _Info);
	void DiveGetUpAniUpdate(float _DeltaTime, const StateInfo& _Info);
	void DiveGetUpAniEnd(const StateInfo& _Info);

	void CannotControlStart(const StateInfo& _Info);
	void CannotControlUpdate(float _DeltaTime, const StateInfo& _Info);
	void CannotControlEnd(const StateInfo& _Info);


	// 입력 & 움직임
	void InputControllerMove(float _DeltaTime);
	void InputControllerJump(float _DeltaTime);
	void InputControllerDive(float _DeltaTime);
	PlayerActType InputDetect();
	float4 MoveDir_;
	float4 Velocity_;
	bool IsTouchGround;
	bool IsDetachGround;
	bool IsOnGround;
	bool IsOnGround2;
	bool IsHeadTouchGround_;
	float PlayerXZSpeed_;
	void CheckXZSpeed();
	bool CheckOnGround();
	bool waitphysx_;
	bool IsDiving_;

	float UnControlableTime_;
	bool IsUnControlable_;
	// 일어서기
	bool StandUp(float _DeltaTime);
	bool IsStandingReady_;
	float StandUpDelay_;

	// TODO::테스트코드
	void ImpulseTest();
	bool IsStanding_;

	float4 ResetCheckPointPos();

	// 캐릭터 애니메이션 & 스킨
private:
	void SetCharacterAnimation();
	void SetCharacterTexture();
	std::string CurAniName;

	struct SkinData
	{
		float4 BodyColor;
	};

	SkinData SkinData_;

	void ResetPlayer();

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

	// 서버
	void SetGoal(bool _Value)
	{
		IsGoal_ = _Value;
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


	//움직임 Setter Getter
	inline void TouchGroundOff()
	{
		IsTouchGround = false;
	}

	inline void TouchGroundOn()
	{
		IsTouchGround = true;
	}

	inline void DetachGroundOff()
	{
		IsDetachGround = false;
	}

	inline void DetachGroundOn()
	{
		IsDetachGround = true;
	}

	inline void SetIsStandingReady(bool _Result)
	{
		IsStandingReady_ = _Result;
	}

	inline void SetIsOngGround2()
	{
		IsOnGround2 = true;
	}

	inline void Setwaitphysx(bool _Bool)
	{
		waitphysx_ = _Bool;
	}

	inline void OnUnControlable()
	{
		IsUnControlable_ = true;
	}

	inline void OffUnControlable()
	{
		IsUnControlable_ = false;
	}

	inline void ResetPlayerPos()
	{
		DynamicActorComponent_->SetPlayerStartPos(CheckPointPos_);
		ResetPlayer();
	}

	inline void InitStandUp2()
	{
		DynamicActorComponent_->InitializeStandUp2();
	}

	inline void IsHeadTouchGroundOn()
	{
		IsHeadTouchGround_ = true;
	}

	inline void IsHeadTouchGroundOff()
	{
		IsHeadTouchGround_ = false;
	}
};

