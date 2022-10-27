#include "PreCompile.h"
#include "TestBox.h"

TestBox::TestBox() 
{
}

TestBox::~TestBox() 
{
}

void TestBox::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->SetPipeLine("Color");
	Renderer->SetMesh("Box");
	Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", float4(0.0f, 0.5f, 0.0f, 1.0f));

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 1, 1, 1 });
	Collision->ChangeOrder(CollisionGroup::Map);
	Collision->SetDebugSetting(CollisionType::CT_OBB, float4(0.0f, 1.0f, 0.0f, 0.5f));

	GetTransform().SetWorldScale({ 100, 100, 100 });

}

void TestBox::Update(float _DeltaTime)
{
}

