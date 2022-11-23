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
}

void LobbyPlayer::Update(float _DeltaTime)
{
}

void LobbyPlayer::LevelStartEvent()
{
	FBXRenderer_ = CreateComponent<GameEngineFBXAnimationRenderer>();
	FBXRenderer_->SetFBXMesh("Character.fbx", "TextureAnimation");
	FBXRenderer_->CreateFBXAnimation("Idle", GameEngineRenderingEvent{ "Character.fbx", 0.016666666666666666666666666666666666666666667f , true }, 0);
	FBXRenderer_->ChangeAnimation("Idle");
	FBXRenderer_->GetTransform().SetWorldScale({ 15,15,15 });
	//FBXRenderer_->GetTransform().SetWorldScale({ SIZE_MAGNIFICATION_RATIO });


	{
		std::vector<std::vector<GameEngineRenderUnit>>& Units = FBXRenderer_->GetAllRenderUnit();

		for (std::vector<GameEngineRenderUnit>& UnitSet : Units)
		{
			for (GameEngineRenderUnit& Unit : UnitSet)
			{
				Unit.ShaderResources.SetTexture("DiffuseTexture", "Character.png");
			}
		}
	}
}
