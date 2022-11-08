#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
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
//	엑터 피킹
/////////////////////////////////////////////////////////////////////

	// 전부 자식에서 호출해주어야 할 함수
	void CreatePickingCollision(float4 Scale,float4 Position);
	void CheckPickingRay();

	// 맵 에딧용 콜리전, 캐릭용 콜리전은 별도로 생각해야함
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

