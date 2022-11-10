#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : StartGameTitleActor가 꺼지면 켜지는 목표 설명바
class GoalTipActor : public GameEngineActor
{
public:
	// constrcuter destructer
	GoalTipActor();
	~GoalTipActor();

	// delete Function
	GoalTipActor(const GoalTipActor& _Other) = delete;
	GoalTipActor(GoalTipActor&& _Other) noexcept = delete;
	GoalTipActor& operator=(const GoalTipActor& _Other) = delete;
	GoalTipActor& operator=(GoalTipActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	//void LevelStartEvent() override;
private:
	std::shared_ptr<GameEngineUIRenderer> Renderer_;
	std::shared_ptr<GameEngineFontRenderer> Font_;
};

