#include "PreCompile.h"
#include "Col_Trigger.h"

Col_Trigger::Col_Trigger() 
{
}

Col_Trigger::~Col_Trigger() 
{
}

void Col_Trigger::Start()
{
	TriggerCol_ = CreateComponent<GameEngineCollision>();
}

void Col_Trigger::Update(float _DeltaTime)
{
}

void Col_Trigger::End()
{
}

void Col_Trigger::LevelStartEvent()
{
	TriggerCol_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
}
