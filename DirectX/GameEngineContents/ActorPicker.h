#pragma once
#include <GameEngineCore/GameEngineActor.h>


class PickableActor;
class ActorPicker : public GameEngineActor
{
public:
	static std::set<std::shared_ptr<PickableActor>> PickedActors;
	static std::shared_ptr<PickableActor> PickedActor;
	static std::shared_ptr<PickableActor> ClickedActor;
	static std::shared_ptr<PickableActor> SelectedActor;
	//static std::weak_ptr<GameEngineActor> CurActor;

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
	std::shared_ptr<GameEngineCollision> Collision_Ray_;
	float4 CamPos_;

	float4 PrevMousePos_;
	float4 CurMousePos_;
	float4 CurActorPos_;

	std::shared_ptr<class ActorAxis> Axis_;


	void SelectPickedActor();
	void UnSelect();
	void ClickCheck();
	void ClickAxisControl();
	void ClickPickableActor();
};

