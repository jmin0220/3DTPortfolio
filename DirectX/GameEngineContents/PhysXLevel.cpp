#include "PreCompile.h"
#include "PhysXLevel.h"
#include "PlayerActor.h"

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

	Player_ = CreateActor<PlayerActor>();

	// InitPhysic�� ������ ���۵ɶ� ����ǹǷ� LevelStartEvent�� ����Ǳ� ���� �������� �����ؾ���.
	Player_->GetTransform().SetWorldPosition({ 0.0f, 100.0f, 0.0f });
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
	// ���ҽ� �ε�
	ContentsCore::GetInst()->LoadLevelResource(LEVELS::PHYSX_TEST);

	VirtualPhysXLevel::LevelStartEvent();
}

void PhysXLevel::LevelEndEvent()
{
	VirtualPhysXLevel::LevelEndEvent();

	//Player_->Death();

	// ���ҽ� ����
	ContentsCore::GetInst()->ReleaseCurLevelResource();
}
