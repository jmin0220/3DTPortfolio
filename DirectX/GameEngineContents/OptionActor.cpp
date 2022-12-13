#include "PreCompile.h"
#include "OptionActor.h"

OptionActor::OptionActor() 
{
}

OptionActor::~OptionActor() 
{
}

void OptionActor::Start()
{
	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetTexture("OptionUI.png");
	Renderer_->GetTransform().SetWorldScale({838,783});
	//Renderer_->GetTransform().SetWorldPosition({380.0f,-10});
}

void OptionActor::Update(float _DeltaTime)
{
}

void OptionActor::LevelStartEvent()
{
}

void OptionActor::LevelEndEvent()
{
}
