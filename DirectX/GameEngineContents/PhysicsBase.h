#pragma once
#include <GameEngineBase/GameEngineNameObject.h>

#include <list>




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

// 설명 : 게임 엔진의 물리를 담당하는 클래스
class PhysicsBase : public GameEngineCollision
{

public:
	// constrcuter destructer
	PhysicsBase();
	virtual ~PhysicsBase();

	// delete Function
	PhysicsBase(const PhysicsBase& _Other) = delete;
	PhysicsBase(PhysicsBase&& _Other) noexcept = delete;
	PhysicsBase& operator=(const PhysicsBase& _Other) = delete;
	PhysicsBase& operator=(PhysicsBase&& _Other) noexcept = delete;

protected:

	std::vector<GameEngineCollision*> CollisionCheck(int _MyCollisionGroup);
	GameEngineCollision* CollisionCheckCertainGroup(int _Group);
	float4 CollidedVector(GameEngineCollision* _Other);
	float4 CollidedNormalVectorReturn(GameEngineCollision* _Other);
private:

};

