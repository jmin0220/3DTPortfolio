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
		Renderer->CreateFBXAnimation("Vic", FBX_NAME_CHARACTER_VICTORY);
		Renderer->ChangeAnimation("Vic");
	//	Renderer->GetTransform().SetWorldScale({ 10.0f, 10.0f, 10.0f });

		Renderer->GetFBXMesh()->GetRenderUnit(0);
	}

	//
}

void TestCharacterAnimation::Update(float _DeltaTime)
{
}

