#include "PreCompile.h"
#include "PhysicsBase.h"
#include <GameEngineContents/GlobalValues.h>

PhysicsBase::PhysicsBase()
{

}

PhysicsBase::~PhysicsBase()
{
}

std::vector<std::shared_ptr<GameEngineCollision>> PhysicsBase::CollisionCheck(int _MyCollisionGroup)
{
	std::shared_ptr<GameEngineCollision> InstColCollisionResult = nullptr;
	std::vector<std::shared_ptr<GameEngineCollision>> InstColCollisionResults;
	bool IsCollide = false;

	for (int i = 0; i < static_cast<int>(CollisionGroup::Max); i++)
	{
		InstColCollisionResult = nullptr;
		if (i != _MyCollisionGroup)
		{
			bool CollisionResult = IsCollision(CollisionType::CT_OBB, i, CollisionType::CT_OBB, 
				[&InstColCollisionResult, &IsCollide, &InstColCollisionResults](std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)->CollisionReturn
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

std::shared_ptr<GameEngineCollision> PhysicsBase::CollisionCheckCertainGroup(int _Group)
{
	std::shared_ptr<GameEngineCollision> InstColCollisionResult = nullptr;
	bool IsCollide = false;
	bool CollisionResult = IsCollision(CollisionType::CT_OBB, _Group, CollisionType::CT_OBB,
		[&InstColCollisionResult, &IsCollide](std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)->CollisionReturn
		{
			InstColCollisionResult = _Other;
			IsCollide = true;
			return CollisionReturn::Break;
		});

	return InstColCollisionResult;
}

float4 PhysicsBase::CollidedVector(std::shared_ptr<GameEngineCollision> _Other)
{
	return  GetActor()->GetTransform().GetWorldPosition() - _Other->GetActor()->GetTransform().GetWorldPosition();
}

float4 PhysicsBase::CollidedNormalVectorReturn(std::shared_ptr<GameEngineCollision> _Other)
{
	return CollidedVector(_Other).Normalize3DReturn();
}