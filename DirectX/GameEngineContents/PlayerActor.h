#pragma once
//#include "PhysXCCTActorComponent.h"
#include "PhysXDynamicActorComponent.h"

// 설명 :
class PlayerActor : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerActor();
	~PlayerActor();

	// delete Function
	PlayerActor(const PlayerActor& _Other) = delete;
	PlayerActor(PlayerActor&& _Other) noexcept = delete;
	PlayerActor& operator=(const PlayerActor& _Other) = delete;
	PlayerActor& operator=(PlayerActor&& _Other) noexcept = delete;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxControllerManager* _CtrManager);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelStartEvent() override;

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> FbxRenderer_;
	std::shared_ptr<PhysXDynamicActorComponent> DynamicActorComponent_;

	// 카메라 암
	std::shared_ptr<class CameraArm> CameraArm_;
	std::shared_ptr<class GameEngineCameraActor> CamActor_;

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
	void InputController();
	float4 MoveDir_;
};

