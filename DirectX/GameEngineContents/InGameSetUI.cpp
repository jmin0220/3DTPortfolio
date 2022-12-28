#include "PreCompile.h"
#include "InGameSetUI.h"
#include "CountDown.h"
#include "GameFail.h"
#include "GameSuccess.h"
#include "GoalTipActor.h"
#include "RoundEnd.h"
#include "StartGameTitleActor.h"
#include "SuccessCount.h"

void InGameSetUI::CountdownStart()
{
	CountDown_->Reset();
	CountDown_->On();
}

bool InGameSetUI::IsCountDownEnd()
{
	return CountDown_->CountDownEnd();
}

void InGameSetUI::OnOffSubTitle()
{
	StartGameTitle_->SetTitleText("게임제목", "부가설명 ㅇㅅㅇ", "UI_Medal_Icon_DoorDash.png");
	StartGameTitle_->OnOffSwitch();
	StartGameTitle_->Reset();
}

void InGameSetUI::OnOffSuccessCount()
{
	SuccessCount_->OnOffSwitch();
}

void InGameSetUI::OffSuccessCount()
{
	SuccessCount_->Off();
}

void InGameSetUI::OnSuccessCount()
{
	SuccessCount_->On();
}

void InGameSetUI::OnOffEnd()
{
	RoundEnd_->OnOffSwitch();
	RoundEnd_->Reset();
}

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

	if (true == GameEngineInput::GetInst()->IsDown("Fail"))
	{
		GameFail_->OnOffSwitch();
		GameFail_->Reset();
	}

	if (true == GameEngineInput::GetInst()->IsDown("Success"))
	{
		GameSuccess_->OnOffSwitch();
		GameSuccess_->Reset();	
	}

	if (true == GameEngineInput::GetInst()->IsDown("End"))
	{
		RoundEnd_->OnOffSwitch();
		RoundEnd_->Reset();
	}

	if (true == GameEngineInput::GetInst()->IsDown("SubTitle"))
	{
		StartGameTitle_->SetTitleText("게임제목", "부가설명 ㅇㅅㅇ", "UI_Medal_Icon_DoorDash.png");
		StartGameTitle_->OnOffSwitch();
		StartGameTitle_->Reset();
	}

	if (true == GameEngineInput::GetInst()->IsDown("321GO"))
	{
		//현재 프레임 애니메이션 속도가 이상한건지 프레임 나뉜게 이상한건지 암튼 이상함
		CountDown_->Reset();
		CountDown_->On();
	}

	if (true == GameEngineInput::GetInst()->IsDown("Count"))
	{
		SuccessCount_->OnOffSwitch();
	}

	if (true == GameEngineInput::GetInst()->IsDown("Tip"))
	{
		GoalTipActor_->OnOffSwitch();
	}


	if (true == GameEngineInput::GetInst()->IsDown("PlusScore"))
	{
		SuccessCount::Score_ += 100;
	}

	if (true == GameServer::GetInst()->IsServerStart())
	{
		SuccessCount::Score_ = GameServer::GetInst()->PlayerScore_;
	}
}

void InGameSetUI::LevelStartEvent()
{
	CountDownStart_ = true;

	if (false == GameEngineInput::GetInst()->IsKey("Fail"))
	{
		GameEngineInput::GetInst()->CreateKey("Fail", '1');
		GameEngineInput::GetInst()->CreateKey("Success", '2');
		GameEngineInput::GetInst()->CreateKey("End", '3');
		GameEngineInput::GetInst()->CreateKey("SubTitle", '4');
		GameEngineInput::GetInst()->CreateKey("Tip", '5');
		GameEngineInput::GetInst()->CreateKey("Count", '6');
		GameEngineInput::GetInst()->CreateKey("321GO", '0');
		GameEngineInput::GetInst()->CreateKey("PlusScore", '7');
	}

	GameFail_ = GetLevel()->CreateActor<GameFail>();
	GameFail_->GetTransform().SetWorldPosition({ 0.0f,200.0f });
	GameFail_->Off();
	
	GameSuccess_ = GetLevel()->CreateActor<GameSuccess>();
	GameSuccess_->Off();

	RoundEnd_ = GetLevel()->CreateActor<RoundEnd>();
	RoundEnd_->GetTransform().SetWorldPosition({ 0.0f,-200.0f });
	RoundEnd_->Off();

	CountDown_ = GetLevel()->CreateActor<CountDown>();
	CountDown_->Off();

	StartGameTitle_ = GetLevel()->CreateActor<StartGameTitleActor>();
	StartGameTitle_->Off();

	GoalTipActor_ = GetLevel()->CreateActor<GoalTipActor>();
	GoalTipActor_->Off();

	SuccessCount_ = GetLevel()->CreateActor<SuccessCount>();
	//SuccessCount_->Off();
}

void InGameSetUI::LevelEndEvent()
{
	CountDownStart_ = false;
}
