#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class ShaderTutorialLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	ShaderTutorialLevel();
	~ShaderTutorialLevel();

	// delete Function
	ShaderTutorialLevel(const ShaderTutorialLevel& _Other) = delete;
	ShaderTutorialLevel(ShaderTutorialLevel&& _Other) noexcept = delete;
	ShaderTutorialLevel& operator=(const ShaderTutorialLevel& _Other) = delete;
	ShaderTutorialLevel& operator=(ShaderTutorialLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	std::shared_ptr<GameEngineLight> LightObject;
};

