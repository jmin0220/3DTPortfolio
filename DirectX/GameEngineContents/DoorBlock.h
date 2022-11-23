#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXBoxGeometryComponent.h"

// Ό³Έν :
class DoorBlock	:	public VirtualPhysXActor
{
public:
	// constrcuter destructer
	DoorBlock();
	~DoorBlock();

	// delete Function
	DoorBlock(const DoorBlock& _Other) = delete;
	DoorBlock(DoorBlock&& _Other) noexcept = delete;
	DoorBlock& operator=(const DoorBlock& _Other) = delete;
	DoorBlock& operator=(DoorBlock&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelStartEvent() override;

	void OffEvent();
	void OnEvent();

	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) override;

private:
	float Speed_;

	std::shared_ptr<PhysXBoxGeometryComponent> PhysXBoxGeometry_;
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer_;

};

