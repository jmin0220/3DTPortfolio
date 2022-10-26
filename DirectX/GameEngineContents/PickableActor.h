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
	void CreatePickingCollision(float4 Scale);
	void CheckPickingRay();

	// �� ������ �ݸ���, ĳ���� �ݸ����� ������ �����ؾ���
	GameEngineCollision* Collision_Picking;
};

