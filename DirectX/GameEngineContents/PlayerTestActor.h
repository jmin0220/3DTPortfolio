#pragma once
//#include "PhysXCCTActorComponent.h"
//#include "PhysXDynamicActorComponent.h"

// ���� :
class PlayerTestActor : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerTestActor();
	~PlayerTestActor();

	// delete Function
	PlayerTestActor(const PlayerTestActor& _Other) = delete;
	PlayerTestActor(PlayerTestActor&& _Other) noexcept = delete;
	PlayerTestActor& operator=(const PlayerTestActor& _Other) = delete;
	PlayerTestActor& operator=(PlayerTestActor&& _Other) noexcept = delete;

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelStartEvent() override;

private:
	std::shared_ptr<GameEngineFBXAnimationRenderer> FbxRenderer_;
	//std::shared_ptr<PhysXDynamicActorComponent> DynamicActorComponent_;

	// ī�޶� ��
	std::shared_ptr<class CameraArm> CameraArm_;
	std::shared_ptr<class GameEngineCameraActor> CamActor_;

	// FSM
private:
	//GameEngineStateManager PlayerStateManager_;

	//void CreateFSMStates();

	//// ���� ����
	//void IdleStart(const StateInfo& _Info);
	//void IdleUpdate(float _DeltaTime, const StateInfo& _Info);
	//void IdleEnd(const StateInfo& _Info);

	//void RunStart(const StateInfo& _Info);
	//void RunUpdate(float _DeltaTime, const StateInfo& _Info);
	//void RunEnd(const StateInfo& _Info);

	//void JumpStart(const StateInfo& _Info);
	//void JumpUpdate(float _DeltaTime, const StateInfo& _Info);
	//void JumpEnd(const StateInfo& _Info);

	// �Է�
	void InputController();
	float4 MoveDir_;
};

