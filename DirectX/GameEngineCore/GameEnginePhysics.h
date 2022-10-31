#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include "GameEngineUpdateObject.h"
#include <list>
#include "GameEngineTransformBase.h"
#include "GameEngineCollision.h"
#include "GameEngineUpdateObject.h"



enum class ColliderType
{
	StaticCollider,
	PlayerCollider,
	Max,
};

enum class CompoundType
{
	Ground,
	Wall,
	Player,
	Max,
};

// ���� : ���� ������ ������ ����ϴ� Ŭ����
class GameEnginePhysics : public GameEngineCollision
{

public:
	// constrcuter destructer
	GameEnginePhysics();
	virtual ~GameEnginePhysics();

	// delete Function
	GameEnginePhysics(const GameEnginePhysics& _Other) = delete;
	GameEnginePhysics(GameEnginePhysics&& _Other) noexcept = delete;
	GameEnginePhysics& operator=(const GameEnginePhysics& _Other) = delete;
	GameEnginePhysics& operator=(GameEnginePhysics&& _Other) noexcept = delete;

protected:

	std::vector<GameEngineCollision*> CollisionCheck(int _MyCollisionGroup);
	GameEngineCollision* CollisionCheckCertainGroup(int _Group);
	float4 CollidedVector(GameEngineCollision* _Other);
	float4 CollidedNormalVectorReturn(GameEngineCollision* _Other);
private:

};
