#include "PreCompile.h"
#include "JumpClubLevel.h"

// ������Ʈ ����
#include "JumpClub_BackGroundObject.h"

JumpClubLevel::JumpClubLevel() 
{
}

JumpClubLevel::~JumpClubLevel() 
{
}

void JumpClubLevel::Start()
{
	StageParentLevel::Start();
	MyStage_ = StageNum::STAGE2;

}

void JumpClubLevel::Update(float _DeltaTime)
{
	StageParentLevel::Update(_DeltaTime);
}

void JumpClubLevel::End()
{
	StageParentLevel::End();
}

void JumpClubLevel::LevelStartEvent()
{
	StageParentLevel::LevelStartEvent();
	BackGroundObj_ = CreateActor<JumpClub_BackGroundObject>();
}

void JumpClubLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
