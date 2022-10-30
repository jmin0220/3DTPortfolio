#include "PreCompile.h"
#include "PhysicsTestLevel.h"
#include <GameEngineCore/CoreMinimal.h>

#include "TestBox.h"
#include "TestGround.h"

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
	GetMainCamera()->GetTransform().SetWorldPosition({ 0.0f, 200.0f, 0.0f });
	GEngine::CollisionDebugOn();
}

void PhysicsTestLevel::Update(float _DeltaTime)
{
}

void PhysicsTestLevel::End()
{

}
