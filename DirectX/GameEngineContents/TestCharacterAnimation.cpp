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
		Renderer = CreateComponent<GameEngineFBXAnimationRenderer>();
		Renderer->SetFBXMesh("TestIdle.fbx", "TextureAnimation");
		Renderer->CreateFBXAnimation("Idle", "TestIdle.fbx");
		Renderer->CreateFBXAnimation("Walk", "TestWalk.fbx");
		Renderer->CreateFBXAnimation("Run", "TestRun.fbx");
		Renderer->ChangeAnimation("Idle");
		GetTransform().SetWorldScale({ SIZE_MAGNIFICATION_RATIO });
		GetTransform().SetWorldRotation({ 0.0f, 180.0f, 0.0f });
	}

	{
		std::vector<std::vector<GameEngineRenderUnit>>& RenderUnits = Renderer->GetAllRenderUnit();
		for (std::vector<GameEngineRenderUnit>& RenderUnit : RenderUnits)
		{
			for (GameEngineRenderUnit& Unit : RenderUnit)
			{
				Unit.ShaderResources.SetTexture("DiffuseTexture", "CH_FallGuy_AM.png");
				//Unit.ShaderResources.SetTexture("DiffuseTexture", "CH_FallGuy_NM.png");
			}
		}
	}
	if (GameEngineInput::GetInst()->IsKey("1") == false)
	{
		GameEngineInput::GetInst()->CreateKey("1", '1');
		GameEngineInput::GetInst()->CreateKey("2", '2');
		GameEngineInput::GetInst()->CreateKey("3", '3');
		GameEngineInput::GetInst()->CreateKey("4", '4');
		GameEngineInput::GetInst()->CreateKey("5", '5');
	}

}

void TestCharacterAnimation::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("1") == true)
	{
		Renderer->ChangeAnimation("Idle");
	}

	if (GameEngineInput::GetInst()->IsDown("2") == true)
	{
		Renderer->ChangeAnimation("Walk");
	}
	if (GameEngineInput::GetInst()->IsDown("3") == true)
	{
		Renderer->ChangeAnimation("Run");
	}
}

