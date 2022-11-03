#pragma once

// Ό³Έν :
class TestMapActor	:	public GameEngineActor
{
public:
	// constrcuter destructer
	TestMapActor();
	~TestMapActor();

	// delete Function
	TestMapActor(const TestMapActor& _Other) = delete;
	TestMapActor(TestMapActor&& _Other) noexcept = delete;
	TestMapActor& operator=(const TestMapActor& _Other) = delete;
	TestMapActor& operator=(TestMapActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:

};

