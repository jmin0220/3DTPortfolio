#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class AXISMODE
{
	MOVE,
	ROT,
};

// Ό³Έν :
class ActorAxis : public GameEngineActor
{
public:
	void ChaneMode(AXISMODE _Mode)
	{
		Mode_ = _Mode;
	}

private:
	AXISMODE Mode_;

public:
	// constrcuter destructer
	ActorAxis();
	~ActorAxis();

	// delete Function
	ActorAxis(const ActorAxis& _Other) = delete;
	ActorAxis(ActorAxis&& _Other) noexcept = delete;
	ActorAxis& operator=(const ActorAxis& _Other) = delete;
	ActorAxis& operator=(ActorAxis&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineCollision> Collision_;
	std::shared_ptr<GameEngineActor> AxisMove_;
	std::shared_ptr<GameEngineActor> AxisRot_; 

	GameEngineStateManager StateManager_;

	void IdleModeStart(const StateInfo& _Info);
	void IdleModeUpdate(float _DeltaTime, const StateInfo& _Info);

	void MoveModeStart(const StateInfo& _Info);
	void MoveModeUpdate(float _DeltaTime, const StateInfo& _Info);

	void RotModeStart(const StateInfo& _Info);
	void RotModeUpdate(float _DeltaTime, const StateInfo& _Info);
};

