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
	/// *** 쓰레드 이용 레벨 변경시 호출 *** ///
	if (ContentsCore::GetInst()->GetLoadingProgress() >= 0.999f)
	{
		GEngine::ChangeLevel(LEVEL_NAME_LOBBY);
	}

	if (false == EnterDown_ && true == GameEngineInput::GetInst()->IsDown(KEY_ENTER))
	{
		EnterDown_ = true;
		GameEngineSound::SoundPlayOneShot("Woohoo.mp3");
		ContentsCore::GetInst()->ChangeLevelByThread(LEVEL_NAME_LOBBY);
	}

	/// ~~~ 쓰레드 이용 레벨 변경시 호출 ~~~ ///
}

void TitleLevel::End()
{
}

void TitleLevel::LevelStartEvent()
{
	/// *** 쓰레드 이용 레벨 변경시 호출 *** ///
	ContentsCore::GetInst()->InitLoadingProgress();

	EnterDown_ = false;

	TitleLogo = CreateActor<TitleActor>();

	Mouse = CreateActor<Cursor>();

	GlobalBGM::GetInst()->SetBGM(GameEngineSound::SoundPlayControl("Title.mp3"));

	GlobalBGM::GetInst()->GetBGM().Volume(Volume_);
}

void TitleLevel::LevelEndEvent()
{
	TitleLogo->Death();
	Mouse->Death();
}
