#include "PreCompile.h"
#include "PickableActor.h"
#include <GameEngineCore/CoreMinimal.h>

#include "ActorPicker.h"

GameEngineCollision* PickableActor::CurPicking_Collision = nullptr;

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
			if (true == GameEngineInput::GetInst()->IsDown("VK_LBUTTON"))
			{
				if (CurPicking_Collision == nullptr)
				{
					CurPicking_Collision = _This;
				}

				//다른 액터의 콜리전이 선택됐다면.
				if (CurPicking_Collision != _This)
				{
					if (_This->GetOrder() == static_cast<int>(CollisionGroup::Picking))
					{
						CurPicking_Collision->On();
					}


					CurPicking_Collision = _This;
				}
			}

			ActorPicker::PickedActors.insert(this);

			return CollisionReturn::ContinueCheck;
		});

	if (false == Pickable)
	{
		ActorPicker::PickedActors.erase(this);
	}
}