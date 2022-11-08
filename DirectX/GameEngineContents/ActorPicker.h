#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : MapEditor���� �������� ��ü�� ������ �����ϸ� �ȵ�
class ActorPicker : public GameEngineActor
{
public:
	static std::set<GameEngineActor*> PickedActors;
	static GameEngineActor* PickedActor;
	static GameEngineActor* ClickedActor;
	static GameEngineActor* SelectedActor;
	static GameEngineActor* CurActor;

public:
	// constrcuter destructer
	ActorPicker();
	~ActorPicker();

	// delete Function
	ActorPicker(const ActorPicker& _Other) = delete;
	ActorPicker(ActorPicker&& _Other) noexcept = delete;
	ActorPicker& operator=(const ActorPicker& _Other) = delete;
	ActorPicker& operator=(ActorPicker&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineCollision* Collision_Ray;
	float4 CamPos;

	float4 PrevMousePos;
	float4 CurMousePos;
	float4 CurActorPos;
	class AxisActor* Axis;


	void SelectPickedActor();
	void UnSelect();
	void ClickCheck();
	void ClickAxisControl();
	void ClickPickableActor();
};

