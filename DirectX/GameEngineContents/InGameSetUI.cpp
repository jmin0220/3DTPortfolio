#include "PreCompile.h"
#include "InGameSetUI.h"
#include "CountDown.h"
#include "GameFail.h"
#include "GameSuccess.h"
#include "GoalTipActor.h"
#include "RoundEnd.h"
#include "StartGameTitleActor.h"
#include "SuccessCount.h"

InGameSetUI::InGameSetUI() 
{
}

InGameSetUI::~InGameSetUI() 
{
}

void InGameSetUI::Start()
{
}

void InGameSetUI::Update(float _DeltaTime)
{
	if (CountDownStart_ == true)
	{
		CountDown_->CountDownStart();
	}
}

void InGameSetUI::LevelStartEvent()
{
	CountDownStart_ = true;

	GameFail_ = GetLevel()->CreateActor<GameFail>();
	GameSuccess_ = GetLevel()->CreateActor<GameSuccess>();
	GoalTipActor_ = GetLevel()->CreateActor<GoalTipActor>();
	RoundEnd_ = GetLevel()->CreateActor<RoundEnd>();
	StartGameTitle_ = GetLevel()->CreateActor<StartGameTitleActor>();
	SuccessCount_ = GetLevel()->CreateActor<SuccessCount>();
	CountDown_ = GetLevel()->CreateActor<CountDown>();

	RoundEnd_->GetTransform().SetWorldPosition({ 0.0f,-200.0f });
	GameFail_->GetTransform().SetWorldPosition({ 0.0f,200.0f });
}

void InGameSetUI::LevelEndEvent()
{
	CountDownStart_ = false;
}
