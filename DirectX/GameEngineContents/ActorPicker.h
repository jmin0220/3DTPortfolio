#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : MapEditor레벨 전용으로 객체를 여러개 생성하면 안됨
class ActorPicker : public GameEngineActor
{
public:
	static std::set<std::shared_ptr<GameEngineActor>> PickedActors;
	static std::shared_ptr<GameEngineActor> PickedActor;
	static std::shared_ptr<GameEngineActor> ClickedActor;
	static std::shared_ptr<GameEngineActor> SelectedActor;
	static std::shared_ptr<GameEngineActor> CurActor;

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
	std::shared_ptr<GameEngineCollision> Collision_Ray;
	float4 CamPos;

	float4 PrevMousePos;
	float4 CurMousePos;
	float4 CurActorPos;
	std::shared_ptr<class AxisActor> Axis;


	void SelectPickedActor();
	void UnSelect();
	void ClickCheck();
	void ClickAxisControl();
	void ClickPickableActor();
};

