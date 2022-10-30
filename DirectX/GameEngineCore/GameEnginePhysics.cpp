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

bool GameEnginePhysics::CollisionCheck(int _MyCollisionGroup)
{
	std::vector<GameEngineCollision*> CollisionResults;
	GameEngineCollision* InstColCollisionResult = nullptr;\
	bool IsCollide = false;

	for (int i = 0; i < static_cast<int>(CollisionGroup::Max); i++)
	{
		InstColCollisionResult = nullptr;
		if (i != _MyCollisionGroup)
		{
			bool CollisionResult = IsCollision(CollisionType::CT_OBB, i, CollisionType::CT_OBB, 
				[&InstColCollisionResult, &CollisionResults, &IsCollide](GameEngineCollision* _This, GameEngineCollision* _Other)->CollisionReturn
				{
					InstColCollisionResult = _Other;
					CollisionResults.push_back(_Other);
					IsCollide = true;
					return CollisionReturn::ContinueCheck;
				});
		}
	}
	return IsCollide;
}
