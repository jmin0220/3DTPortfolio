#include "PreCompile.h"
#include "TestActor_Plane.h"

TestActor_Plane::TestActor_Plane() 
{
}

TestActor_Plane::~TestActor_Plane() 
{
}

void TestActor_Plane::Start()
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 2000, 2000, 1 });
	Collision_->ChangeOrder(CollisionGroup::Map);
	Collision_->SetDebugSetting(CollisionType::CT_OBB, float4(0, 0.5f, 0, 0.5f));

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetMesh("Rect");
	Renderer_->SetTexture("UI_basic_panel.png");
	Renderer_->GetTransform().SetWorldScale({ 2000, 2000, 1 });

	GetTransform().SetWorldRotation({ 90, 0, 0 });
}

void TestActor_Plane::Update(float _DeltaTime)
{
}

void TestActor_Plane::End()
{
}
