#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class TestBox : public GameEngineActor
{
public:
	// constrcuter destructer
	TestBox();
	~TestBox();

	// delete Function
	TestBox(const TestBox& _Other) = delete;
	TestBox(TestBox&& _Other) noexcept = delete;
	TestBox& operator=(const TestBox& _Other) = delete;
	TestBox& operator=(TestBox&& _Other) noexcept = delete;

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
	GameEngineCollision* Collision;
};

