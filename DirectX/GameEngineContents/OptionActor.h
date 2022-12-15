#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 로비에서 볼륨 조절 옵션창
class GameEngineUIRenderer;
class OptionActor : public GameEngineActor
{
public:
	// constrcuter destructer
	OptionActor();
	~OptionActor();

	// delete Function
	OptionActor(const OptionActor& _Other) = delete;
	OptionActor(OptionActor&& _Other) noexcept = delete;
	OptionActor& operator=(const OptionActor& _Other) = delete;
	OptionActor& operator=(OptionActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:
	std::shared_ptr<GameEngineUIRenderer> Renderer_;
	std::shared_ptr<GameEngineUIRenderer> Ball_;
	std::shared_ptr<GameEngineCollision> Collision_;

	GlobalBGM* bgm_;

	bool ColCheck_;
};

