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
	void CreatePickingCollision(float4 Scale);
	void CheckPickingRay();

	// 맵 에딧용 콜리전, 캐릭용 콜리전은 별도로 생각해야함
	GameEngineCollision* Collision_Picking;
};

