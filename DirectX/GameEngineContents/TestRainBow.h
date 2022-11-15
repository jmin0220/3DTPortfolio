#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "PickableActor.h"

// Ό³Έν :
class TestRainBow	:	public GameEngineActor
{
public:
	// constrcuter destructer
	TestRainBow();
	~TestRainBow();

	// delete Function
	TestRainBow(const TestRainBow& _Other) = delete;
	TestRainBow(TestRainBow&& _Other) noexcept = delete;
	TestRainBow& operator=(const TestRainBow& _Other) = delete;
	TestRainBow& operator=(TestRainBow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:

};

