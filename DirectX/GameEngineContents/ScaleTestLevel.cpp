#include "PreCompile.h"
#include "ScaleTestLevel.h"
#include <GameEngineCore/CoreMinimal.h>

#include "TestMapActor.h"
#include "TestCharacterAnimation.h"

ScaleTestLevel::ScaleTestLevel() 
{
}

ScaleTestLevel::~ScaleTestLevel() 
{
}

void ScaleTestLevel::Start()
{


}

void ScaleTestLevel::Update(float _DeltaTime)
{

}

void ScaleTestLevel::End()
{
}

void ScaleTestLevel::LevelStartEvent()
{		
	// 리소스 로드
	ContentsCore::GetInst()->LoadLevelResource(LEVELS::SCALE_TEST);
	//액터 생성
	std::shared_ptr<GameEngineActor> Map = CreateActor<TestMapActor>();
	std::shared_ptr<GameEngineActor> Cha_Ani = CreateActor<TestCharacterAnimation>();
}

void ScaleTestLevel::LevelEndEvent()
{
}

