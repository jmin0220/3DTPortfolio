#pragma once


// 설명 :
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
	static int Num;
	int MyNum;
	float RotY;
	std::shared_ptr<GameEngineFBXStaticRenderer> ChevronRenderer_;
	std::shared_ptr<GameEngineFBXStaticRenderer> PropellerRenderer_;

	// 서버
	bool ServerActivated_;
};

