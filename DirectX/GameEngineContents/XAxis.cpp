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
		// 마우스 피킹
		CreatePickingCollision({ 125.0f, 25.0f, 25.0f }, { 50.0f,0,0 });
		Collision_Picking.lock()->ChangeOrder(CollisionGroup::Axis);
	}

	float4 Dir = { 1.0f,0,0,0 };

	SetAxisDir(Dir);
}

void XAxis::Update(float _DeltaTime)
{
	CheckPickingRay();
}

