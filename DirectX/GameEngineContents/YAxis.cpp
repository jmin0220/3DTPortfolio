#include "PreCompile.h"
#include "YAxis.h"

YAxis::YAxis() 
{
}

YAxis::~YAxis() 
{
}

void YAxis::Start()
{
	{
		// 마우스 피킹
		CreatePickingCollision({ 25.0f, 125.0f, 25.0f }, { 0,50.0f,0 });
		Collision_Picking->ChangeOrder(CollisionGroup::Picking);
	}

	float4 Dir = { 0,1.0f,0,0 };

	SetAxisDir(Dir);
}

void YAxis::Update(float _DeltaTime)
{
	CheckPickingRay();
}

