#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ???? :
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

	std::shared_ptr<GameEngineTextureRenderer> GetRenderer()
	{
		return Renderer;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	std::shared_ptr<GameEngineTextureRenderer> Renderer;
	std::shared_ptr<class PhysicsObject> Collision;
	float4 ResultColor;
};

