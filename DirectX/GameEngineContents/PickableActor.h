#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class PickableActor : public GameEngineActor
{
public:
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
	GameEngineCollision* Collision_Picking;
	GameEngineCollision* PrevActorCol;
	static GameEngineCollision* CurPicking_Collision;

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
		return Collision_Picking->GetOrder();
	}

	static GameEngineCollision* GetCurPickingCol()
	{
		return CurPicking_Collision;
	}

	GameEngineCollision* GetPickingCol()
	{
		return Collision_Picking;
	}
};

