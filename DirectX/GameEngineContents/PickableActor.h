#pragma once
#include <GameEngineCore/GameEngineActor.h>

struct AxisRotOption
{
	float4 RenderPos;
	float4 Color;
	bool IsRot;
};

// ���� :
class PickableActor : public GameEngineActor
{
public:
	static std::weak_ptr<GameEngineCollision> CurPicking_Collision;

	// constrcuter destructer
	PickableActor();
	~PickableActor();

	// delete Function
	PickableActor(const PickableActor& _Other) = delete;
	PickableActor(PickableActor&& _Other) noexcept = delete;
	PickableActor& operator=(const PickableActor& _Other) = delete;
	PickableActor& operator=(PickableActor&& _Other) noexcept = delete;

protected:
/////////////////////////////////////////////////////////////////////
//	���� ��ŷ
/////////////////////////////////////////////////////////////////////

	// ���� �ڽĿ��� ȣ�����־�� �� �Լ�
	void CreatePickingCollision(float4 Scale,float4 Position);
	void CheckPickingRay();

	// �� ������ �ݸ���, ĳ���� �ݸ����� ������ �����ؾ���
	std::weak_ptr<GameEngineCollision> Collision_Picking;
	std::weak_ptr<GameEngineCollision> PrevActorCol;


public:
	float4 AxisDir;
	void SetAxisDir(float4 Dir)
	{
		AxisDir = Dir;
	}

	float4 GetAxisDir()
	{
		return AxisDir;
	}

	int GetCollisionOrder()
	{
		return Collision_Picking.lock()->GetOrder();
	}

	static std::weak_ptr<GameEngineCollision> GetCurPickingCol()
	{
		return CurPicking_Collision;
	}

	std::weak_ptr<GameEngineCollision> GetPickingCol()
	{
		return Collision_Picking;
	}
};

