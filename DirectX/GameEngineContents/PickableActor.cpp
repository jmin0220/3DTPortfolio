#include "PreCompile.h"
#include "PickableActor.h"
#include <GameEngineCore/CoreMinimal.h>

#include "ActorPicker.h"

PickableActor::PickableActor() 
{
}

PickableActor::~PickableActor() 
{
}

void PickableActor::CreatePickingCollision(float4 Scale,float4 Position)
{
	Collision_Picking = CreateComponent<GameEngineCollision>();
	Collision_Picking->GetTransform().SetWorldScale(Scale);
	Collision_Picking->GetTransform().SetWorldPosition(Position);
	Collision_Picking->ChangeOrder(CollisionGroup::Picking);
}


// ActorPicker에 나 충돌했어요 알려줌
void PickableActor::CheckPickingRay()
{
	if (nullptr == Collision_Picking)
	{
		MsgBoxAssert("맵 에디터용 엑터에 피킹용 콜리전이 생성되지 않았습니다");
	}

	bool Pickable = Collision_Picking->IsCollision(CollisionType::CT_OBB, CollisionGroup::Ray, CollisionType::CT_OBB,
		[=](GameEngineCollision* _This, GameEngineCollision* _Other)
		{
			ActorPicker::PickedActors.insert(this);

			return CollisionReturn::ContinueCheck;
		});

	if (false == Pickable)
	{
		ActorPicker::PickedActors.erase(this);
	}
}