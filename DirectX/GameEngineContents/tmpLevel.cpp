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

tmpLevel::tmpLevel() 
	:Font(nullptr)
{
}

tmpLevel::~tmpLevel() 
{
}

void tmpLevel::Start()
{
	TitleLogo = CreateActor<TitleActor>();
	TitleLogo->GetTransform().SetLocalPosition({ 800,-450 });
	TitleLogo->GetTransform().SetLocalPosition({ -400 + 418, 225 - 143 });

	Name = CreateActor<NamePlate>();

	Button = CreateActor<NoneButton>();

	MoneyUI = CreateActor<NoneMoney>();

	ShowButton = CreateActor<SelectShowButton>();

	StartButton = CreateActor<PlayButton>();

	Top = CreateActor<TopMenu>();

	Crown = CreateActor<CrownCount>();

	Mouse = CreateActor<Cursor>();
}

void tmpLevel::Update(float _DeltaTime)
{
}

void tmpLevel::End()
{
}
