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
		// 마우스 피킹
		CreatePickingCollision({ 25.0f, 25.0f, 125.0f }, { 0.0f,0,-50.0f });
		Collision_Picking.lock()->ChangeOrder(CollisionGroup::Axis);
	}

	float4 Dir = { 0, 0 , 1.0f ,0 };

	SetAxisDir(Dir);
}

void ZAxis::Update(float _DeltaTime)
{
	CheckPickingRay();
}

