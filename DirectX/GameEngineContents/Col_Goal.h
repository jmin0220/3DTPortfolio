#pragma once

// ???? :
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

	CollisionReturn CheckCol(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other);


public:
	static bool IsPlayerGoal_;

	static void SetIsPlayerGoal()
	{
		IsPlayerGoal_ = !IsPlayerGoal_;
	}

	static bool GetIsPlayerGoal_()
	{
		return IsPlayerGoal_;
	}
};

