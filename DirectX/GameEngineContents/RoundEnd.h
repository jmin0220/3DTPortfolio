#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class RoundEnd : public GameEngineActor
{
public:
	// constrcuter destructer
	RoundEnd();
	~RoundEnd();

	// delete Function
	RoundEnd(const RoundEnd& _Other) = delete;
	RoundEnd(RoundEnd&& _Other) noexcept = delete;
	RoundEnd& operator=(const RoundEnd& _Other) = delete;
	RoundEnd& operator=(RoundEnd&& _Other) noexcept = delete;

	void StartAnimation();
	void EndAnimation();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
private:
	GameEngineUIRenderer* SetRenderer_;
	GameEngineUIRenderer* SideCircle1_;
	GameEngineUIRenderer* SideCircle2_;
	GameEngineUIRenderer* SideCircle3_;
	GameEngineUIRenderer* SideCircle4_;
	GameEngineUIRenderer* Text_;

	bool Pop_;
	bool IsOut_;
	float PopUpTime_;
};

