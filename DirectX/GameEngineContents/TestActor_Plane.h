#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TestActor_Plane : public GameEngineActor
{
public:
	// constrcuter destructer
	TestActor_Plane();
	~TestActor_Plane();

	// delete Function
	TestActor_Plane(const TestActor_Plane& _Other) = delete;
	TestActor_Plane(TestActor_Plane&& _Other) noexcept = delete;
	TestActor_Plane& operator=(const TestActor_Plane& _Other) = delete;
	TestActor_Plane& operator=(TestActor_Plane&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	std::shared_ptr<GameEngineCollision> Collision_;
	std::shared_ptr<GameEngineTextureRenderer> Renderer_;

};

