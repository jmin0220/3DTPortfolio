#pragma once


// Ό³Έν :
class Chevron	:	public GameEngineActor
{
public:
	// constrcuter destructer
	Chevron();
	~Chevron();

	// delete Function
	Chevron(const Chevron& _Other) = delete;
	Chevron(Chevron&& _Other) noexcept = delete;
	Chevron& operator=(const Chevron& _Other) = delete;
	Chevron& operator=(Chevron&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	float RotY;
	std::shared_ptr<GameEngineFBXStaticRenderer> ChevronRenderer_;
	std::shared_ptr<GameEngineFBXStaticRenderer> PropellerRenderer_;
};

