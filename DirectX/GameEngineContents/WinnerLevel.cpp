#include "PreCompile.h"
#include "WinnerLevel.h"

#include "Winner.h"
#include "LobbyPlayer.h"
#include "WinnerBG.h"
#include "FloorActor.h"
#include "UISkyBoxActor.h"

WinnerLevel::WinnerLevel() 
	:ChairTime_(0.0f)
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
	ChairTime_ += _DeltaTime;
	if (ChairTime_ > 9.0f)
	{
		Chair_->Off();
	}
}

void WinnerLevel::End()
{
}

void WinnerLevel::LevelStartEvent()
{
	ChairTime_ = 0.0f;

	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
	
	//ContentsCore::GetInst()->LoadLevelResource(LEVELS::WINNNER);//경로설정
	BG_ = CreateActor<WinnerBG>();
	Sky_ = CreateActor<UISkyBoxActor>();

	Winner_ = CreateActor<Winner>();

	Player_ = CreateActor<LobbyPlayer>();
	Player_->GetTransform().SetWorldRotation({ 0,180,0 });
	Player_->GetTransform().SetWorldPosition({ 0,-15,0 });

	Player_->ChangeAnimationWin();

	Chair_ = CreateActor<FloorActor>();
	Chair_->On();
}

void WinnerLevel::LevelEndEvent()
{
	Sky_->Death();
	//BG_->Death();
	Winner_->Death();
	Player_->Death();
	Chair_->Death();

	ContentsCore::GetInst()->ReleaseCurLevelResource();
}
