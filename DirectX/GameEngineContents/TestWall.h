#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class TestWall : public GameEngineActor
{
public:
	// constrcuter destructer
	TestWall();
	~TestWall();

	// delete Function
	TestWall(const TestWall& _Other) = delete;
	TestWall(TestWall&& _Other) noexcept = delete;
	TestWall& operator=(const TestWall& _Other) = delete;
	TestWall& operator=(TestWall&& _Other) noexcept = delete;

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
	std::shared_ptr<class PhysicsObject> Wall;
	std::shared_ptr<class PhysicsObject> Wall2;
	float4 ResultColor;
};

