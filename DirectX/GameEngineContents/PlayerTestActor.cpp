#include "PreCompile.h"
#include "PlayerTestActor.h"

#include "CameraArm.h"

PlayerTestActor::PlayerTestActor() 
{
}

PlayerTestActor::~PlayerTestActor() 
{
}


void PlayerTestActor::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	//DynamicActorComponent_->CreatePhysXActors(_Scene, _physics);
}

void PlayerTestActor::Start()
{
	// 캐릭터 메쉬 로드 테스트용
	{
		FbxRenderer_ = CreateComponent<GameEngineFBXAnimationRenderer>();
		FbxRenderer_->SetFBXMesh("TestIdle.fbx", "TextureAnimation");
		FbxRenderer_->CreateFBXAnimation("Idle",
			GameEngineRenderingEvent{ "TestIdle.fbx", 0.016666666666666666666666666666666666666666667f , true }, 0);

		FbxRenderer_->ChangeAnimation("Idle");
	}

	{
		std::vector<std::vector<GameEngineRenderUnit>>& RenderUnits = FbxRenderer_->GetAllRenderUnit();
		for (std::vector<GameEngineRenderUnit>& RenderUnit : RenderUnits)
		{
			for (GameEngineRenderUnit& Unit : RenderUnit)
			{
				Unit.ShaderResources.SetTexture("DiffuseTexture", "CH_FallGuy_AM.png");
				//Unit.ShaderResources.SetTexture("DiffuseTexture", "CH_FallGuy_NM.png");
			}
		}
	}
	//DynamicActorComponent_ = CreateComponent<PhysXDynamicActorComponent>();

	CamActor_ = GetLevel()->GetMainCameraActor();
	CameraArm_ = GetLevel()->CreateActor<CameraArm>();
	CameraArm_->SetFollowCamera(CamActor_, std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()));

	// FSM
	//CreateFSMStates();
}

void PlayerTestActor::Update(float _DeltaTime)
{
	InputController();

	//PlayerStateManager_.Update(_DeltaTime);

	GetTransform().SetWorldMove(MoveDir_ * 100.0f * _DeltaTime);
}

void PlayerTestActor::LevelStartEvent()
{
}

void PlayerTestActor::InputController()
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
