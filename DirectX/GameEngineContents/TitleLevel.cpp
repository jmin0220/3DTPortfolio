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
	//GameEngineInput::GetInst()->CreateKey("Start", VK_RETURN);
}

void TitleLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown(KEY_ENTER))
	{
		ContentsCore::GetInst()->ChangeLevelByThread(LEVEL_NAME_LOBBY);
	}


	if (ContentsCore::GetInst()->GetLoadingProgress() >= 0.999f)
	{
		GEngine::ChangeLevel(LEVEL_NAME_LOBBY);
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
