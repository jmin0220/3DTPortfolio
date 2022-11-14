#include "PreCompile.h"
#include "PickableActor.h"
#include <GameEngineCore/CoreMinimal.h>

#include "ActorPicker.h"

std::weak_ptr<GameEngineCollision> PickableActor::CurPicking_Collision;

PickableActor::PickableActor()
{
}

PickableActor::~PickableActor() 
{
}

void PickableActor::CreatePickingCollision(float4 Scale = {100.0f,100.0f,100.0f}, float4 Position = {0,0,0})
{
	Collision_Picking = CreateComponent<GameEngineCollision>();
	Collision_Picking.lock()->GetTransform().SetWorldScale(Scale);
	Collision_Picking.lock()->GetTransform().SetWorldPosition(Position);
	Collision_Picking.lock()->ChangeOrder(CollisionGroup::Picking);
}


// ActorPicker에 나 충돌했어요 알려줌
void PickableActor::CheckPickingRay()
{
	if (nullptr == Collision_Picking.lock())
	{
		MsgBoxAssert("맵 에디터용 엑터에 피킹용 콜리전이 생성되지 않았습니다");
	}

	bool Pickable = Collision_Picking.lock()->IsCollision(CollisionType::CT_OBB, CollisionGroup::Ray, CollisionType::CT_OBB,
		[=](std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
		{
			if (true == GameEngineInput::GetInst()->IsDown("VK_LBUTTON"))
			{
				if (CurPicking_Collision.lock() == nullptr)
				{
					CurPicking_Collision = _This;
				}

				//다른 액터의 콜리전이 선택됐다면.
				if (CurPicking_Collision.lock() != _This)
				{
					if (_This->GetOrder() == static_cast<int>(CollisionGroup::Picking))
					{
						CurPicking_Collision.lock()->On();
					}


					CurPicking_Collision = _This;
				}
			}

			ActorPicker::PickedActors.insert(std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()));
			//ActorPicker::PickedActors.insert(std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()));

			return CollisionReturn::ContinueCheck;
		});

	if (false == Pickable)
	{
		ActorPicker::PickedActors.erase(std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()));
	}
}