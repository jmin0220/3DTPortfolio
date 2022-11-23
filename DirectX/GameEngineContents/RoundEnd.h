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
	void Reset();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
private:
	std::shared_ptr<GameEngineUIRenderer> SetRenderer_;
	std::shared_ptr<GameEngineUIRenderer> CrownRenderer_;
	std::shared_ptr<GameEngineUIRenderer> SideCircle1_;
	std::shared_ptr<GameEngineUIRenderer> SideCircle2_;
	std::shared_ptr<GameEngineUIRenderer> SideCircle3_;
	std::shared_ptr<GameEngineUIRenderer> SideCircle4_;
	std::shared_ptr<GameEngineUIRenderer> Text_;

	bool Pop_;
	bool IsOut_;
	float PopUpTime_;
	float4 SlicePos_;
};

