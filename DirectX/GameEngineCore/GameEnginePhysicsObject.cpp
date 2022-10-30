#include "PreCompile.h"
#include "GameEnginePhysicsObject.h"
#include "GameEngineLevel.h"
#include "GameEngineComponent.h"
#include "GameEngineTransformComponent.h"
#include <GameEngineContents/GlobalValues.h>

GameEnginePhysicsObject::GameEnginePhysicsObject()
	: Gravity(float4{0.0f, -98.10f, 0.0f})
	, Velocity({100.0f, 100.0f, 10.0f})
	, Type(ColliderType::StaticCollider)
	, Mass(1.0f)
	, MyCollisionGroup(0)
{

}

GameEnginePhysicsObject::~GameEnginePhysicsObject()
{
}

void GameEnginePhysicsObject::Start()
{
}
void GameEnginePhysicsObject::Update(float _DeltaTime)
{
	bool CollisionResult = CollisionCheck(MyCollisionGroup);

	if (CollisionResult == false)
	{
		BasicDynamics(_DeltaTime);
	}
}

void GameEnginePhysicsObject::BasicDynamics(float _DeltaTime)
{
	float4 GetPosition = GetTransform().GetWorldPosition();
	float4 NewForce = Force + Gravity * Mass;
	float4 Acceleration = NewForce / Mass;
	Velocity += Acceleration * _DeltaTime;
	float4 MovedPosition = Velocity * _DeltaTime + (NewForce / Mass) * _DeltaTime * _DeltaTime * 0.5f;
	GetTransform().SetWorldMove(MovedPosition);
}

void GameEnginePhysicsObject::End()
{
}