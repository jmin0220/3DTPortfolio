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
	LobbySet_ = CreateActor<LobbySetUI>();

	InGameSetUI_ = CreateActor<InGameSetUI>();

	//Player_ = CreateActor<LobbyPlayer>();

	//Test_ = CreateActor<TestActor>();

	Mouse = CreateActor<Cursor>();

}

void LobbyLevel::LevelEndEvent()
{
	// ¿¢ÅÍ Á¦°Å

	LobbySet_->Death();

	InGameSetUI_->Death();

	//Player_->Death();

	//Test_->Death();

	Mouse->Death();
}

