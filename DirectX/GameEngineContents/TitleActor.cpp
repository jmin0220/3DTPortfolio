#include "PreCompile.h"
#include "TitleActor.h"

TitleActor::TitleActor() 
{
}

TitleActor::~TitleActor() 
{
}

void TitleActor::Start()
{
	{
		Renderer2 = CreateComponent<GameEngineTextureRenderer>();
		Renderer2->GetTransform().SetLocalScale({ 1600, 900, 1 });
		Renderer2->SetPivot(PIVOTMODE::CENTER);
		Renderer2->GetTransform().SetLocalPosition({ -18,-82 });
				
		Renderer2->SetTexture("LobbySketch.png");
		Renderer2->Off();
	}

	{
		Logo = CreateComponent<GameEngineTextureRenderer>();
		Logo->GetTransform().SetLocalScale({ 836, 572, 1 });
		Logo->SetPivot(PIVOTMODE::CENTER);

		Logo->SetTexture("Logo.png");
	}

}

void TitleActor::Update(float _DeltaTime)
{
}

