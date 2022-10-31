#include "PreCompile.h"
#include "XAxis.h"

XAxis::XAxis() 
{
}

XAxis::~XAxis() 
{
}

void XAxis::Start()
{
	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 125.0f, 25.0f, 25.0f });
		//Collision->GetTransform().SetLocalScale({ 1, 1, 1 });
		Collision->GetTransform().SetLocalPosition({ 50.0f,0,0 });
		Collision->ChangeOrder(CollisionGroup::Map);
		Collision->SetDebugSetting(CollisionType::CT_OBB, float4(1.0f, 0.0f, 0.0f, 0.5f));

		// 마우스 피킹
		CreatePickingCollision(Collision->GetTransform().GetWorldScale(), Collision->GetTransform().GetWorldPosition());
	}

	float4 Dir = { 1.0f,0,0,0 };

	SetAxisDir(Dir);
}

void XAxis::Update(float _DeltaTime)
{
	CheckPickingRay();
}

