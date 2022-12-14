#include "PreCompile.h"
#include "ScaleTestLevel.h"
#include <GameEngineCore/CoreMinimal.h>

#include "TestMapActor.h"
#include "TestFloor.h"
#include "TestWallActor.h"
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
	//std::shared_ptr<GameEngineActor> Map = CreateActor<TestMapActor>();
	//std::shared_ptr<GameEngineActor> Wall = CreateActor<TestWallActor>();
	//Wall->GetTransform().SetWorldPosition({ 0,0,0 });
	//std::shared_ptr<GameEngineActor> Floor = CreateActor<TestFloor>();
	//Floor->GetTransform().SetWorldPosition({ 0,0,0 });
	Cha_Ani = CreateActor<TestCharacterAnimation>();
	Cha_Ani->GetTransform().SetWorldPosition({ 0,1.3f,0.0f });
	Cha_Ani->GetTransform().SetWorldScale({ 100, 100, 100});
}

void ScaleTestLevel::LevelEndEvent()
{
	ContentsCore::GetInst()->ReleaseCurLevelResource();
	Cha_Ani->Death();
}

