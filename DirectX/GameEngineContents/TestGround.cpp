#include "PreCompile.h"
#include "TestGround.h"

TestGround::TestGround() 
{
}

TestGround::~TestGround() 
{
}

void TestGround::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->SetPipeLine("Color");
	Renderer->SetMesh("Box");

	ResultColor = float4(0.0f, 0.5f, 0.0f, 1.0f);
	Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", ResultColor);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 1, 1, 1 });
	Collision->ChangeOrder(CollisionGroup::PhysicsGround);
	Collision->SetDebugSetting(CollisionType::CT_OBB, float4(0.0f, 1.0f, 0.0f, 0.5f));

	GetTransform().SetWorldScale({ 1000, 10, 1000});
	GetTransform().SetWorldPosition({ 0.0f, -100.0f, 0.0f });

}

void TestGround::Update(float _DeltaTime)
{
	
}

