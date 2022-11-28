#pragma once

// Ό³Έν :
class Col_Goal	:	public GameEngineActor
{
public:
	// constrcuter destructer
	Col_Goal();
	~Col_Goal();

	// delete Function
	Col_Goal(const Col_Goal& _Other) = delete;
	Col_Goal(Col_Goal&& _Other) noexcept = delete;
	Col_Goal& operator=(const Col_Goal& _Other) = delete;
	Col_Goal& operator=(Col_Goal&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End();

	void LevelStartEvent() override;
private:
	std::shared_ptr<GameEngineCollision> GoalCol_;
};

