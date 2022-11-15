#include "PreCompile.h"
#include "TestCharacterAnimation.h"

TestCharacterAnimation::TestCharacterAnimation() 
{
}

TestCharacterAnimation::~TestCharacterAnimation() 
{
}

void TestCharacterAnimation::Start()
{
	//GameEngineTime::GetInst()->SetTimeScale();
	{
		std::shared_ptr<GameEngineFBXAnimationRenderer> Renderer = CreateComponent<GameEngineFBXAnimationRenderer>();
		Renderer->SetFBXMesh(FBX_NAME_CHARACTER_RUN, "TextureAnimation");
		Renderer->CreateFBXAnimation("Run", FBX_NAME_CHARACTER_RUN);
		//Renderer->CreateFBXAnimation("Vic", FBX_NAME_CHARACTER_VICTORY);
		Renderer->ChangeAnimation("Run");
		GetTransform().SetWorldScale({SIZE_MAGNIFICATION_RATIO});
		std::vector<std::vector<GameEngineRenderUnit>> Units = Renderer->GetAllRenderUnit();
		Units[0][0].ShaderResources.SetTexture("DiffuseTexture", "CH_Tanager_AM.png");
		Units[1][0].ShaderResources.SetTexture("DiffuseTexture", "CH_Tanager_AM.png");
		Units[2][0].ShaderResources.SetTexture("DiffuseTexture", "CH_Tanager_AM.png");
		Units[3][0].ShaderResources.SetTexture("DiffuseTexture", "CH_Tanager_AM.png");
		FbxExMaterialSettingData Data = Renderer->GetFBXMesh()->GetMaterialSettingData(0,0);
	//	Renderer->GetTransform().SetWorldScale({ 10.0f, 10.0f, 10.0f });

		Renderer->GetFBXMesh()->GetRenderUnit(0);
	}

	//
}

void TestCharacterAnimation::Update(float _DeltaTime)
{
}

