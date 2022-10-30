#include "PreCompile.h"
#include "TestGround.h"
#include <GameEngineCore/GameEnginePhysicsObject.h>

TestGround::TestGround() 
{
}

TestGround::~TestGround() 
{
}

void TestGround::Start()
{
	//Renderer = CreateComponent<GameEngineTextureRenderer>();
	//Renderer->SetPipeLine("Color");
	//Renderer->SetMesh("Box");

	//ResultColor = float4(0.0f, 0.5f, 0.0f, 1.0f);
	//Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", ResultColor);

	Collision = CreateComponent<GameEnginePhysicsObject>();
	Collision->GetTransform().SetLocalScale({ 1, 1, 1 });
	Collision->ChangeOrder(CollisionGroup::PhysicsGround);
	Collision->SetMyCollisionGroup(static_cast<int>(CollisionGroup::PhysicsGround));
	Collision->SetDebugSetting(CollisionType::CT_OBB, float4(0.0f, 1.0f, 0.0f, 0.5f));
	Collision->SetDebugSetting(CollisionType::CT_OBB, float4(0.0f, 1.0f, 0.0f, 0.5f));
	Collision->SetVelocity({ 0.0f, 10.0f, 0.0f });
	Collision->SetGravity({ 0.0f, 0.0f, 0.0f });

	GetTransform().SetWorldScale({ 1000, 10, 1000});
	GetTransform().SetWorldPosition({ 0.0f, -100.0f, 0.0f });

}

void TestGround::Update(float _DeltaTime)
{
	
}

