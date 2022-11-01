#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class TestPlayer : public GameEngineActor
{
public:
	// constrcuter destructer
	TestPlayer();
	~TestPlayer();

	// delete Function
	TestPlayer(const TestPlayer& _Other) = delete;
	TestPlayer(TestPlayer&& _Other) noexcept = delete;
	TestPlayer& operator=(const TestPlayer& _Other) = delete;
	TestPlayer& operator=(TestPlayer&& _Other) noexcept = delete;

	GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	GameEngineTextureRenderer* Renderer;
	class PhysicsObject* Collision;
	float4 ResultColor;
	GameEngineStateManager MoveFSM;
};

