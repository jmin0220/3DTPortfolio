#pragma once
#include <GameEngineCore/GameEngineActor.h>


// 설명 :
class PickableActor : public GameEngineActor
{
public:

	// ★★★ CreateActor<PickableActor> 후에 무조건 호출해줘야함 ★★★
	void SetStaticMesh(const std::string& _FBX, const std::string& _Texture = "");

	// Axis용
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
//	엑터 피킹
/////////////////////////////////////////////////////////////////////

	// 피킹 레이저와 닿았는지 여부 체크
	void CheckPickingRay();
	void CheckSelected();

	// 맵 에딧용 콜리전, 캐릭용 콜리전은 별도로 생각해야함
	std::shared_ptr<GameEngineCollision> Collision_Picking;
	std::shared_ptr<GameEngineFBXStaticRenderer> FBXRenderer_;
	std::shared_ptr<GameEngineCollision> PrevActorCol;

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool IsAxis_;
	float4 MoveDir_;

// .feat 희상형
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

