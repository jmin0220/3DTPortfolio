#include "PreCompile.h"
#include "ZAxis.h"

ZAxis::ZAxis() 
{
}

ZAxis::~ZAxis() 
{
}

void ZAxis::Start()
{
	{
		Collision = CreateComponent<GameEngineCollision>();
		//Collision->GetTransform().SetLocalScale({ 25.0f, 25.0f, 125.0f });
		Collision->GetTransform().SetLocalScale({ 1, 1, 1 });
		Collision->GetTransform().SetLocalPosition({ 0.0f,0,-50.0f });
		Collision->ChangeOrder(CollisionGroup::Map);
		Collision->SetDebugSetting(CollisionType::CT_OBB, float4(0.0f, 0.0f, 1.0f, 0.5f));

		// 마우스 피킹
		CreatePickingCollision(Collision->GetTransform().GetWorldScale(),Collision->GetTransform().GetWorldPosition());
	}

	float4 Dir = { 0, 0 , 1.0f ,0 };

	SetAxisDir(Dir);
}

void ZAxis::Update(float _DeltaTime)
{
	CheckPickingRay();
}

