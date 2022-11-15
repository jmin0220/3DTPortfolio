#include "PreCompile.h"
#include "StageTestLevel.h"
#include "TestRainBow.h"
#include <GameEngineBase/magic_enum.hpp>
#include <GameEngineCore/ThirdParty/inc/json.h>
#include <GameEngineCore/CoreMinimal.h>
#include <iostream>
#include <fstream>

StageTestLevel::StageTestLevel() 
{
}

StageTestLevel::~StageTestLevel() 
{
}

void StageTestLevel::Start()
{
	MyStage_ = StageNum::STAGE1;
}
void StageTestLevel::Update(float _DeltaTime)
{

}
void StageTestLevel::End()
{

}

void StageTestLevel::LevelStartEvent()
{
	StageParentLevel::LevelStartEvent();
}
void StageTestLevel::LevelEndEvent()
{
}