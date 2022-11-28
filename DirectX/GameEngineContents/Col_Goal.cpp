#include "PreCompile.h"
#include "Col_Goal.h"

Col_Goal::Col_Goal() 
{
}

Col_Goal::~Col_Goal() 
{
}

void Col_Goal::Start()
{
	GoalCol_ = CreateComponent<GameEngineCollision>();
}

void Col_Goal::Update(float _DeltaTime)
{
}

void Col_Goal::End()
{
}

void Col_Goal::LevelStartEvent()
{
	GoalCol_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
}
