#include "PreCompile.h"
#include "LobbyLevel.h"
#include "Cursor.h"
#include <GameEngineCore/GameEngineActor.h>
#include "FontActor.h"

#include "LobbyPlayer.h"

#include "LobbySetUI.h"
#include "InGameSetUI.h"

#include "Winner.h"

LobbyLevel::LobbyLevel() 
	:Font(nullptr)
	,Swap(false)
{
}

LobbyLevel::~LobbyLevel() 
{
}

void LobbyLevel::Start()
{

	
}

void LobbyLevel::Update(float _DeltaTime)
{
	std::weak_ptr<PlayButton> tmpPlayButton = LobbySet_->GetPlayButton();
	if (ContentsCore::GetInst()->GetLoadingProgress() >= 0.999f)
	{
		GEngine::ChangeLevel(LEVEL_NAME_FALLING);
	}

	if (true == tmpPlayButton.lock()->GetIsLevelChange())
	{
		ContentsCore::GetInst()->ChangeLevelByThread(LEVEL_NAME_FALLING);
	}
}

void LobbyLevel::End()
{
}

void LobbyLevel::LevelStartEvent()
{
	ContentsCore::GetInst()->InitLoadingProgress();

	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	//ContentsCore::GetInst()->LoadLevelResource(LEVELS::LOBBY);//��μ���
	//�̰� �ϸ� �ؿ� EndEvent���� ���ҽ� ���� ������Ѵ�

	LobbySet_ = CreateActor<LobbySetUI>();

	InGameSetUI_ = CreateActor<InGameSetUI>();

	Player_ = CreateActor<LobbyPlayer>();
	Player_->GetTransform().SetWorldPosition({ 0, -15, 0});//���� z�� ������ �ȹ���
	Player_->GetTransform().SetWorldRotation({ 0,160,0 });//���������� ����

	Mouse = CreateActor<Cursor>();
}

void LobbyLevel::LevelEndEvent()
{
	// ���� ����

	LobbySet_->Death();

	InGameSetUI_->Death();

	Player_->Death();

	Mouse->Death();

	ContentsCore::GetInst()->ReleaseCurLevelResource();
}

