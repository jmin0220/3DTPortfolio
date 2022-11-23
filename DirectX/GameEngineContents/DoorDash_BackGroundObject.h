#pragma once

// Ό³Έν :
class DoorDash_BackGroundObject : public GameEngineActor
{
public:
	// constrcuter destructer
	DoorDash_BackGroundObject();
	~DoorDash_BackGroundObject();

	// delete Function
	DoorDash_BackGroundObject(const DoorDash_BackGroundObject& _Other) = delete;
	DoorDash_BackGroundObject(DoorDash_BackGroundObject&& _Other) noexcept = delete;
	DoorDash_BackGroundObject& operator=(const DoorDash_BackGroundObject& _Other) = delete;
	DoorDash_BackGroundObject& operator=(DoorDash_BackGroundObject&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	//void End() override;

	//void LevelStartEvent() override;
	//void LevelEndEvent() override;
private:
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;
};

