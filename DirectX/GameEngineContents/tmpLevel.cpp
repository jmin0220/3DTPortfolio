#include "PreCompile.h"
#include "tmpLevel.h"
#include "TitleActor.h"
#include "Cursor.h"
#include <GameEngineCore/GameEngineActor.h>
#include "FontActor.h"
#include "NamePlate.h"
#include "NoneButton.h"
#include "NoneMoney.h"
#include "SelectShowButton.h"
#include "PlayButton.h"
#include "TopMenu.h"
#include "CrownCount.h"
#include "StartGameTitleActor.h"
#include "GoalTipActor.h"
#include "CountDown.h"
#include "SuccessCount.h"
#include "GameSuccess.h"
#include "TestActor.h"
#include "RoundEnd.h"

tmpLevel::tmpLevel() 
	:Font(nullptr)
	,Swap(false)
{
}

tmpLevel::~tmpLevel() 
{
}

void tmpLevel::Start()
{

	
}

void tmpLevel::Update(float _DeltaTime)
{
	TitleLogo->FontSizeAnimation();//뒤늦게 들어오기땜에 Update에 있어야함
	CountDownActor_->CountDownStart();
}

void tmpLevel::End()
{
}

void tmpLevel::LevelStartEvent()
{
	// 엑터 생성
	TitleLogo = CreateActor<TitleActor>();

	Name = CreateActor<NamePlate>();

	Button = CreateActor<NoneButton>();

	MoneyUI = CreateActor<NoneMoney>();

	ShowButton = CreateActor<SelectShowButton>();

	StartButton = CreateActor<PlayButton>();

	Top = CreateActor<TopMenu>();

	Crown = CreateActor<CrownCount>();

	Startbar_ = CreateActor<StartGameTitleActor>();

	Tip_ = CreateActor<GoalTipActor>();

	GameSuccess_ = CreateActor<GameSuccess>();

	CountDownActor_ = CreateActor<CountDown>();

	Success_ = CreateActor<SuccessCount>();

	//RoundEnd_ = CreateActor<RoundEnd>();

	Test_ = CreateActor<TestActor>();

	Mouse = CreateActor<Cursor>();


	// 엑터 초기화
	Test_->GetTransform().SetWorldPosition({ 300, 300 });
	TitleLogo->LogoSizeAnimation();
	
}

void tmpLevel::LevelEndEvent()
{
	// 엑터 제거
	TitleLogo->Death();

	Name->Death();

	Button->Death();

	MoneyUI->Death();

	ShowButton->Death();

	StartButton->Death();

	Top->Death();

	Crown->Death();

	Startbar_->Death();

	Tip_->Death();

	GameSuccess_->Death();

	CountDownActor_->Death();

	Success_->Death();

	//RoundEnd_->Death();

	Test_->Death();

	Mouse->Death();
}

