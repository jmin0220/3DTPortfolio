#include "PreCompile.h"
#include "WinnerLevel.h"

#include "Winner.h"
#include "LobbyPlayer.h"

WinnerLevel::WinnerLevel() 
{
}

WinnerLevel::~WinnerLevel() 
{
}

void WinnerLevel::Start()
{
}

void WinnerLevel::Update(float _DeltaTime)
{
}

void WinnerLevel::End()
{
}

void WinnerLevel::LevelStartEvent()
{
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	ContentsCore::GetInst()->LoadLevelResource(LEVELS::LOBBY);//경로설정

	Winner_ = CreateActor<Winner>();
	Player_ = CreateActor<LobbyPlayer>();
	Player_->GetTransform().SetWorldRotation({ 0,180,0 });
	Player_->GetTransform().SetWorldPosition({ 0,-15,0 });

	Player_->ChangeAnimationWin();
}

void WinnerLevel::LevelEndEvent()
{
	Winner_->Death();
	Player_->Death();
}
