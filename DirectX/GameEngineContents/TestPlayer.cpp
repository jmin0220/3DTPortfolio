#include "PreCompile.h"
#include "TestPlayer.h"
#include "PhysicsObject.h"
#include <GameEngineCore/GameEngineUpdateObject.h>

TestPlayer::TestPlayer() 
{
}

TestPlayer::~TestPlayer() 
{
}

void TestPlayer::Start()
{
	if (GameEngineInput::GetInst()->IsKey("MoveRight") == false)
	{
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveForward", VK_UP);
		GameEngineInput::GetInst()->CreateKey("MoveBackward", VK_DOWN);
	}

	Collision = CreateComponent<PhysicsObject>();

	Collision->GetTransform().SetLocalScale({ 1, 1, 1 });
	Collision->ChangeOrder(CollisionGroup::PhysicsPlayer);
	Collision->SetMyCollisionGroup(static_cast<int>(CollisionGroup::PhysicsPlayer));
	Collision->SetDebugSetting(CollisionType::CT_OBB, float4(1.0f, 0.0f, 0.0f, 1.0f));
	Collision->SetVelocity({ 0.0f, 0.0f, 0.0f });
	Collision->SetGravity({ 0.0f, -98.1f, 0.0f });
	Collision->SetIsStatic(false);
	Collision->SetCompoundType(CompoundType::Player);

	//Renderer = CreateComponent<GameEngineTextureRenderer>();
	//Renderer->SetPipeLine("Color");
	//Renderer->SetMesh("Box");

	//ResultColor = float4(1.0f, 0.0f, 0.0f, 0.5f);
	//Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", ResultColor);

	GetTransform().SetWorldPosition({ 100, 100, 100 });
	GetTransform().SetWorldScale({ 100, 100, 100 });

}

void TestPlayer::Update(float _DeltaTime)
{
}

