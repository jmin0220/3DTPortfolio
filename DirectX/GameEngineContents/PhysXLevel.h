#pragma once
#include "VirtualPhysXLevel.h"
#include "PhysXActor.h"

// ������ ����ؾ� �ϴ� Scene�� GameEngineLevel���
// VirtualPhysXLevel�� ��� ���� ��
class PlayerActor;
class PhysXLevel : public VirtualPhysXLevel
{
public:
	// constrcuter destructer
	PhysXLevel();
	~PhysXLevel();

	// delete Function
	PhysXLevel(const PhysXLevel& _Other) = delete;
	PhysXLevel(PhysXLevel&& _Other) noexcept = delete;
	PhysXLevel& operator=(const PhysXLevel& _Other) = delete;
	PhysXLevel& operator=(PhysXLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTIme) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

	std::shared_ptr<PhysXActor> PhysXActor_;


private:

};

