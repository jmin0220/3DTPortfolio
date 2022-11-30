#include "PreCompile.h"
#include "PlayerActor.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "StageParentLevel.h"
#include "VirtualPhysXLevel.h"

#include "CameraArm.h"

float SPEED_PLAYER = 2500.0f;

PlayerActor::PlayerActor() :
	CheckPointFlag_(false),
	CheckPointPos_(float4::ZERO)
{
}

PlayerActor::~PlayerActor() 
{
}


physx::PxRigidDynamic* PlayerActor::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{

	return DynamicActorComponent_->CreatePhysXActors(_Scene, _physics, 
		physx::PxVec3(MeshBoundScale.x, 
		MeshBoundScale.y, 
		MeshBoundScale.z));
}

void PlayerActor::Start()
{
	// ĳ���� �޽� �ε� �׽�Ʈ��
	FbxRenderer_ = CreateComponent<GameEngineFBXAnimationRenderer>();
	DynamicActorComponent_ = CreateComponent<PhysXDynamicActorComponent>();


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

		//üũ����Ʈ ����� ���߿� ��������
		GameEngineInput::GetInst()->CreateKey("StandUp", 'K');

		//üũ����Ʈ �����
		GameEngineInput::GetInst()->CreateKey("TestPos", 'J');
	}

	DynamicActorComponent_->TurnOnSpeedLimit();
}

void PlayerActor::Update(float _DeltaTime)
{
	InputController(_DeltaTime);

	PlayerStateManager_.Update(_DeltaTime);

	//GetTransform().SetWorldMove(MoveDir_ * SPEED_PLAYER * _DeltaTime);
	// TODO::����׽�Ʈ�ڵ�
	ImpulseTest();
	StandUp();


	//üũ����Ʈ ����� ���߿� ��������
	if (GameEngineInput::GetInst()->IsDown("TestPos") == true)
	{
		DynamicActorComponent_->SetPlayerStartPos(ResetCheckPointPos());
	}
}

void PlayerActor::LevelStartEvent()
{
	// �޽� �ε�
	//FbxRenderer_->SetFBXMesh("Character.FBX", "Texture");
	FbxRenderer_->SetFBXMesh("TestIdle.fbx", "TextureAnimationCustom");
	SetCharacterAnimation();
	SetCharacterTexture();
	FbxRenderer_->GetTransform().SetWorldScale({ PLAYER_SIZE_MAGNIFICATION_RATIO });

	MeshBoundScale = FbxRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	MeshBoundScale *= float4{ PLAYER_SIZE_MAGNIFICATION_RATIO };
	FbxRenderer_->GetTransform().SetLocalPosition({0.0f, -MeshBoundScale.y * 1.5f , 0.0f});
	//FbxRenderer_->GetTransform().SetLocalPosition({0.0f, 0.0f , 0.0f});

	// �÷��̾ �����ϰ�, �÷��̾��� RigidActor�� �޾ƿͼ� �ݹ鿡 �����
	static_cast<VirtualPhysXLevel*>(GetLevel())->SetSimulationPlayer(CreatePhysXActors(dynamic_cast<StageParentLevel*>(GetLevel())->GetScene(),
		dynamic_cast<StageParentLevel*>(GetLevel())->GetPhysics()));

	// LevelStartEvent���� �÷��̾ �����ϰ� ��ġ�� �������ϴ� �Լ�
	DynamicActorComponent_->SetPlayerStartPos(GetTransform().GetWorldPosition());


}

void PlayerActor::LevelEndEvent()
{
}

void PlayerActor::InputController(float _DeltaTime)
{


	float4 tmpMoveSpeed = float4::ZERO;
	MoveDir_ = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress(KEY_W))
	{
		// EX) ī�޶� �����ִ� �������� ����
		//MoveDir_ += GetTransform().Ge(tForwardVector();
		float4 InstMoveDir = GetLevel()->GetMainCameraActor()->GetTransform().GetForwardVector();
		InstMoveDir.y = 0;
		MoveDir_ += InstMoveDir.Normalize3DReturn();
		int a = 0;
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_A))
	{
		//MoveDir_ += GetTransform().GetLeftVector();
		//MoveDir_ += GetLevel()->GetMainCameraActor()->GetTransform().GetLeftVector();
		float4 InstMoveDir = GetLevel()->GetMainCameraActor()->GetTransform().GetLeftVector();
		InstMoveDir.y = 0;
		MoveDir_ += InstMoveDir.Normalize3DReturn();
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_S))
	{
		//MoveDir_ += GetTransform().GetBackVector();
		//MoveDir_ += GetLevel()->GetMainCameraActor()->GetTransform().GetBackVector();
		float4 InstMoveDir = GetLevel()->GetMainCameraActor()->GetTransform().GetBackVector();
		InstMoveDir.y = 0;
		MoveDir_ += InstMoveDir.Normalize3DReturn();
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_D))
	{
		//MoveDir_ += GetTransform().GetRightVector();
		//MoveDir_ += GetLevel()->GetMainCameraActor()->GetTransform().GetRightVector();
		float4 InstMoveDir = GetLevel()->GetMainCameraActor()->GetTransform().GetRightVector();
		InstMoveDir.y = 0;
		MoveDir_ += InstMoveDir.Normalize3DReturn();
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
	//MoveDir_ += {0.0f, 0.5f, 0.0f};

	tmpMoveSpeed = MoveDir_ * SPEED_PLAYER * _DeltaTime;
	DynamicActorComponent_->SetMoveSpeed(tmpMoveSpeed);
}

// TODO::���� ��� �׽�Ʈ
void PlayerActor::ImpulseTest()
{
	float4 tmpPower = float4::ZERO;
	float tmpImpulse = 1.0f;
	
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

float4 PlayerActor::ResetCheckPointPos()
{
	float4 Pos = CheckPointPos_;
	Pos.x = Pos.x + GameEngineRandom::MainRandom.RandomFloat(-20.0f, 20.0f);
	return Pos;
}


// �ִϸ��̼� �ʱ�ȭ
void PlayerActor::SetCharacterAnimation()
{
	FbxRenderer_->CreateFBXAnimation("Idle",
	GameEngineRenderingEvent{ "TestIdle.fbx", 0.016666666666666666666666666666666666666666667f , true }, 0);

	FbxRenderer_->CreateFBXAnimation("Run",
		GameEngineRenderingEvent{ "TestRun.fbx", 0.016666666666666666666666666666666666666666667f , true }, 0);

	FbxRenderer_->ChangeAnimation("Run");
}

// ĳ���� ��Ų
void PlayerActor::SetCharacterTexture()
{
	SkinData_.BodyColor = float4(0.37f, 0.64f, 0.91f);
	{
		std::vector<std::vector<GameEngineRenderUnit>>& RenderUnits = FbxRenderer_->GetAllRenderUnit();
		for (std::vector<GameEngineRenderUnit>& RenderUnit : RenderUnits)
		{
			for (GameEngineRenderUnit& Unit : RenderUnit)
			{
				// �ؽ���
				Unit.ShaderResources.SetTexture("DiffuseTexture", "CH_FallGuy_AM.png");

				// �� ����
				if (true == Unit.ShaderResources.IsConstantBuffer("DiffuseData"))
				{
					Unit.ShaderResources.SetConstantBufferLink("DiffuseData", SkinData_);
				}

				// ����ŷ
				if (true == Unit.ShaderResources.IsTexture("FaceEyeMskTexture"))
				{
					Unit.ShaderResources.SetTexture("FaceEyeMskTexture", "CH_FallGuy_faceEyes_MSK.png");
				}

				// ��Ų
				if (true == Unit.ShaderResources.IsTexture("BodyMskTexture"))
				{
					Unit.ShaderResources.SetTexture("BodyMskTexture", "CH_FallGuy_BackToFrontGradient_PTN.png");
				}

				// �븻�� + ��
				if (true == Unit.ShaderResources.IsTexture("NormalTexture"))
				{
					Unit.ShaderResources.SetTexture("NormalTexture", "CH_FallGuy_NM.png");
				}

			}
		}
	}
}

void PlayerActor::StandUp()
{

}