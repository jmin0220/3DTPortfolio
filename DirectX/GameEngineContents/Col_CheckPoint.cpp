#include "PreCompile.h"
#include "PlayerActor.h"
#include "Col_CheckPoint.h"

Col_CheckPoint::Col_CheckPoint() :
	Check(false)
{
}

Col_CheckPoint::~Col_CheckPoint() 
{
}

void Col_CheckPoint::Start()
{
	CheckPointCol_ = CreateComponent<GameEngineCollision>();
	CheckPointCol_->ChangeOrder(CollisionGroup::CheckPoint);
}

void Col_CheckPoint::Update(float _DeltaTime)
{
	//DoorDash 체크포인트
	CheckPointCol_->IsCollision(CollisionType::CT_OBB, CollisionGroup::Player, CollisionType::CT_OBB ,
		std::bind(&Col_CheckPoint::CheckCol, this, std::placeholders::_1, std::placeholders::_2));
}

void Col_CheckPoint::End()
{
}

void Col_CheckPoint::LevelStartEvent()
{
	CheckPointCol_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
}

CollisionReturn Col_CheckPoint::CheckCol(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	if (_Other->GetActor()->CastThis<PlayerActor>()->GetFlag() == false)
	{
		std::shared_ptr<PlayerActor> Player_ = _Other->GetActor()->CastThis<PlayerActor>();

		Player_->SetCheckPoint(_This->GetTransform().GetWorldPosition());
		Player_->SetFlag(); //true
		
	}
	return CollisionReturn::Break;
}
