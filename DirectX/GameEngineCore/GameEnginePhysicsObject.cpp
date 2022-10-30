#include "PreCompile.h"
#include "GameEnginePhysicsObject.h"
#include "GameEngineLevel.h"
#include "GameEngineComponent.h"
#include "GameEngineTransformComponent.h"
#include <GameEngineContents/GlobalValues.h>

GameEnginePhysicsObject::GameEnginePhysicsObject()
	: Gravity(float4{0.0f, -9.810f, 0.0f})
	, Velocity({0.0f, 0.0f, 0.0f})
	, CollideImpact({1.0f,1.0f,1.0f})
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
	if (Velocity.x > 50.0f)
	{
		int a = 0;
	}
	GameEngineCollision* CollisionResult = CollisionCheck(MyCollisionGroup);
	if (CollisionResult != nullptr)
	{
		CollideImpact = CollidedNormalVectorReturn(CollisionResult);

	}

	BasicDynamics(_DeltaTime);
}

void GameEnginePhysicsObject::BasicDynamics(float _DeltaTime)
{
	float4 GetPosition = GetTransform().GetWorldPosition();
	float4 NewForce = Force + Gravity * Mass;
	float4 Acceleration = NewForce / Mass;
	Velocity += Acceleration * _DeltaTime;

	Velocity *= CollideImpact;
	float4 MovedPosition = Velocity * _DeltaTime + (NewForce / Mass) * _DeltaTime * _DeltaTime * 0.5f;
	GetTransform().SetWorldMove(MovedPosition);

	CollideImpact = { 1.0f, 1.0f, 1.0f };
}

void GameEnginePhysicsObject::End()
{
}