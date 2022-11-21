#include "PreCompile.h"
#include "LobbySetUI.h"
#include "CrownCount.h"
#include "NamePlate.h"
#include "NoneButton.h"
#include "NoneMoney.h"
#include "PlayButton.h"
#include "SelectShowButton.h"
#include "TopMenu.h"
#include "Cursor.h"

LobbySetUI::LobbySetUI() 
	:IsLevelOn_(false)
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
	Time_ += (_DeltaTime * 5.0f);

	if (IsLevelOn_ == true)
	{
		Circle1_->GetTransform().SetWorldScale({ CircleSize_.x  + Time_, CircleSize_.y  + Time_, 1.0f });
		Circle2_->GetTransform().SetWorldScale({ CircleSize_.x + 4.0f + (Time_*2.f), CircleSize_.y + 4.0f + (Time_ * 2.f), 1.0f });

		if (Time_ > 125.0f)
		{
			Circle1_->GetTransform().SetWorldScale({ 1.0f,1.0f,1.0f });
			Circle2_->GetTransform().SetWorldScale({ 2.0f,2.0f,1.0f });
			Time_ = 0.0f;
		}
	}
}

void LobbySetUI::LevelStartEvent()
{
	CircleSize_ = { 1,1 };
	IsLevelOn_ = true;
	Time_ = 0.0f;

	BG_ = CreateComponent<GameEngineTextureRenderer>();
	BG_->SetTexture("LobbyBG.png");
	BG_->SetPivot(PIVOTMODE::CENTER);
	BG_->GetTransform().SetWorldScale({ 1600,900 });
	BG_->GetTransform().SetWorldPosition({ 0,0,1500 });//1500이 맥스거리..? 그 이상하면 퍼런배경 드러남

	Circle1_ = CreateComponent<GameEngineTextureRenderer>();
	Circle1_->SetTexture("Circle1.png");
	Circle1_->SetPivot(PIVOTMODE::CENTER);
	Circle1_->GetTransform().SetWorldScale({ 1,1,1 });

	Circle2_ = CreateComponent<GameEngineTextureRenderer>();
	Circle2_->SetTexture("Circle2.png");
	Circle2_->SetPivot(PIVOTMODE::CENTER);
	Circle2_->GetTransform().SetWorldScale({ 5,5,1 });

	CrownCount_ = GetLevel()->CreateActor<CrownCount>();
	NamePlate_ = GetLevel()->CreateActor<NamePlate>();
	NoneButton_ = GetLevel()->CreateActor<NoneButton>();
	NoneMoney_ = GetLevel()->CreateActor<NoneMoney>();
	PlayButton_ = GetLevel()->CreateActor<PlayButton>();
	SelectShowButton_ = GetLevel()->CreateActor<SelectShowButton>();
	TopMenu_ = GetLevel()->CreateActor<TopMenu>();
	Mouse_ = GetLevel()->CreateActor<Cursor>();
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
	Mouse_->GetLevel()->Death();
	IsLevelOn_ = false;
}

