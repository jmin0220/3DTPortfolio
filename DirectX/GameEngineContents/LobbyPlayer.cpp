#include "PreCompile.h"
#include "LobbyPlayer.h"

LobbyPlayer::LobbyPlayer() 
{
}

LobbyPlayer::~LobbyPlayer() 
{
}

void LobbyPlayer::Start()
{
	FBXRenderer_ = CreateComponent<GameEngineFBXAnimationRenderer>();
	FBXRenderer_->SetFBXMesh("Character_Idle_A.fbx", "TextureAnimationCustom");
	SetCharacterAnimation();
	SetCharacterTexture();
}

void LobbyPlayer::Update(float _DeltaTime)
{
}

void LobbyPlayer::LevelStartEvent()
{
	FBXRenderer_->GetTransform().SetWorldScale({ 15,15,15 });
	//FBXRenderer_->GetTransform().SetWorldScale({ SIZE_MAGNIFICATION_RATIO });
}

// �ִϸ��̼� �ʱ�ȭ
void LobbyPlayer::SetCharacterAnimation()
{
	FBXRenderer_->CreateFBXAnimation("Idle",
		GameEngineRenderingEvent{ "Character_Idle_A.fbx", 0.016666666666666666666666666666666666666666667f , true }, 0);
	FBXRenderer_->CreateFBXAnimation("Win",
		GameEngineRenderingEvent{ "Character_Victory_Default_A.fbx", 0.016666666666666666666666666666666666666666667f , false }, 0);
	FBXRenderer_->CreateFBXAnimation("Fall",
		GameEngineRenderingEvent{ "Character_LobbyDive_A.fbx", 0.016666666666666666666666666666666666666666667f , true }, 0);
	FBXRenderer_->CreateFBXAnimation("Tumble",
		GameEngineRenderingEvent{ "Character_Fall_A.fbx", 0.016666666666666666666666666666666666666666667f , true }, 0);
	FBXRenderer_->CreateFBXAnimation("Jogging",
		GameEngineRenderingEvent{ "Character_JoggingOnSpot.fbx", 0.018f , true }, 0);
	FBXRenderer_->CreateFBXAnimation("Gasp",
		GameEngineRenderingEvent{ "Character_Victory_Gasp.fbx", 0.018f , true }, 0);
	FBXRenderer_->ChangeAnimation("Idle");
}

void LobbyPlayer::ChangeAnimationIdle()
{
	FBXRenderer_->ChangeAnimation("Idle");
}

void LobbyPlayer::ChangeAnimationWin()
{
	FBXRenderer_->ChangeAnimation("Win");
}

void LobbyPlayer::ChangeAnimationFall()
{
	FBXRenderer_->ChangeAnimation("Fall");
}

void LobbyPlayer::ChangeAnimationTumbel()
{
	FBXRenderer_->ChangeAnimation("Tumble");
}

void LobbyPlayer::ChangeAnimationJogging()
{
	FBXRenderer_->ChangeAnimation("Jogging");
}

void LobbyPlayer::ChangeAnimationGasp()
{
	FBXRenderer_->ChangeAnimation("Gasp");
}
// �ؽ�ó ����
// ĳ���� ��Ų
void LobbyPlayer::SetCharacterTexture()
{
	SkinData_.BodyColor = float4(0.93f, 0.21f, 0.54f);
	{
		std::vector<std::vector<GameEngineRenderUnit>>& RenderUnits = FBXRenderer_->GetAllRenderUnit();
		for (std::vector<GameEngineRenderUnit>& RenderUnit : RenderUnits)
		{
			for (GameEngineRenderUnit& Unit : RenderUnit)
			{
				// �ؽ���(�Ͼ�� ����)
				Unit.ShaderResources.SetTexture("DiffuseTexture", "CH_FallGuy_AM.png");

				// �� ����(�ϴ��� ���� ���� ����)
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

