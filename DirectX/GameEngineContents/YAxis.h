#pragma once

// Ό³Έν :
class YAxis	: public GameEngineActor
{
public:
	// constrcuter destructer
	YAxis();
	~YAxis();

	// delete Function
	YAxis(const YAxis& _Other) = delete;
	YAxis(YAxis&& _Other) noexcept = delete;
	YAxis& operator=(const YAxis& _Other) = delete;
	YAxis& operator=(YAxis&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	std::shared_ptr<GameEngineCollision> Collision;
public:
	std::shared_ptr<GameEngineCollision> GetCollision()
	{
		return Collision;
	}
};

