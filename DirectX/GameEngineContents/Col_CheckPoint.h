#pragma once

// Ό³Έν :
class Col_CheckPoint	:	public GameEngineActor
{
public:
	// constrcuter destructer
	Col_CheckPoint();
	~Col_CheckPoint();

	// delete Function
	Col_CheckPoint(const Col_CheckPoint& _Other) = delete;
	Col_CheckPoint(Col_CheckPoint&& _Other) noexcept = delete;
	Col_CheckPoint& operator=(const Col_CheckPoint& _Other) = delete;
	Col_CheckPoint& operator=(Col_CheckPoint&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End();

	void LevelStartEvent() override;
private:
	std::shared_ptr<GameEngineCollision> CheckPointCol_;
};

