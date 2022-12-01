#include "PreCompile.h"
#include "LobbyLevel.h"
#include "Cursor.h"
#include <GameEngineCore/GameEngineActor.h>
#include "FontActor.h"

#include "LobbyPlayer.h"

#include "LobbySetUI.h"

#include "Winner.h"

LobbyLevel::LobbyLevel() 
	:Font(nullptr)
	,Swap(false)
	,FallTime_(0.0f)
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

	FallTime_ = 0.0f;

	Player_ = CreateActor<LobbyPlayer>();
	Player_->GetTransform().SetWorldPosition({ 0, -15, 0});//현재 z값 영향을 안받음
	Player_->GetTransform().SetWorldRotation({ 0,160,0 });//반측면으로 돌림

	StateManager_.ChangeState("Lobby");
	
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	LobbySet_ = CreateActor<LobbySetUI>();

	Mouse = CreateActor<Cursor>();
}

void LobbyLevel::LevelEndEvent()
{
	// 엑터 제거

	LobbySet_->Death();

	Player_->Death();

	Mouse->Death();

	//ContentsCore::GetInst()->ReleaseCurLevelResource();
}

void LobbyLevel::LobbyStart(const StateInfo& _Info)
{
	//레벨에 액터만들어지기전에 들어가서 터짐
	Player_->ChangeAnimationIdle();
	Player_->GetTransform().SetWorldPosition({ 0, -15, 0 });
	Player_->GetTransform().SetWorldRotation({ 0,160,0 });
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
	Player_->ChangeAnimationFall();
	Player_->GetTransform().SetWorldPosition({ 0, 40, 50 });
	Player_->GetTransform().SetWorldRotation({ 0,180,0 });

	LobbySet_->AllOff();
}

void LobbyLevel::FallingUpdate(float _DeltaTime, const StateInfo& _Info)
{
	FallTime_ -= GameEngineTime::GetDeltaTime()*20.0f;

	if (Player_->GetTransform().GetWorldPosition().y > -10.0f)
	{
		Player_->GetTransform().SetWorldPosition({ 0.0f, 40.0f + FallTime_, 50.0f});
	}

	{
		//러프를 하니 z값이 안먹는거 같다..?
		/*float4 CurrentPos = Player_->GetTransform().GetWorldPosition();
		float4 DestinationPos = (float4{ 0, 0, 50 ,1 });
		Player_->GetTransform().SetWorldScale({ float4::Lerp(CurrentPos, DestinationPos, GameEngineTime::GetDeltaTime() * 15.f) });*/
	}
}

