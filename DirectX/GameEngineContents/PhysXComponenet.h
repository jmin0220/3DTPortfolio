#pragma once

// Ό³Έν :
class PhysXComponenet : public GameEngineTransformComponent
{
public:
	// constrcuter destructer
	PhysXComponenet();
	~PhysXComponenet();

	// delete Function
	PhysXComponenet(const PhysXComponenet& _Other) = delete;
	PhysXComponenet(PhysXComponenet&& _Other) noexcept = delete;
	PhysXComponenet& operator=(const PhysXComponenet& _Other) = delete;
	PhysXComponenet& operator=(PhysXComponenet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

