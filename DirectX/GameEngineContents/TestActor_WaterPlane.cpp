#include "PreCompile.h"
#include "TestActor_WaterPlane.h"


TestActor_WaterPlane::TestActor_WaterPlane() 
{
}

TestActor_WaterPlane::~TestActor_WaterPlane() 
{
}

// "Water" ���׸���(������ ����������) ���� ����
void TestActor_WaterPlane::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetMesh("Rect");
	Renderer_->GetRenderUnit().SetPipeLine("Water");
	Renderer_->GetRenderUnit().EngineShaderResourcesSetting(Renderer_);
	Renderer_->GetTransform().SetWorldScale({ 2000, 2000, 1 });

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 2000, 2000, 1 });
	Collision_->ChangeOrder(CollisionGroup::Map);
	Collision_->SetDebugSetting(CollisionType::CT_OBB, float4(0, 0.5f, 0, 0.5f));

	GetTransform().SetWorldRotation({ 90, 0, 0 });
}

void TestActor_WaterPlane::Update(float _DeltaTime)
{
}

