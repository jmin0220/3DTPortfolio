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
	StageParentLevel::Start();
	MyStage_ = StageNum::STAGE4;
}

void HexAGoneLevel::Update(float _DeltaTime)
{
	StageParentLevel::Update(_DeltaTime);
}

void HexAGoneLevel::End()
{
	StageParentLevel::End();
}

void HexAGoneLevel::LevelStartEvent()
{

	StageParentLevel::LevelStartEvent();
	//ContentsCore::GetInst()->LoadLevelResource(LEVELS::STAGE04_HEX_A_GONE);
	std::shared_ptr<GameEngineActor> TestMap = CreateActor<TestMapActor>();
}

void HexAGoneLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
