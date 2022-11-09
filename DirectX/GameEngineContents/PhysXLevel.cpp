#include "PreCompile.h"
#include "PhysXLevel.h"

PhysXLevel::PhysXLevel() 
{
}

PhysXLevel::~PhysXLevel() 
{
}



// 각 시점마다 VirtualPhysXLevel의 시점 함수들을 호출해서
// 물리에 관련된 함수들을 실행시켜야 함.
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
