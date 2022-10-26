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

void PickableActor::CreatePickingCollision(float4 Scale)
{
	Collision_Picking = CreateComponent<GameEngineCollision>();
	Collision_Picking->GetTransform().SetWorldScale(Scale);
}


// ActorPicker�� �� �浹�߾�� �˷���
void PickableActor::CheckPickingRay()
{
	if (nullptr == Collision_Picking)
	{
		MsgBoxAssert("�� �����Ϳ� ���Ϳ� ��ŷ�� �ݸ����� �������� �ʾҽ��ϴ�");
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