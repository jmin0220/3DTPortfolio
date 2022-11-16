#include "PreCompile.h"
#include "HexAGoneLevel.h"

//오브젝트액터
#include "TestMapActor.h"

HexAGoneLevel::HexAGoneLevel() 
{
}

HexAGoneLevel::~HexAGoneLevel() 
{
}

void HexAGoneLevel::Start()
{
	VirtualPhysXLevel::Start();
	MyStage_ = StageNum::STAGE4;
}

void HexAGoneLevel::Update(float _DeltaTime)
{
	VirtualPhysXLevel::Update(_DeltaTime);
}

void HexAGoneLevel::End()
{
	VirtualPhysXLevel::End();
}

void HexAGoneLevel::LevelStartEvent()
{
	VirtualPhysXLevel::LevelStartEvent();
	StageParentLevel::LevelStartEvent();
	//ContentsCore::GetInst()->LoadLevelResource(LEVELS::STAGE04_HEX_A_GONE);
	std::shared_ptr<GameEngineActor> TestMap = CreateActor<TestMapActor>();
}

void HexAGoneLevel::LevelEndEvent()
{
	VirtualPhysXLevel::LevelEndEvent();
	ContentsCore::GetInst()->ReleaseCurLevelResource();
}
