#include "PreCompile.h"
#include "PlayerTestLevel.h"
#include <GameEngineCore/CoreMinimal.h>

#include "PlayerTestActor.h"

PlayerTestLevel::PlayerTestLevel() 
{
}

PlayerTestLevel::~PlayerTestLevel() 
{
}

void PlayerTestLevel::Start()
{


}

void PlayerTestLevel::Update(float _DeltaTime)
{

}

void PlayerTestLevel::End()
{
}

void PlayerTestLevel::LevelStartEvent()
{		
	// 리소스 로드
	ContentsCore::GetInst()->LoadLevelResource(LEVELS::PLAYER_TEST);
	//액터 생성
	//std::shared_ptr<GameEngineActor> Map = CreateActor<TestMapActor>();
	//std::shared_ptr<GameEngineActor> Wall = CreateActor<TestWallActor>();
	//Wall->GetTransform().SetWorldPosition({ 0,0,0 });
	//std::shared_ptr<GameEngineActor> Floor = CreateActor<TestFloor>();
	//Floor->GetTransform().SetWorldPosition({ 0,0,0 });
	Player = CreateActor<PlayerTestActor>();
	Player->GetTransform().SetWorldScale({ 100.0f, 100.0f, 100.0f });
}

void PlayerTestLevel::LevelEndEvent()
{
	Player->Death();
}

