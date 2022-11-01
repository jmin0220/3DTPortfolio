#include "PreCompile.h"
#include "PhysicsObject.h"
#include <GameEngineContents/GlobalValues.h>

PhysicsObject::PhysicsObject()
	: Gravity(float4{0.0f, -9.810f, 0.0f})
	, Velocity({0.0f, 0.0f, 0.0f})
	, Mass(1.0f)
	, MyCollisionGroup(0)
	, IsCollide(false)
	, IsStatic (true)
	, BoundRatio(0.0f)
	, _ColliderType(ColliderType::StaticCollider)
	, _CompoundType(CompoundType::Ground)
	, IsPlayable(false)
{

}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::Start()
{
}
void PhysicsObject::Update(float _DeltaTime)
{
	IsCollide = false;
	if (IsPlayable == true)
	{
		InputUpdate();
	}

	std::vector<GameEngineCollision*> CollisionResults = CollisionCheck(MyCollisionGroup);
	if (CollisionResults.size() > 0)
	{
		IsCollide = true;
	}


	BasicDynamics(_DeltaTime, CollisionResults);

}

void PhysicsObject::BasicDynamics(float _DeltaTime, std::vector<GameEngineCollision*> _CollisionResults)
{
	float4 GetPosition = GetActor()->GetTransform().GetWorldPosition();
	float4 NewForce = Force + Gravity * Mass;
	float4 Acceleration = NewForce / Mass;
	Velocity += Acceleration * _DeltaTime;
	//충돌기반으로 velocity를 조정한다;
	VelocityCal(_DeltaTime);
	float4 MovedPosition = Velocity * _DeltaTime + (NewForce / Mass) * _DeltaTime * _DeltaTime * 0.5f;
	GetActor()->GetTransform().SetWorldMove(MovedPosition);

	if (IsPlayable == true)
	{
		CalculateMoveVel(_DeltaTime);
		GetActor()->GetTransform().SetWorldMove(MovementVelocity * _DeltaTime);
	}
	for (GameEngineCollision* Collision : _CollisionResults)
	{
		if (IsCollide == true && IsStatic == false)
		{
			PhysicsObject* CollisionPO = dynamic_cast<PhysicsObject*> (Collision);
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
}

void PhysicsObject::VelocityCal(float _DeltaTime)
{

}

void PhysicsObject::CollisionWithGround(float _DeltaTime, PhysicsObject* _PO)
{
	float4 InstGravity = Gravity;
	float4 UpVector = _PO->GetActor()->GetTransform().GetUpVector();
	

	Velocity.y *= -UpVector.y * _PO->BoundRatio;

	while (true)
	{
		GameEngineCollision* InstGround = CollisionCheckCertainGroup(static_cast<int>(CollisionGroup::PhysicsGround));
		if (InstGround == nullptr)
		{
			break;
		}
		//float4 InstVec = GetActor()->GetTransform().GetWorldPosition() - InstGround->GetActor()->GetTransform().GetWorldPosition();
		//float4 Rotation = InstGround->GetActor()->GetTransform().GetLocalRotation();
		// 
		//TODO::위에서 박았는지 아래에서 박았는지 확인용, 일단 위에서 아래로 박는다고 가정하기
		float4 InstVec = float4{ 0.0f, 1.0f, 0.0f };
		if (InstVec.y > 0.0f)
		{
			InstVec = { 0.0f, 0.05f, 0.0f };
		}
		else
		{
			float4 Instfloat4 = GetActor()->GetTransform().GetWorldPosition();
			InstVec = { 0.0f, -0.05f, 0.0f };
		}
		GetActor()->GetTransform().SetWorldMove(InstVec);
	}

}

void PhysicsObject::CollisionWithWall(float _DeltaTime, PhysicsObject* _PO)
{
	float4 InstGravity = Gravity;
	float4 UpVector = _PO->GetActor()->GetTransform().GetUpVector();

	Velocity.x *= -UpVector.y * _PO->BoundRatio;
	while (true)
	{
		GameEngineCollision* InstGround = CollisionCheckCertainGroup(static_cast<int>(CollisionGroup::PhysicsWall));
		if (InstGround == nullptr)
		{
			break;
		}
		float4 InstVec = GetActor()->GetTransform().GetWorldPosition() - InstGround->GetActor()->GetTransform().GetWorldPosition();
		if (InstVec.x > 0.0f)
		{
			InstVec = { 0.5f, 0.0f, 0.0f };
		}
		else
		{
			InstVec = { -0.5f, 0.0f, 0.0f };
		}
		GetActor()->GetTransform().SetWorldMove(InstVec);
	}

}

void PhysicsObject::End()
{
}