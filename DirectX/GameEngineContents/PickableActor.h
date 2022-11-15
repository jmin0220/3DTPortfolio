#pragma once
#include <GameEngineCore/GameEngineActor.h>


// ���� :
class PickableActor : public GameEngineActor
{
public:

	// �ڡڡ� CreateActor<PickableActor> �Ŀ� ������ ȣ��������� �ڡڡ�
	void SetStaticMesh(const std::string& _FBX, const std::string& _Texture = "");

	// Axis��
	void SetAxisMove(float4 _Color, float4 _Scale, float4 _MoveDir);
	void SetAxisRot(float4 _Color, float4 _Scale);

	bool IsAxis()
	{
		return IsAxis_;
	}

	float4 GetMoveDir()
	{
		return MoveDir_;
	}

public:
	static std::shared_ptr<GameEngineCollision> CurPicking_Collision;

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

	// ��ŷ �������� ��Ҵ��� ���� üũ
	void CheckPickingRay();
	void CheckSelected();

	// �� ������ �ݸ���, ĳ���� �ݸ����� ������ �����ؾ���
	std::shared_ptr<GameEngineCollision> Collision_Picking;
	std::shared_ptr<GameEngineFBXStaticRenderer> FBXRenderer_;
	std::shared_ptr<GameEngineCollision> PrevActorCol;

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool IsAxis_;
	float4 MoveDir_;

// .feat �����
//public:
	//float4 AxisDir;
	//void SetAxisDir(float4 Dir)
	//{
	//	AxisDir = Dir;
	//}

	//float4 GetAxisDir()
	//{
	//	return AxisDir;
	//}

	//int GetCollisionOrder()
	//{
	//	return Collision_Picking.lock()->GetOrder();
	//}

	//static std::weak_ptr<GameEngineCollision> GetCurPickingCol()
	//{
	//	return CurPicking_Collision;
	//}

	//std::weak_ptr<GameEngineCollision> GetPickingCol()
	//{
	//	return Collision_Picking;
	//}
};

