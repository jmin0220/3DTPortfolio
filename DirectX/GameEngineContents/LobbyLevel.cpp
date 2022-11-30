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
	StateManager_.CreateStateMember("Lobby"
		, std::bind(&LobbyLevel::LobbyUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&LobbyLevel::LobbyStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("Falling"
		, std::bind(&LobbyLevel::FallingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&LobbyLevel::FallingStart, this, std::placeholders::_1));

	StateManager_.ChangeState("Lobby");
	
}

void LobbyLevel::Update(float _DeltaTime)
{
	StateManager_.Update(_DeltaTime);
}

void LobbyLevel::End()
{
}

void LobbyLevel::LevelStartEvent()
{
	// 서버 GUI킴
	ContentsCore::GetInst()->ServerGUIOn();

	StateManager_.ChangeState("Lobby");
	
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

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

	Mouse->Death();

	//ContentsCore::GetInst()->ReleaseCurLevelResource();
}

void LobbyLevel::LobbyStart(const StateInfo& _Info)
{
}

void LobbyLevel::LobbyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == LobbySet_->GetPlayButton().lock()->GetIsLevelChange())
	{
		StateManager_.ChangeState("Falling");
		return;
	}
}

void LobbyLevel::FallingStart(const StateInfo& _Info)
{
	Player_->GetTransform().SetWorldPosition({ 0, 30, 100 });
}

void LobbyLevel::FallingUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

