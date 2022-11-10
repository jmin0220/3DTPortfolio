#include "PreCompile.h"
#include "PickableActor.h"
#include <GameEngineCore/CoreMinimal.h>

#include "ActorPicker.h"

std::shared_ptr<GameEngineCollision> PickableActor::CurPicking_Collision = nullptr;

PickableActor::PickableActor()
{
}

PickableActor::~PickableActor() 
{
}

void PickableActor::CreatePickingCollision(float4 Scale = {100.0f,100.0f,100.0f}, float4 Position = {0,0,0})
{
	Collision_Picking = CreateComponent<GameEngineCollision>();
	Collision_Picking->GetTransform().SetWorldScale(Scale);
	Collision_Picking->GetTransform().SetWorldPosition(Position);
	Collision_Picking->ChangeOrder(CollisionGroup::Picking);
}


// ActorPicker�� �� �浹�߾�� �˷���
void PickableActor::CheckPickingRay()
{
	if (nullptr == Collision_Picking)
	{
		MsgBoxAssert("�� �����Ϳ� ���Ϳ� ��ŷ�� �ݸ����� �������� �ʾҽ��ϴ�");
	}

	bool Pickable = Collision_Picking->IsCollision(CollisionType::CT_OBB, CollisionGroup::Ray, CollisionType::CT_OBB,
		[=](std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
		{
			if (true == GameEngineInput::GetInst()->IsDown("VK_LBUTTON"))
			{
				if (CurPicking_Collision == nullptr)
				{
					CurPicking_Collision = _This;
				}

				//�ٸ� ������ �ݸ����� ���õƴٸ�.
				if (CurPicking_Collision != _This)
				{
					if (_This->GetOrder() == static_cast<int>(CollisionGroup::Picking))
					{
						CurPicking_Collision->On();
					}


					CurPicking_Collision = _This;
				}
			}

			ActorPicker::PickedActors.insert(std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()));

			return CollisionReturn::ContinueCheck;
		});

	if (false == Pickable)
	{
		ActorPicker::PickedActors.erase(std::dynamic_pointer_cast<GameEngineActor>(shared_from_this()));
	}
}