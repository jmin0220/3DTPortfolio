#pragma once

// Ό³Έν :
class Col_Trigger	:	public GameEngineActor
{
public:
	// constrcuter destructer
	Col_Trigger();
	~Col_Trigger();

	// delete Function
	Col_Trigger(const Col_Trigger& _Other) = delete;
	Col_Trigger(Col_Trigger&& _Other) noexcept = delete;
	Col_Trigger& operator=(const Col_Trigger& _Other) = delete;
	Col_Trigger& operator=(Col_Trigger&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End();

	void LevelStartEvent() override;
private:
	std::shared_ptr<GameEngineCollision> TriggerCol_;
};

