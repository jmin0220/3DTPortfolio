#pragma once

// Ό³Έν :
class JumpClub_BackGroundObject : public GameEngineActor
{
public:
	// constrcuter destructer
	JumpClub_BackGroundObject();
	~JumpClub_BackGroundObject();

	// delete Function
	JumpClub_BackGroundObject(const JumpClub_BackGroundObject& _Other) = delete;
	JumpClub_BackGroundObject(JumpClub_BackGroundObject&& _Other) noexcept = delete;
	JumpClub_BackGroundObject& operator=(const JumpClub_BackGroundObject& _Other) = delete;
	JumpClub_BackGroundObject& operator=(JumpClub_BackGroundObject&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;

};

