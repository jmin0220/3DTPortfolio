#pragma once

// Ό³Έν :
class Hex_ProPeller	:	GameEngineActor
{
public:
	// constrcuter destructer
	Hex_ProPeller();
	~Hex_ProPeller();

	// delete Function
	Hex_ProPeller(const Hex_ProPeller& _Other) = delete;
	Hex_ProPeller(Hex_ProPeller&& _Other) noexcept = delete;
	Hex_ProPeller& operator=(const Hex_ProPeller& _Other) = delete;
	Hex_ProPeller& operator=(Hex_ProPeller&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:

};

