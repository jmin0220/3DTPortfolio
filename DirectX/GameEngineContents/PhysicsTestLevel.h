#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class PhysicsTestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PhysicsTestLevel();
	~PhysicsTestLevel();

	// delete Function
	PhysicsTestLevel(const PhysicsTestLevel& _Other) = delete;
	PhysicsTestLevel(PhysicsTestLevel&& _Other) noexcept = delete;
	PhysicsTestLevel& operator=(const PhysicsTestLevel& _Other) = delete;
	PhysicsTestLevel& operator=(PhysicsTestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

