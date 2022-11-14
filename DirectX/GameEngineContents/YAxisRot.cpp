#include "PreCompile.h"
#include "YAxisRot.h"

YAxisRot::YAxisRot() 
{
}

YAxisRot::~YAxisRot() 
{
}

void YAxisRot::Start()
{
	{
		// 마우스 피킹
		CreatePickingCollision({ 25.0f, 125.0f, 25.0f }, { 0, 0.0f,0 });
		Collision_Picking.lock()->ChangeOrder(CollisionGroup::Axis);
	}

	float4 Dir = { 0,1.0f,0,0 };

	SetAxisDir(Dir);
}

void YAxisRot::Update(float _DeltaTime)
{
	CheckPickingRay();
}

