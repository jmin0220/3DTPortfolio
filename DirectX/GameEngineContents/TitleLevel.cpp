#include "PreCompile.h"
#include "TitleLevel.h"
#include "TitleActor.h"
#include "Cursor.h"

TitleLevel::TitleLevel() 
	: EnterDown_(false)
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{

}

void TitleLevel::Update(float _DeltaTime)
{
	/// *** ������ �̿� ���� ����� ȣ�� *** ///
	if (ContentsCore::GetInst()->GetLoadingProgress() >= 0.999f)
	{
		GEngine::ChangeLevel(LEVEL_NAME_LOBBY);
	}

	if (false == EnterDown_ && true == GameEngineInput::GetInst()->IsDown(KEY_ENTER))
	{
		EnterDown_ = true;
		ContentsCore::GetInst()->ChangeLevelByThread(LEVEL_NAME_LOBBY);
	}
	/// ~~~ ������ �̿� ���� ����� ȣ�� ~~~ ///
}

void TitleLevel::End()
{
}

void TitleLevel::LevelStartEvent()
{
	/// *** ������ �̿� ���� ����� ȣ�� *** ///
	ContentsCore::GetInst()->InitLoadingProgress();

	EnterDown_ = false;

	TitleLogo = CreateActor<TitleActor>();

	Mouse = CreateActor<Cursor>();

	GameEngineSound::SoundPlayControl("Title.mp3");
}

void TitleLevel::LevelEndEvent()
{
	TitleLogo->Death();
	Mouse->Death();
}
