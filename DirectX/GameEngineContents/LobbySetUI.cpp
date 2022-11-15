#include "PreCompile.h"
#include "LobbySetUI.h"
#include "CrownCount.h"
#include "NamePlate.h"
#include "NoneButton.h"
#include "NoneMoney.h"
#include "PlayButton.h"
#include "SelectShowButton.h"
#include "TopMenu.h"

LobbySetUI::LobbySetUI() 
{
}

LobbySetUI::~LobbySetUI() 
{
}

void LobbySetUI::Start()
{
}

void LobbySetUI::Update(float _DeltaTime)
{
}

void LobbySetUI::LevelStartEvent()
{
	CrownCount_ = GetLevel()->CreateActor<CrownCount>();
	NamePlate_ = GetLevel()->CreateActor<NamePlate>();
	NoneButton_ = GetLevel()->CreateActor<NoneButton>();
	NoneMoney_ = GetLevel()->CreateActor<NoneMoney>();
	PlayButton_ = GetLevel()->CreateActor<PlayButton>();
	SelectShowButton_ = GetLevel()->CreateActor<SelectShowButton>();
	TopMenu_ = GetLevel()->CreateActor<TopMenu>();
}

void LobbySetUI::LevelEndEvent()
{
	CrownCount_->GetLevel()->Death();
	NamePlate_->GetLevel()->Death();
	NoneButton_->GetLevel()->Death();
	NoneMoney_->GetLevel()->Death();
	PlayButton_->GetLevel()->Death();
	SelectShowButton_->GetLevel()->Death();
	TopMenu_->GetLevel()->Death();
}

