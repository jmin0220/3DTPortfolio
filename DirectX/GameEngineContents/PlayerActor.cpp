#include "PreCompile.h"
#include "PlayerActor.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "StageParentLevel.h"
#include "VirtualPhysXLevel.h"

#include "CameraArm.h"

float SPEED_PLAYER = 4000.0f;

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
	// 캐릭터 메쉬 로드 테스트용
	FbxRenderer_ = CreateComponent<GameEngineFBXAnimationRenderer>();
	DynamicActorComponent_ = CreateComponent<PhysXDynamicActorComponent>();


	//EventCol
	EventCol_ = CreateComponent<GameEngineCollision>();
	EventCol_->ChangeOrder(CollisionGroup::Player);
	EventCol_->GetTransform().SetWorldScale({ PLAYER_COL_SCALE });
	EventCol_->GetTransform().SetLocalPosition({ 0,2.0f,0 });


	// FSM
	CreateFSMStates();

	// TODO::충격테스트용 키
	if (false == GameEngineInput::GetInst()->IsKey("ImpulsW"))
	{
		GameEngineInput::GetInst()->CreateKey("ImpulsW", VK_UP);
		GameEngineInput::GetInst()->CreateKey("ImpulsA", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("ImpulsS", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("ImpulsD", VK_RIGHT);

		//체크포인트 실험용
		GameEngineInput::GetInst()->CreateKey("TestPos", 'J');
	}
}

void PlayerActor::Update(float _DeltaTime)
{
	InputController(_DeltaTime);

	PlayerStateManager_.Update(_DeltaTime);

	//GetTransform().SetWorldMove(MoveDir_ * SPEED_PLAYER * _DeltaTime);
	// TODO::충격테스트코드
	ImpulseTest();


	//체크포인트 실험용
	if (GameEngineInput::GetInst()->IsDown("TestPos") == true)
	{
		DynamicActorComponent_->SetPlayerStartPos(ResetCheckPointPos());
	}
}

void PlayerActor::LevelStartEvent()
{
	// 메쉬 로드
	//FbxRenderer_->SetFBXMesh("Character.FBX", "Texture");
	FbxRenderer_->SetFBXMesh("TestIdle.fbx", "TextureAnimationCustom");
	SetCharacterAnimation();
	SetCharacterTexture();
	FbxRenderer_->GetTransform().SetWorldScale({ PLAYER_SIZE_MAGNIFICATION_RATIO });

	MeshBoundScale = FbxRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	MeshBoundScale *= float4{ PLAYER_SIZE_MAGNIFICATION_RATIO };
	//FbxRenderer_->GetTransform().SetLocalPosition({0.0f, -MeshBoundScale.y * 1.5f , 0.0f});
	FbxRenderer_->GetTransform().SetLocalPosition({0.0f, 0.0f , 0.0f});

	// 플레이어를 생성하고, 플레이어의 RigidActor를 받아와서 콜백에 사용함
	static_cast<VirtualPhysXLevel*>(GetLevel())->SetSimulationPlayer(CreatePhysXActors(dynamic_cast<StageParentLevel*>(GetLevel())->GetScene(),
		dynamic_cast<StageParentLevel*>(GetLevel())->GetPhysics()));

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

// TODO::물리 충격 테스트
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

float4 PlayerActor::ResetCheckPointPos()
{
	float4 Pos = CheckPointPos_;
	Pos.x = Pos.x + GameEngineRandom::MainRandom.RandomFloat(-20.0f, 20.0f);
	return Pos;
}


// 애니메이션 초기화
void PlayerActor::SetCharacterAnimation()
{
	FbxRenderer_->CreateFBXAnimation("Idle",
	GameEngineRenderingEvent{ "TestIdle.fbx", 0.016666666666666666666666666666666666666666667f , true }, 0);

	FbxRenderer_->ChangeAnimation("Idle");
}

// 캐릭터 스킨
void PlayerActor::SetCharacterTexture()
{
	SkinData_.BodyColor = float4(0.37f, 0.64f, 0.91f);
	{
		std::vector<std::vector<GameEngineRenderUnit>>& RenderUnits = FbxRenderer_->GetAllRenderUnit();
		for (std::vector<GameEngineRenderUnit>& RenderUnit : RenderUnits)
		{
			for (GameEngineRenderUnit& Unit : RenderUnit)
			{
				// 텍스쳐
				Unit.ShaderResources.SetTexture("DiffuseTexture", "CH_FallGuy_AM.png");

				// 색 정보
				if (true == Unit.ShaderResources.IsConstantBuffer("DiffuseData"))
				{
					Unit.ShaderResources.SetConstantBufferLink("DiffuseData", SkinData_);
				}

				// 마스킹
				if (true == Unit.ShaderResources.IsTexture("FaceEyeMskTexture"))
				{
					Unit.ShaderResources.SetTexture("FaceEyeMskTexture", "CH_FallGuy_faceEyes_MSK.png");
				}

				// 스킨
				if (true == Unit.ShaderResources.IsTexture("BodyMskTexture"))
				{
					Unit.ShaderResources.SetTexture("BodyMskTexture", "CH_FallGuy_BackToFrontGradient_PTN.png");
				}

				// 노말맵 + 빛
				if (true == Unit.ShaderResources.IsTexture("NormalTexture"))
				{
					Unit.ShaderResources.SetTexture("NormalTexture", "CH_FallGuy_NM.png");
				}

			}
		}
	}
}

