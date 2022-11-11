#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXBoxGeometryComponent.h"

// 물리를 사용해야하는 Actor는 GameEngineActor대신
// VirtualPhysXActor를 상속
class PhysXActor : public VirtualPhysXActor
{
public:
	// constrcuter destructer
	PhysXActor();
	~PhysXActor();

	// delete Function
	PhysXActor(const PhysXActor& _Other) = delete;
	PhysXActor(PhysXActor&& _Other) noexcept = delete;
	PhysXActor& operator=(const PhysXActor& _Other) = delete;
	PhysXActor& operator=(PhysXActor&& _Other) noexcept = delete;

protected:
	void Start() override;

	void LevelStartEvent() override;

	// ★반드시 생성해야함★★★★★★★★★★
	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) override;

private:
	std::shared_ptr<PhysXBoxGeometryComponent> PhysXBoxGeometry_;

};

