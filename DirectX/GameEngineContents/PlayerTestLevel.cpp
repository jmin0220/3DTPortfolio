#include "PreCompile.h"
#include "PlayerTestLevel.h"
#include <GameEngineCore/CoreMinimal.h>

#include "PhysXHexgonTest.h"


PlayerTestLevel::PlayerTestLevel() 
{
}

PlayerTestLevel::~PlayerTestLevel() 
{
}

void PlayerTestLevel::Start()
{

	VirtualPhysXLevel::Start();


}

void PlayerTestLevel::Update(float _DeltaTime)
{
	VirtualPhysXLevel::Update(_DeltaTime);
}

void PlayerTestLevel::End()
{
	VirtualPhysXLevel::End();
}

void PlayerTestLevel::LevelStartEvent()
{		
	VirtualPhysXLevel::LevelStartEvent();

	PhysxHexTile_ = CreateActor<PhysXHexgonTest>();


	// 리소스 로드
	ContentsCore::GetInst()->LoadLevelResource(LEVELS::PLAYER_TEST);
}

void PlayerTestLevel::LevelEndEvent()
{
	VirtualPhysXLevel::LevelEndEvent();
	PhysxHexTile_->Death();
}

