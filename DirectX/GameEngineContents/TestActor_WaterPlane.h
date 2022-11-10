#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TestActor_WaterPlane : public GameEngineActor
{
public:
	// constrcuter destructer
	TestActor_WaterPlane();
	~TestActor_WaterPlane();

	// delete Function
	TestActor_WaterPlane(const TestActor_WaterPlane& _Other) = delete;
	TestActor_WaterPlane(TestActor_WaterPlane&& _Other) noexcept = delete;
	TestActor_WaterPlane& operator=(const TestActor_WaterPlane& _Other) = delete;
	TestActor_WaterPlane& operator=(TestActor_WaterPlane&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}


private:
	std::shared_ptr<GameEngineCollision> Collision_;
	std::shared_ptr<GameEngineTextureRenderer> Renderer_;
};

