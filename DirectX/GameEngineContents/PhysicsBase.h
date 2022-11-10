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

	std::vector<std::shared_ptr<GameEngineCollision>> CollisionCheck(int _MyCollisionGroup);
	std::shared_ptr<GameEngineCollision> CollisionCheckCertainGroup(int _Group);
	float4 CollidedVector(std::shared_ptr<GameEngineCollision> _Other);
	float4 CollidedNormalVectorReturn(std::shared_ptr<GameEngineCollision> _Other);
private:

};

