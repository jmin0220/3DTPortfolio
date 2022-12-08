#pragma once

// Ό³Έν :
class BigShots_Spinner : public GameEngineActor
{
public:
	// constrcuter destructer
	BigShots_Spinner();
	~BigShots_Spinner();

	// delete Function
	BigShots_Spinner(const BigShots_Spinner& _Other) = delete;
	BigShots_Spinner(BigShots_Spinner&& _Other) noexcept = delete;
	BigShots_Spinner& operator=(const BigShots_Spinner& _Other) = delete;
	BigShots_Spinner& operator=(BigShots_Spinner&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> FBXRenderer_;

};

