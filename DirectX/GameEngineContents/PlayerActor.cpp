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
	// ĳ���� �޽� �ε� �׽�Ʈ��
	FbxRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	DynamicActorComponent_ = CreateComponent<PhysXDynamicActorComponent>();

	CamActor_ = GetLevel()->GetMainCameraActor();
	CameraArm_ = GetLevel()->CreateActor<CameraArm>();
	CameraArm_->SetFollowCamera(CamActor_, std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()));


	//EventCol
	EventCol_ = CreateComponent<GameEngineCollision>();
	EventCol_->ChangeOrder(CollisionGroup::Player);
	EventCol_->GetTransform().SetWorldScale({ PLAYER_COL_SCALE });
	EventCol_->GetTransform().SetLocalPosition({ 0,2.0f,0 });


	// FSM
	CreateFSMStates();

	// TODO::����׽�Ʈ�� Ű
	if (false == GameEngineInput::GetInst()->IsKey("ImpulsW"))
	{
		GameEngineInput::GetInst()->CreateKey("ImpulsW", VK_UP);
		GameEngineInput::GetInst()->CreateKey("ImpulsA", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("ImpulsS", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("ImpulsD", VK_RIGHT);
	}
}

void PlayerActor::Update(float _DeltaTime)
{
	InputController(_DeltaTime);

	PlayerStateManager_.Update(_DeltaTime);

	GetTransform().SetWorldMove(MoveDir_ * SPEED_PLAYER * _DeltaTime);

	// TODO::����׽�Ʈ�ڵ�
	ImpulseTest();
}

void PlayerActor::LevelStartEvent()
{
	// �޽� �ε�
	FbxRenderer_->SetFBXMesh("Character.FBX", "Texture");
	FbxRenderer_->GetTransform().SetWorldScale({ 3,3,3 });
}

void PlayerActor::LevelEndEvent()
{
	CameraArm_->Off();
}

void PlayerActor::InputController(float _DeltaTime)
{
	float4 tmpMoveSpeed = float4::ZERO;
	MoveDir_ = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress(KEY_W))
	{
		// EX) ī�޶� �����ִ� �������� ����
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

	if (true == GameEngineInput::GetInst()->IsDown(KEY_SPACEBAR))
	{

		DynamicActorComponent_->SetMoveJump();

		//static bool tmp = true;
		//if (true == tmp)
		//{
		//	DynamicActorComponent_->SetlockAxis();
		//	tmp = false;
		//}
		//else
		//{
		//	DynamicActorComponent_->SetUnlockAxis();
		//	tmp = true;
		//}
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOUSELEFT))
	{
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOUSERIGHT))
	{
	}

	if (true == MoveDir_.IsNearlyZero())
	{
		// TODO::�����δ� ���𰡿� �浹������ ȣ��
		//DynamicActorComponent_->SetDynamicIdle();

		return;
	}

	// 2�� �̻��� Ű�� ���ÿ� ������ ������ �߻��ϹǷ� �븻������
	MoveDir_.Normalize3D();
	// TODO::�ٴ��� ������ ������ �� �ֵ���
	MoveDir_ += {0.0f, 0.001f, 0.0f};

	tmpMoveSpeed = MoveDir_ * SPEED_PLAYER * _DeltaTime;
	DynamicActorComponent_->SetMoveSpeed(tmpMoveSpeed);
}

// TODO::���� ��� �׽�Ʈ
void PlayerActor::ImpulseTest()
{
	float4 tmpPower = float4::ZERO;
	float tmpImpulse = 2.5f;
	
	if (true == GameEngineInput::GetInst()->IsPress("ImpulsW"))
	{
		tmpPower = { 0.0f, 0.0f, tmpImpulse };
	}
	if (true == GameEngineInput::GetInst()->IsPress("ImpulsA"))
	{
		tmpPower = { -tmpImpulse, 0.0f, 0.0f };
	}
	if (true == GameEngineInput::GetInst()->IsPress("ImpulsS"))
	{
		tmpPower = { 0.0f, 0.0f, -tmpImpulse };
	}
	if (true == GameEngineInput::GetInst()->IsPress("ImpulsD"))
	{
		tmpPower = { tmpImpulse, 0.0f, 0.0f };
	}

	if (true == tmpPower.IsNearlyZero())
	{
		return;
	}

	DynamicActorComponent_->PushImpulse(tmpPower);
}