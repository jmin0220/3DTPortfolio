#include "PreCompile.h"
#include "BigShots_Cannon.h"

BigShots_Cannon::BigShots_Cannon() 
{
}

BigShots_Cannon::~BigShots_Cannon() 
{
}

void BigShots_Cannon::Start()
{
	FbxRenderer_ = CreateComponent<GameEngineFBXAnimationRenderer>();
}

void BigShots_Cannon::Update(float _DeltaTime)
{
}

void BigShots_Cannon::LevelStartEvent()
{
	FbxRenderer_->SetFBXMesh("PRP_CanonLip.fbx", "TextureAnimation");

	FbxRenderer_->CreateFBXAnimation("Idle",
		GameEngineRenderingEvent{ "PRP_CanonLip.fbx", 0.1f , true }, 0);
	FbxRenderer_->ChangeAnimation("Idle");

	std::vector<std::vector<GameEngineRenderUnit>>& RenderUnits = FbxRenderer_->GetAllRenderUnit();
	for (std::vector<GameEngineRenderUnit>& RenderUnit : RenderUnits)
	{
		for (GameEngineRenderUnit& Unit : RenderUnit)
		{
			// ÅØ½ºÃÄ
			Unit.ShaderResources.SetTexture("DiffuseTexture", "PRP_S04_Cannon_AM.png");
		}
	}
	//FbxRenderer_->GetTransform().SetWorldScale({ 3,3,3 });
}

void BigShots_Cannon::LevelEndEvent()
{
}
