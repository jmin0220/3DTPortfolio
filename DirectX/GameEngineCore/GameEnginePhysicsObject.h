#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include "GameEngineUpdateObject.h"
#include <list>
#include "GameEngineTransformBase.h"
#include "GameEnginePhysics.h"


// 설명 : 게임 엔진의 물리를 담당하는 클래스
class GameEnginePhysicsObject : public GameEnginePhysics
{

public:
	// constrcuter destructer
	GameEnginePhysicsObject();
	virtual ~GameEnginePhysicsObject();

	// delete Function
	GameEnginePhysicsObject(const GameEnginePhysicsObject& _Other) = delete;
	GameEnginePhysicsObject(GameEnginePhysicsObject&& _Other) noexcept = delete;
	GameEnginePhysicsObject& operator=(const GameEnginePhysicsObject& _Other) = delete;
	GameEnginePhysicsObject& operator=(GameEnginePhysicsObject&& _Other) noexcept = delete;
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void SetMyCollisionGroup(int _Int)
	{
		MyCollisionGroup = _Int;
	}




private:
	float4 Gravity;
	float4 Velocity;
	float4 Force;
	float Mass;
	int MyCollisionGroup;
	bool IsCollide;
	bool IsStatic;
	float BoundRatio;
	ColliderType _ColliderType;
	CompoundType _CompoundType;

	void BasicDynamics(float _DeltaTime, std::vector<GameEngineCollision*> _CollisionResults);
	void CollisionWithGround(float _DeltaTime, GameEnginePhysicsObject* _PO);
	void CollisionWithWall(float _DeltaTime, GameEnginePhysicsObject* _PO);

public:
	void SetGravity(float4 _Gravity)
	{
		Gravity = _Gravity;
	}

	void SetVelocity(float4 _Velocity)
	{
		Velocity = _Velocity;
	}

	void SetForce(float4 _Force)
	{
		Force = _Force;
	}

	void SetColliderType(ColliderType _Type)
	{
		_ColliderType = _Type;
	}

	void SetCompoundType(CompoundType _Type)
	{
		_CompoundType = _Type;
	}

	void SetIsStatic(bool _boolean)
	{
		IsStatic = _boolean;
	}

	void SetBoundRatio(float _BoundRatio)
	{
		if (_BoundRatio < 0.0f)
		{
			MsgBoxAssert("BoundRatio를 음수로 설정하지 마시오");
		}
		BoundRatio = _BoundRatio;
	}
};

