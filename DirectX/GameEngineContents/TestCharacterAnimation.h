#pragma once

// Ό³Έν :
class TestCharacterAnimation	:	public GameEngineActor
{
public:
	// constrcuter destructer
	TestCharacterAnimation();
	~TestCharacterAnimation();

	// delete Function
	TestCharacterAnimation(const TestCharacterAnimation& _Other) = delete;
	TestCharacterAnimation(TestCharacterAnimation&& _Other) noexcept = delete;
	TestCharacterAnimation& operator=(const TestCharacterAnimation& _Other) = delete;
	TestCharacterAnimation& operator=(TestCharacterAnimation&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:

};

