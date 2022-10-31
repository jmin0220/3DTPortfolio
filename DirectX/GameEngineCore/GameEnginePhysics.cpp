#include "PreCompile.h"
#include "GameEnginePhysics.h"
#include "GameEngineLevel.h"
#include "GameEngineComponent.h"
#include "GameEngineTransformComponent.h"
#include <GameEngineContents/GlobalValues.h>

GameEnginePhysics::GameEnginePhysics()
{

}

GameEnginePhysics::~GameEnginePhysics()
{
}

std::vector<GameEngineCollision*> GameEnginePhysics::CollisionCheck(int _MyCollisionGroup)
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

GameEngineCollision* GameEnginePhysics::CollisionCheckCertainGroup(int _Group)
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

float4 GameEnginePhysics::CollidedVector(GameEngineCollision* _Other)
{
	return  GetTransform().GetWorldPosition() - _Other->GetTransform().GetWorldPosition();
}

float4 GameEnginePhysics::CollidedNormalVectorReturn(GameEngineCollision* _Other)
{
	return CollidedVector(_Other).Normalize3DReturn();
}