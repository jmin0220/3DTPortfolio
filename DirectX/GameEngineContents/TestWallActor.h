#pragma once

// Ό³Έν :
class TestWallActor	:	public GameEngineActor
{
public:
	// constrcuter destructer
	TestWallActor();
	~TestWallActor();

	// delete Function
	TestWallActor(const TestWallActor& _Other) = delete;
	TestWallActor(TestWallActor&& _Other) noexcept = delete;
	TestWallActor& operator=(const TestWallActor& _Other) = delete;
	TestWallActor& operator=(TestWallActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};
private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer;
};

