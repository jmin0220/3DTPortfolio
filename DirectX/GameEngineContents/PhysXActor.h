#pragma once
#include "VirtualPhysXActor.h"
#include "PhysXBoxGeometryComponent.h"

// ������ ����ؾ��ϴ� Actor�� GameEngineActor���
// VirtualPhysXActor�� ���
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

	// �ڹݵ�� �����ؾ��ԡڡڡڡڡڡڡڡڡڡ�
	void CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) override;

private:
	std::shared_ptr<PhysXBoxGeometryComponent> PhysXBoxGeometry_;

};

