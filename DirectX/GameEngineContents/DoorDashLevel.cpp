#include "PreCompile.h"
#include "DoorDashLevel.h"

#include "DoorDashStage.h"

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

	std::shared_ptr<DoorDashStage> Map = CreateActor<DoorDashStage>();
}

void DoorDashLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
