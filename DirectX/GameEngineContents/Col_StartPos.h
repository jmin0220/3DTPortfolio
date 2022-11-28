#pragma once

// Ό³Έν :
class Col_StartPos	:	public GameEngineActor
{
public:
	// constrcuter destructer
	Col_StartPos();
	~Col_StartPos();

	// delete Function
	Col_StartPos(const Col_StartPos& _Other) = delete;
	Col_StartPos(Col_StartPos&& _Other) noexcept = delete;
	Col_StartPos& operator=(const Col_StartPos& _Other) = delete;
	Col_StartPos& operator=(Col_StartPos&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End();

	void LevelStartEvent() override;
private:
	std::shared_ptr<GameEngineCollision> StartCol_;
};

