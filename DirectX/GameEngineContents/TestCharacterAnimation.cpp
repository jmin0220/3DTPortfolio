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

		{
			Renderer->CreateFBXAnimation("Idle", 
				GameEngineRenderingEvent{ "TestIdle.fbx", 0.016666666666666666666666666666666666666666667f , true }, 0);
		}

		{
			GameEngineRenderingEvent Event;
			Event.ResourcesName = "TestWalk.fbx";
			Event.Loop = true;
			Event.Inter = 0.016666666666666666666666666666666666666666667f;
			Renderer->CreateFBXAnimation("Walk", Event, 0);
		}

		{
			GameEngineRenderingEvent Event;
			Event.ResourcesName = "TestRun.fbx";
			Event.Loop = true;
			Event.Inter = 0.016666666666666666666666666666666666666666667f;
			Renderer->CreateFBXAnimation("Run", Event, 0);
		}

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

