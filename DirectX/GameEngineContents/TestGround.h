#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class TestGround : public GameEngineActor
{
public:
	// constrcuter destructer
	TestGround();
	~TestGround();

	// delete Function
	TestGround(const TestGround& _Other) = delete;
	TestGround(TestGround&& _Other) noexcept = delete;
	TestGround& operator=(const TestGround& _Other) = delete;
	TestGround& operator=(TestGround&& _Other) noexcept = delete;

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
};

