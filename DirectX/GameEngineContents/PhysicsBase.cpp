#include "PreCompile.h"
#include "PhysicsBase.h"
#include <GameEngineContents/GlobalValues.h>

PhysicsBase::PhysicsBase()
{

}

PhysicsBase::~PhysicsBase()
{
}

std::vector<GameEngineCollision*> PhysicsBase::CollisionCheck(int _MyCollisionGroup)
{
	GameEngineCollision* InstColCollisionResult = nullptr;
	std::vector<GameEngineCollision*> InstColCollisionResults;
	bool IsCollide = false;

	for (int i = 0; i < static_cast<int>(CollisionGroup::Max); i++)
	{
		InstColCollisionResult = nullptr;
		if (i != _MyCollisionGroup)
		{
			bool CollisionResult = IsCollision(CollisionType::CT_OBB, i, CollisionType::CT_OBB, 
				[&InstColCollisionResult, &IsCollide, &InstColCollisionResults](GameEngineCollision* _This, GameEngineCollision* _Other)->CollisionReturn
				{
					InstColCollisionResult = _Other;
					InstColCollisionResults.push_back(_Other);
					IsCollide = true;
					return CollisionReturn::Break;
				});
		}
	}

	return InstColCollisionResults;
}

GameEngineCollision* PhysicsBase::CollisionCheckCertainGroup(int _Group)
{
	GameEngineCollision* InstColCollisionResult = nullptr;
	bool IsCollide = false;
	bool CollisionResult = IsCollision(CollisionType::CT_OBB, _Group, CollisionType::CT_OBB,
		[&InstColCollisionResult, &IsCollide](GameEngineCollision* _This, GameEngineCollision* _Other)->CollisionReturn
		{
			InstColCollisionResult = _Other;
			IsCollide = true;
			return CollisionReturn::Break;
		});

	return InstColCollisionResult;
}

float4 PhysicsBase::CollidedVector(GameEngineCollision* _Other)
{
	return  GetActor()->GetTransform().GetWorldPosition() - _Other->GetActor()->GetTransform().GetWorldPosition();
}

float4 PhysicsBase::CollidedNormalVectorReturn(GameEngineCollision* _Other)
{
	return CollidedVector(_Other).Normalize3DReturn();
}