#include "PreCompile.h"
#include "BigShots_Cannon.h"
#include "BigShots_PRP.h"
#include "BigShots_Puff.h"
#include <GameEngineBase/GameEngineRandom.h>

BigShots_Cannon::BigShots_Cannon() 
	: ShootingTime_(5.0f)
{
}

BigShots_Cannon::~BigShots_Cannon() 
{
}

void BigShots_Cannon::Start()
{
	FbxRenderer_ = CreateComponent<GameEngineFBXAnimationRenderer>();
	FbxFloatingRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	FbxSpinnerRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
}

void BigShots_Cannon::Update(float _DeltaTime)
{
	if (0.0f >= ShootingTime_)
	{
		FbxRenderer_->ChangeAnimation("Idle");
		ShootingTime_ = 10.0f;
		return;
	}
	else
	{
		ShootingTime_ -= _DeltaTime;
	}
	
	FbxRenderer_->CastThis<GameEngineFBXAnimationRenderer>()->GetCurAni()->bOnceEnd = false;
	FbxRenderer_->AnimationBindFrame("Idle", [=](const GameEngineRenderingEvent& _Info)
		{
			if (_Info.CurFrame == 3)
			{
				//연기 효과
				std::shared_ptr<GameEngineActor> Puff = GetLevel()->CreateActor<BigShots_Puff>();
				Puff->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{ 0.0f,0.0f,30.0f });

				std::shared_ptr<BigShots_PRP> PRP = GetLevel()->CreateActor<BigShots_PRP>();
				PRP->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4{ 0.0f,0.0f,15.0f });
				PRP->CreatePhysX();

				GameEngineRandom RandomValue_;
				float RandomFloatNum = GameEngineRandom::MainRandom.RandomFloat(2.0f, 3.0f);

				ShootingTime_ = RandomFloatNum;
			}
		});
}

void BigShots_Cannon::LevelStartEvent()
{
	FbxRenderer_->SetFBXMesh("PRP_CanonLip.fbx", "TextureAnimation");

	FbxRenderer_->CreateFBXAnimation("Idle",
		GameEngineRenderingEvent{ "PRP_CanonLip.fbx", ANIMATION_FRAME_TIME , false }, 0);
	FbxRenderer_->ChangeAnimation("Idle");

	
	//std::vector<std::vector<GameEngineRenderUnit>>& RenderUnits = FbxRenderer_->GetAllRenderUnit();
	std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& RenderUnits = FbxRenderer_->GetAllRenderUnit();

	for (std::vector<std::shared_ptr<GameEngineRenderUnit>>& RenderUnit : RenderUnits)
	{
		for (std::shared_ptr<GameEngineRenderUnit>& Unit : RenderUnit)
		{
			// 텍스쳐
			Unit->ShaderResources.SetTexture("DiffuseTexture", "PRP_S04_Cannon_AM.png");
		}
	}
	FbxRenderer_->GetTransform().SetWorldScale({ 2.5f,2.5f,2.5f });

	FbxFloatingRenderer_->SetFBXMesh("ENV_S04_FloatingCannonTubes.fbx", "Texture");
	FbxFloatingRenderer_->GetTransform().SetWorldRotation(GetTransform().GetWorldRotation() + float4(10.0f, 0.0f, 0.0f));

	FbxSpinnerRenderer_->SetFBXMesh("ENV_S04_Spinner.fbx", "Texture");
	FbxSpinnerRenderer_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + float4(0.0f, 40.0f, 0.0f));
	FbxSpinnerRenderer_->GetTransform().SetWorldRotation(GetTransform().GetWorldRotation() + float4(10.0f, 0.0f, 0.0f));
}

void BigShots_Cannon::LevelEndEvent()
{
}
