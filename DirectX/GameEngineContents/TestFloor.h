#pragma once

// Ό³Έν :
class TestFloor	:	public GameEngineActor
{
public:
	// constrcuter destructer
	TestFloor();
	~TestFloor();

	// delete Function
	TestFloor(const TestFloor& _Other) = delete;
	TestFloor(TestFloor&& _Other) noexcept = delete;
	TestFloor& operator=(const TestFloor& _Other) = delete;
	TestFloor& operator=(TestFloor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer;
};

