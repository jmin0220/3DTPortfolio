#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SkyboxActor : public GameEngineActor
{
public:
	// constrcuter destructer
	SkyboxActor();
	~SkyboxActor();

	// delete Function
	SkyboxActor(const SkyboxActor& _Other) = delete;
	SkyboxActor(SkyboxActor&& _Other) noexcept = delete;
	SkyboxActor& operator=(const SkyboxActor& _Other) = delete;
	SkyboxActor& operator=(SkyboxActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> StaticRenderer_;
};

