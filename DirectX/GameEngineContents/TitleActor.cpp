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
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->GetTransform().SetLocalScale({ 836, 572, 1 });
	Renderer->SetPivot(PIVOTMODE::CENTER);

	Renderer->SetTexture("Logo.png");
}

void TitleActor::Update(float _DeltaTime)
{
}

