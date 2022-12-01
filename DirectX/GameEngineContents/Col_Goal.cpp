#include "PreCompile.h"
#include "Col_Goal.h"
#include "PlayerActor.h"

Col_Goal::Col_Goal() 
{
}

Col_Goal::~Col_Goal() 
{
}

void Col_Goal::Start()
{
	GoalCol_ = CreateComponent<GameEngineCollision>();
	GoalCol_->ChangeOrder(CollisionGroup::Trigger);
}

void Col_Goal::Update(float _DeltaTime)
{
	GoalCol_->IsCollision(CollisionType::CT_OBB, CollisionGroup::Player, CollisionType::CT_OBB,
		std::bind(&Col_Goal::CheckCol, this, std::placeholders::_1, std::placeholders::_2));
}

void Col_Goal::End()
{
}

void Col_Goal::LevelStartEvent()
{
	GoalCol_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
}

CollisionReturn Col_Goal::CheckCol(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	if (_Other->GetActor()->CastThis<PlayerActor>()->GetIsGoal() == false)
	{
		std::shared_ptr<PlayerActor> Player_ = _Other->GetActor()->CastThis<PlayerActor>();

		Player_->SetIsGoal(); //true

	}

	return CollisionReturn::Break;
}
