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

GameEngineCollision* GameEnginePhysics::CollisionCheck(int _MyCollisionGroup)
{
	GameEngineCollision* InstColCollisionResult = nullptr;
	bool IsCollide = false;

	for (int i = 0; i < static_cast<int>(CollisionGroup::Max); i++)
	{
		InstColCollisionResult = nullptr;
		if (i != _MyCollisionGroup)
		{
			bool CollisionResult = IsCollision(CollisionType::CT_OBB, i, CollisionType::CT_OBB, 
				[&InstColCollisionResult, &IsCollide](GameEngineCollision* _This, GameEngineCollision* _Other)->CollisionReturn
				{
					InstColCollisionResult = _Other;
					IsCollide = true;
					return CollisionReturn::Break;
				});
		}
		if (InstColCollisionResult != nullptr)
		{
			return InstColCollisionResult;
		}
	}

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