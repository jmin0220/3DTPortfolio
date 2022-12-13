#pragma once

// Ό³Έν :
class BigShots_Cannon : public GameEngineActor
{
public:
	// constrcuter destructer
	BigShots_Cannon();
	~BigShots_Cannon();

	// delete Function
	BigShots_Cannon(const BigShots_Cannon& _Other) = delete;
	BigShots_Cannon(BigShots_Cannon&& _Other) noexcept = delete;
	BigShots_Cannon& operator=(const BigShots_Cannon& _Other) = delete;
	BigShots_Cannon& operator=(BigShots_Cannon&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	std::shared_ptr<GameEngineFBXAnimationRenderer> FbxRenderer_;
	std::shared_ptr<GameEngineFBXStaticRenderer> FbxFloatingRenderer_;
	std::shared_ptr<GameEngineFBXStaticRenderer> FbxSpinnerRenderer_;

	float ShootingTime_;
};

