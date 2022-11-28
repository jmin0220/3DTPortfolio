#include "PreCompile.h"
#include "Col_StartPos.h"

Col_StartPos::Col_StartPos() 
{
}

Col_StartPos::~Col_StartPos() 
{
}

void Col_StartPos::Start()
{
	StartCol_ = CreateComponent<GameEngineCollision>();
}

void Col_StartPos::Update(float _DeltaTime)
{

}

void Col_StartPos::End()
{
}

void Col_StartPos::LevelStartEvent()
{
	StartCol_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
}
