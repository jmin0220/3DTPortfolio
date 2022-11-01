#include "PreCompile.h"
#include "TestBox.h"
#include "PhysicsObject.h"
#include <GameEngineCore/GameEngineUpdateObject.h>

TestBox::TestBox() 
{
}

TestBox::~TestBox() 
{
}

void TestBox::Start()
{
	//Renderer = CreateComponent<GameEngineTextureRenderer>();
	//Renderer->SetPipeLine("Color");
	//Renderer->SetMesh("Box");

	//ResultColor = float4(1.0f, 0.5f, 0.0f, 1.0f);
	//Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", ResultColor);

	Collision = CreateComponent<PhysicsObject>();

	Collision->GetTransform().SetLocalScale({ 1, 1, 1 });
	Collision->ChangeOrder(CollisionGroup::PhysicsPlayer);
	Collision->SetMyCollisionGroup(static_cast<int>(CollisionGroup::PhysicsPlayer));
	Collision->SetDebugSetting(CollisionType::CT_OBB, float4(1.0f, 0.0f, 0.0f, 1.0f));
	Collision->SetVelocity({ 300.0f, 100.0f, 10.0f });
	Collision->SetGravity({ 0.0f, -98.1f, 0.0f });
	Collision->SetIsStatic(false);
	Collision->SetCompoundType(CompoundType::Player);

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->SetPipeLine("Color");
	Renderer->SetMesh("Box");

	ResultColor = float4(1.0f, 0.0f, 0.0f, 0.5f);
	Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", ResultColor);

	GetTransform().SetWorldPosition({ 100, 100, 100 });
	GetTransform().SetWorldScale({ 100, 100, 100 });

}

void TestBox::Update(float _DeltaTime)
{
}

