#include "PreCompile.h"
#include "DoorDashLevel.h"

#include "DoorDashStage.h"
#include "PlayerActor.h"

DoorDashLevel::DoorDashLevel() 
{
}

DoorDashLevel::~DoorDashLevel() 
{
}

void DoorDashLevel::Start()
{
	StageParentLevel::Start();
	MyStage_ = StageNum::STAGE1;
}

void DoorDashLevel::Update(float _DeltaTime)
{
	StageParentLevel::Update(_DeltaTime);
}

void DoorDashLevel::End()
{
	StageParentLevel::End();
}

void DoorDashLevel::LevelStartEvent()
{
	StageParentLevel::LevelStartEvent();

	std::shared_ptr<PlayerActor> Player = CreateActor<PlayerActor>();
	Player->CreatePhysXActors(GetScene(), GetPhysics());
	std::shared_ptr<DoorDashStage> Map = CreateActor<DoorDashStage>();
	Map->GetTransform().SetWorldPosition({30.0f, -200.0f, 30.0f});

}

void DoorDashLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
