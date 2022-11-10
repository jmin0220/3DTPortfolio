#include "PreCompile.h"
#include "PhysicsTestLevel.h"
#include <GameEngineCore/CoreMinimal.h>

#include "TestBox.h"
#include "TestGround.h"
#include "TestWall.h"
#include "TestPlayer.h"

PhysicsTestLevel::PhysicsTestLevel() 
{
}

PhysicsTestLevel::~PhysicsTestLevel() 
{
}

void PhysicsTestLevel::Start()
{

	GEngine::CollisionDebugOn();
	GetMainCameraActor()->GetTransform().SetWorldPosition({ 0.0f, 200.0f, 100.0f });
	GetMainCameraActor()->GetTransform().SetWorldRotation({ -10.0f,  10.0f, 0.0f});

}

void PhysicsTestLevel::Update(float _DeltaTime)
{
	GameEngineTransform& Transform = GetMainCameraActor()->GetTransform();

}

void PhysicsTestLevel::End()
{

}

void PhysicsTestLevel::LevelStartEvent()
{


	//std::shared_ptr<GameEngineActor> Box = CreateActor<TestBox>();
	std::shared_ptr<GameEngineActor> Player = CreateActor<TestPlayer>();
	std::shared_ptr<GameEngineActor> Ground = CreateActor<TestGround>();
	std::shared_ptr<GameEngineActor> Wall = CreateActor<TestWall>();
}

void PhysicsTestLevel::LevelEndEvent()
{
}
