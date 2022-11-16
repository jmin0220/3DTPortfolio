#include "PreCompile.h"
#include "PlayerActor.h"

#include "CameraArm.h"

float SPEED_PLAYER = 100.0f;

PlayerActor::PlayerActor() 
{
}

PlayerActor::~PlayerActor() 
{
}


void PlayerActor::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxControllerManager* _CtrManager)
{
	CCTActorComponent_->CreatePhysXActors(_Scene, _physics, _CtrManager);
}

void PlayerActor::Start()
{
	// 캐릭터 메쉬 로드 테스트용
	FbxRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	CCTActorComponent_ = CreateComponent<PhysXCCTActorComponent>();

	CamActor_ = GetLevel()->GetMainCameraActor();
	CameraArm_ = GetLevel()->CreateActor<CameraArm>();
	CameraArm_->SetFollowCamera(CamActor_, std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()));

	// FSM
	CreateFSMStates();
}

void PlayerActor::Update(float _DeltaTime)
{
	InputController();

	PlayerStateManager_.Update(_DeltaTime);

	GetTransform().SetWorldMove(MoveDir_ * SPEED_PLAYER * _DeltaTime);
}

void PlayerActor::LevelStartEvent()
{
	// 메쉬 로드
	FbxRenderer_->SetFBXMesh("Character.FBX", "Texture");
	FbxRenderer_->GetTransform().SetWorldScale({ SIZE_MAGNIFICATION_RATIO });
}

void PlayerActor::InputController()
{
	MoveDir_ = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress(KEY_W))
	{
		// EX) 카메라가 보고있는 방향으로 전진
		// MoveDir_ += GetLevel()->GetMainCameraActor()->GetTransform().GetForwardVector();
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_A))
	{
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_S))
	{
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_D))
	{
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_SPACEBAR))
	{
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOUSELEFT))
	{
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOUSERIGHT))
	{
	}

}
