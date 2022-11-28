#include "PreCompile.h"
#include "Col_CheckPoint.h"

Col_CheckPoint::Col_CheckPoint() 
{
}

Col_CheckPoint::~Col_CheckPoint() 
{
}

void Col_CheckPoint::Start()
{
	CheckPointCol_ = CreateComponent<GameEngineCollision>();
}

void Col_CheckPoint::Update(float _DeltaTime)
{
}

void Col_CheckPoint::End()
{
}

void Col_CheckPoint::LevelStartEvent()
{
	CheckPointCol_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
}
