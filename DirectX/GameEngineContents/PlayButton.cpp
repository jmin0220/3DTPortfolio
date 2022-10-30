#include "PreCompile.h"
#include "PlayButton.h"

PlayButton::PlayButton() 
{
}

PlayButton::~PlayButton() 
{
}

void PlayButton::Start()
{
	Button = CreateComponent<GameEngineUIRenderer>();
	Button->SetTexture("Play.png");
	Button->GetTransform().SetWorldScale({ 350, 110});
	Button->GetTransform().SetWorldPosition({ 600,-380 });
}

void PlayButton::Update(float _DeltaTime)
{
}

