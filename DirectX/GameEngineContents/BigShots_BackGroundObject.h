#pragma once

// Ό³Έν :
class BigShots_BackGroundObject : public GameEngineActor
{
public:
	// constrcuter destructer
	BigShots_BackGroundObject();
	~BigShots_BackGroundObject();

	// delete Function
	BigShots_BackGroundObject(const BigShots_BackGroundObject& _Other) = delete;
	BigShots_BackGroundObject(BigShots_BackGroundObject&& _Other) noexcept = delete;
	BigShots_BackGroundObject& operator=(const BigShots_BackGroundObject& _Other) = delete;
	BigShots_BackGroundObject& operator=(BigShots_BackGroundObject&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;

};

