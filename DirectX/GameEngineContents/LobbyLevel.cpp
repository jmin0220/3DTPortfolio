#include "PreCompile.h"
#include "LobbyLevel.h"
#include "Cursor.h"
#include <GameEngineCore/GameEngineActor.h>
#include "FontActor.h"

#include "LobbyPlayer.h"

#include "LobbySetUI.h"
#include "InGameSetUI.h"

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
}

void LobbyLevel::End()
{
}

void LobbyLevel::LevelStartEvent()
{
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	ContentsCore::GetInst()->LoadLevelResource(LEVELS::LOBBY_TEST);//경로설정

	LobbySet_ = CreateActor<LobbySetUI>();

	//InGameSetUI_ = CreateActor<InGameSetUI>();

	Player_ = CreateActor<LobbyPlayer>();
	Player_->GetTransform().SetWorldPosition({ 0,-100,600});//현재 z값 영향을 안받음
	Player_->GetTransform().SetWorldRotation({ 0,160,0 });//반측면으로 돌림

	//Test_ = CreateActor<TestActor>();

	Mouse = CreateActor<Cursor>();

}

void LobbyLevel::LevelEndEvent()
{
	// 엑터 제거

	LobbySet_->Death();

	//InGameSetUI_->Death();

	Player_->Death();

	//Test_->Death();

	Mouse->Death();
}

