#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ShaderTutorialActor : public GameEngineActor
{
public:
	// constrcuter destructer
	ShaderTutorialActor();
	~ShaderTutorialActor();

	// delete Function
	ShaderTutorialActor(const ShaderTutorialActor& _Other) = delete;
	ShaderTutorialActor(ShaderTutorialActor&& _Other) noexcept = delete;
	ShaderTutorialActor& operator=(const ShaderTutorialActor& _Other) = delete;
	ShaderTutorialActor& operator=(ShaderTutorialActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

