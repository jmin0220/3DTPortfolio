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

	Mouse = CreateActor<Cursor>();
	
}

void tmpLevel::Update(float _DeltaTime)
{
	TitleLogo->FontSizeAnimation();//�ڴʰ� �����ⶫ�� Update�� �־����
}

void tmpLevel::End()
{
}

void tmpLevel::LevelStartEvent()
{
	TitleLogo->LogoSizeAnimation();
}

void tmpLevel::LevelEndEvent()
{
}

