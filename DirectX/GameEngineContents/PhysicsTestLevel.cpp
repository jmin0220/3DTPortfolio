#include "PreCompile.h"
#include "PhysicsTestLevel.h"
#include <GameEngineCore/CoreMinimal.h>

#include "TestBox.h"
#include "TestGround.h"
#include "TestWall.h"

PhysicsTestLevel::PhysicsTestLevel() 
{
}

PhysicsTestLevel::~PhysicsTestLevel() 
{
}

void PhysicsTestLevel::Start()
{
	GameEngineActor* Box = CreateActor<TestBox>();
	GameEngineActor* Ground = CreateActor<TestGround>();
	GameEngineActor* Wall = CreateActor<TestWall>();
	GEngine::CollisionDebugOn();
	GetMainCameraActor()->GetTransform().SetWorldPosition({ 0.0f, 500.0f, 1725.42419f });
	GetMainCameraActor()->GetTransform().SetWorldRotation({ -10.0f,  10.0f, 0.0f});

}

void PhysicsTestLevel::Update(float _DeltaTime)
{
	GameEngineTransform& Transform = GetMainCameraActor()->GetTransform();

}

void PhysicsTestLevel::End()
{

}
