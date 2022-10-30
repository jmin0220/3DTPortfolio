#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include "GameEngineUpdateObject.h"
#include <list>
#include "GameEngineTransformBase.h"
#include "GameEnginePhysics.h"


// ���� : ���� ������ ������ ����ϴ� Ŭ����
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

	void BasicDynamics(float _DeltaTime);

private:
	float4 Gravity;
	float4 Velocity;
	float4 Force;
	float4 CollideImpact;
	float Mass;
	ColliderType Type;
	int MyCollisionGroup;

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
		Type = _Type;
	}
};

