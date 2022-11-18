#include "PreCompile.h"
#include "TitleLevel.h"
#include "TitleActor.h"
#include "Cursor.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{
	GameEngineInput::GetInst()->CreateKey("Start", VK_RETURN);
}

void TitleLevel::Update(float _DeltaTime)
{
	if (TitleLogo->IsLevelChange_ == true)
	{
		GEngine::ChangeLevel("LobbyLevel");
	}
}

void TitleLevel::End()
{
}

void TitleLevel::LevelStartEvent()
{
	TitleLogo = CreateActor<TitleActor>();

	Mouse = CreateActor<Cursor>();
}

void TitleLevel::LevelEndEvent()
{
	TitleLogo->Death();
	Mouse->Death();
}
