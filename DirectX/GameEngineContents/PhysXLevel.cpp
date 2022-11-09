#include "PreCompile.h"
#include "PhysXLevel.h"

PhysXLevel::PhysXLevel() 
{
}

PhysXLevel::~PhysXLevel() 
{
}



// �� �������� VirtualPhysXLevel�� ���� �Լ����� ȣ���ؼ�
// ������ ���õ� �Լ����� ������Ѿ� ��.
void PhysXLevel::Start()
{
	VirtualPhysXLevel::Start();

	PhysXActor_ = CreateActor<PhysXActor>();
}

void PhysXLevel::Update(float _DeltaTIme)
{
	VirtualPhysXLevel::Update(_DeltaTIme);
}

void PhysXLevel::End()
{
	VirtualPhysXLevel::End();
}

void PhysXLevel::LevelStartEvent()
{
	VirtualPhysXLevel::LevelStartEvent();
}

void PhysXLevel::LevelEndEvent()
{
	VirtualPhysXLevel::LevelEndEvent();
}
