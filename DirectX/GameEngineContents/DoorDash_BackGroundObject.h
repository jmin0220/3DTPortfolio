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

private:

};

