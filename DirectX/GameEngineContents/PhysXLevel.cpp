#include "PreCompile.h"
#include "PhysXLevel.h"
#include "PlayerActor.h"

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

	Player_ = CreateActor<PlayerActor>();

	// InitPhysic는 레벨이 시작될때 실행되므로 LevelStartEvent가 실행되기 전에 포지션을 결정해야함.
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
	// 리소스 로드
	ContentsCore::GetInst()->LoadLevelResource(LEVELS::PHYSX_TEST);

	VirtualPhysXLevel::LevelStartEvent();
}

void PhysXLevel::LevelEndEvent()
{
	VirtualPhysXLevel::LevelEndEvent();

	//Player_->Death();

	// 리소스 해제
	ContentsCore::GetInst()->ReleaseCurLevelResource();
}
