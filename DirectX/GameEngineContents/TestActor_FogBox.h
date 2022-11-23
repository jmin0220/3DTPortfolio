#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TestActor_FogBox : public GameEngineActor
{
public:
	// constrcuter destructer
	TestActor_FogBox();
	~TestActor_FogBox();

	// delete Function
	TestActor_FogBox(const TestActor_FogBox& _Other) = delete;
	TestActor_FogBox(TestActor_FogBox&& _Other) noexcept = delete;
	TestActor_FogBox& operator=(const TestActor_FogBox _Other) = delete;
	TestActor_FogBox& operator=(TestActor_FogBox&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	std::shared_ptr<GameEngineTextureRenderer> Renderer_;
	float4 Color_;
};

