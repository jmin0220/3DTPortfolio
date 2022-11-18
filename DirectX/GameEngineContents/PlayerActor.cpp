#include "PreCompile.h"
#include "PlayerActor.h"

#include "CameraArm.h"

float SPEED_PLAYER = 400000.0f;

PlayerActor::PlayerActor() 
{
}

PlayerActor::~PlayerActor() 
{
}


void PlayerActor::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	DynamicActorComponent_->CreatePhysXActors(_Scene, _physics);
}

void PlayerActor::Start()
{
	// 캐릭터 메쉬 로드 테스트용
	FbxRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	DynamicActorComponent_ = CreateComponent<PhysXDynamicActorComponent>();

	CamActor_ = GetLevel()->GetMainCameraActor();
	CameraArm_ = GetLevel()->CreateActor<CameraArm>();
	CameraArm_->SetFollowCamera(CamActor_, std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()));

	// FSM
	CreateFSMStates();
}

void PlayerActor::Update(float _DeltaTime)
{
	InputController(_DeltaTime);

	PlayerStateManager_.Update(_DeltaTime);

	GetTransform().SetWorldMove(MoveDir_ * SPEED_PLAYER * _DeltaTime);
}

void PlayerActor::LevelStartEvent()
{
	// 메쉬 로드
	FbxRenderer_->SetFBXMesh("Character.FBX", "Texture");
	FbxRenderer_->GetTransform().SetWorldScale({ 3,3,3 });
}

void PlayerActor::InputController(float _DeltaTime)
{
	float4 tmpMoveSpeed = float4::ZERO;
	MoveDir_ = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress(KEY_W))
	{
		// EX) 카메라가 보고있는 방향으로 전진
		MoveDir_ += GetTransform().GetForwardVector();
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_A))
	{
		MoveDir_ += GetTransform().GetLeftVector();
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_S))
	{
		MoveDir_ += GetTransform().GetBackVector();
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_D))
	{
		MoveDir_ += GetTransform().GetRightVector();
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_SPACEBAR))
	{
		DynamicActorComponent_->SetMoveJump();
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOUSELEFT))
	{
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOUSERIGHT))
	{
	}

	if (true == MoveDir_.IsNearlyZero())
	{
		// TODO::실제로는 무언가와 충돌했을때 호출
		//DynamicActorComponent_->SetDynamicIdle();

		return;
	}

	// 2개 이상의 키가 동시에 눌리면 문제가 발생하므로 노말라이즈
	MoveDir_.Normalize3D();
	// TODO::바닥의 마찰을 무시할 수 있도록
	MoveDir_ += {0.0f, 0.001f, 0.0f};

	tmpMoveSpeed = MoveDir_ * SPEED_PLAYER * _DeltaTime;
	DynamicActorComponent_->SetMoveSpeed(tmpMoveSpeed);
}
