#include "PreCompile.h"
#include "TestWall.h"
#include "PhysicsObject.h"

TestWall::TestWall() 
{
}

TestWall::~TestWall() 
{
}

void TestWall::Start()
{
	//Renderer = CreateComponent<GameEngineTextureRenderer>();
	//Renderer->SetMaterial("Color");
	//Renderer->SetMesh("Box");

	//ResultColor = float4(0.0f, 0.5f, 0.0f, 1.0f);
	//Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", ResultColor);

	Wall = CreateComponent<PhysicsObject>();
	Wall->GetTransform().SetLocalScale({ 1, 1, 1 });
	Wall->ChangeOrder(CollisionGroup::PhysicsWall);
	Wall->SetMyCollisionGroup(static_cast<int>(CollisionGroup::PhysicsGround));
	Wall->SetDebugSetting(CollisionType::CT_OBB, float4(0.0f, 1.0f, 0.0f, 1.0f));
	Wall->SetDebugSetting(CollisionType::CT_OBB, float4(0.0f, 1.0f, 0.0f, 1.0f));
	Wall->SetVelocity({ -10.0f, 0.0f, 0.0f });
	Wall->SetGravity({ 0.0f, 0.0f, 0.0f });
	Wall->SetBoundRatio(0.8f);
	Wall->SetCompoundType(CompoundType::Wall);
	GetTransform().SetWorldScale({ 10, 1000, 1000});
	GetTransform().SetWorldPosition({ 400.0f, 0.0f, 0.0f });

	//Wall2 = CreateComponent<PhysicsObject>();
	//Wall2->GetTransform().SetLocalScale({ 1, 1, 1 });
	//Wall2->ChangeOrder(CollisionGroup::PhysicsWall);
	//Wall2->SetMyCollisionGroup(static_cast<int>(CollisionGroup::PhysicsGround));
	//Wall2->SetDebugSetting(CollisionType::CT_OBB, float4(0.0f, 1.0f, 0.0f, 1.0f));
	//Wall2->SetDebugSetting(CollisionType::CT_OBB, float4(0.0f, 1.0f, 0.0f, 1.0f));
	//Wall2->SetVelocity({ 10.0f, 0.0f, 0.0f });
	//Wall2->SetGravity({ 0.0f, 0.0f, 0.0f });
	//Wall2->SetBoundRatio(0.8f);
	//Wall2->SetCompoundType(CompoundType::Wall);
	//Wall2->GetTransform().SetWorldScale({ 10, 1000, 1000 });
	//Wall2->GetTransform().SetWorldPosition({ -400.0f, 0.0f, 0.0f });

}

void TestWall::Update(float _DeltaTime)
{
	
}

