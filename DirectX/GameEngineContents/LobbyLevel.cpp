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
	if (tmpPlayButton.lock()->GetIsLevelChange() == true)
	{
		GEngine::ChangeLevel(LEVEL_NAME_HEXAGONE);
	}
}

void LobbyLevel::End()
{
}

void LobbyLevel::LevelStartEvent()
{
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	//ContentsCore::GetInst()->LoadLevelResource(LEVELS::LOBBY);//경로설정
	//이걸 하면 밑에 EndEvent에서 리소스 제거 해줘야한다

	LobbySet_ = CreateActor<LobbySetUI>();

	InGameSetUI_ = CreateActor<InGameSetUI>();

	Player_ = CreateActor<LobbyPlayer>();
	Player_->GetTransform().SetWorldPosition({ 0, -15, 0});//현재 z값 영향을 안받음
	Player_->GetTransform().SetWorldRotation({ 0,160,0 });//반측면으로 돌림

	Mouse = CreateActor<Cursor>();
}

void LobbyLevel::LevelEndEvent()
{
	// 엑터 제거

	LobbySet_->Death();

	InGameSetUI_->Death();

	Player_->Death();

	//Test_->Death();

	Mouse->Death();

	ContentsCore::GetInst()->ReleaseCurLevelResource();
}

