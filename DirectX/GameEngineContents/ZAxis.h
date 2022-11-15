#pragma once

// Ό³Έν :
class ZAxis	: public GameEngineActor
{
public:
	// constrcuter destructer
	ZAxis();
	~ZAxis();

	// delete Function
	ZAxis(const ZAxis& _Other) = delete;
	ZAxis(ZAxis&& _Other) noexcept = delete;
	ZAxis& operator=(const ZAxis& _Other) = delete;
	ZAxis& operator=(ZAxis&& _Other) noexcept = delete;

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

