#include "PreCompile.h"
#include "GameEnginePhysicsObject.h"
#include "GameEngineLevel.h"
#include "GameEngineComponent.h"
#include "GameEngineTransformComponent.h"
#include <GameEngineContents/GlobalValues.h>
#include "GameEngineCollision.h"

GameEnginePhysicsObject::GameEnginePhysicsObject()
	: Gravity(float4{0.0f, -9.810f, 0.0f})
	, Velocity({0.0f, 0.0f, 0.0f})
	, Mass(1.0f)
	, MyCollisionGroup(0)
	, IsCollide(false)
	, IsStatic (true)
	, BoundRatio(0.0f)
	, _ColliderType(ColliderType::StaticCollider)
	, _CompoundType(CompoundType::Ground)
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
	IsCollide = false;

	if (Velocity.x > 50.0f)
	{
		int a = 0;
	}
	std::vector<GameEngineCollision*> CollisionResults = CollisionCheck(MyCollisionGroup);
	if (CollisionResults.size() > 0)
	{
		IsCollide = true;
	}
	BasicDynamics(_DeltaTime, CollisionResults);
}

void GameEnginePhysicsObject::BasicDynamics(float _DeltaTime, std::vector<GameEngineCollision*> _CollisionResults)
{
	float4 GetPosition = GetTransform().GetWorldPosition();
	float4 NewForce = Force + Gravity * Mass;
	float4 Acceleration = NewForce / Mass;
	Velocity += Acceleration * _DeltaTime;

	//충돌기반으로 velocity를 조정한다;

	for (GameEngineCollision* Collision : _CollisionResults)
	{
		if (IsCollide == true && IsStatic == false)
		{
			GameEnginePhysicsObject* CollisionPO = dynamic_cast<GameEnginePhysicsObject*> (Collision);
			CompoundType InstCompoundType = CollisionPO->_CompoundType;
			switch (InstCompoundType)
			{
			case CompoundType::Ground:
				CollisionWithGround(_DeltaTime, CollisionPO);
				break;
			case CompoundType::Wall:
				CollisionWithWall(_DeltaTime, CollisionPO);
				break;
			default:
				break;
			}

		}
	}

	float4 MovedPosition = Velocity * _DeltaTime + (NewForce / Mass) * _DeltaTime * _DeltaTime * 0.5f;
	GetTransform().SetWorldMove(MovedPosition);
}

void GameEnginePhysicsObject::CollisionWithGround(float _DeltaTime, GameEnginePhysicsObject* _PO)
{

	float4 InstGravity = Gravity;
	float4 NewForce = Force + Gravity * Mass;
	float4 UpVector = _PO->GetTransform().GetUpVector();

	Velocity.y *= -UpVector.y * _PO->BoundRatio;
	while (true)
	{
		GameEngineCollision* InstGround = CollisionCheckCertainGroup(static_cast<int>(CollisionGroup::PhysicsGround));
		if (InstGround == nullptr)
		{
			break;
		}
		float4 InstVec = GetTransform().GetWorldPosition() - InstGround->GetTransform().GetWorldPosition();
		if (InstVec.y > 0.0f)
		{
			InstVec = { 0.0f, 0.5f, 0.0f };
		}
		else
		{
			InstVec = { 0.0f, -0.5f, 0.0f };
		}
		GetTransform().SetWorldMove(InstVec);
	}

}

void GameEnginePhysicsObject::CollisionWithWall(float _DeltaTime, GameEnginePhysicsObject* _PO)
{

	float4 InstGravity = Gravity;
	float4 NewForce = Force + Gravity * Mass;
	float4 UpVector = _PO->GetTransform().GetUpVector();

	Velocity.x *= -UpVector.y * _PO->BoundRatio;
	while (true)
	{
		GameEngineCollision* InstGround = CollisionCheckCertainGroup(static_cast<int>(CollisionGroup::PhysicsWall));
		if (InstGround == nullptr)
		{
			break;
		}
		float4 InstVec = GetTransform().GetWorldPosition() - InstGround->GetTransform().GetWorldPosition();
		if (InstVec.x > 0.0f)
		{
			InstVec = { 0.5f, 0.0f, 0.0f };
		}
		else
		{
			InstVec = { -0.5f, 0.0f, 0.0f };
		}
		GetTransform().SetWorldMove(InstVec);
	}

}

void GameEnginePhysicsObject::End()
{
}