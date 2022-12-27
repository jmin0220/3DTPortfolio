#include "PreCompile.h"
#include "LobbyLevel.h"
#include "Cursor.h"
#include <GameEngineCore/GameEngineActor.h>
#include "FontActor.h"

#include "LobbyPlayer.h"
#include "LobbySetUI.h"
#include "Winner.h"
#include "FloorActor.h"
#include "Bingle.h"
#include "TopMenu.h"
#include "GameServer.h"

// �����׽�Ʈ�� ù �������� ����
const std::string FirstStage = LEVEL_NAME_JUMPCLUB;

LobbyLevel::LobbyLevel() 
	:Swap(false)
	,FallTime_(0.0f)
	,NumberFont_(nullptr)
	,UserFont_(nullptr)
	,WaitingFont_(nullptr)
	,PrevUserCount_(0)
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

	if (false == GameEngineInput::GetInst()->IsKey("LEFT_Q"))
	{
		GameEngineInput::GetInst()->CreateKey("LEFT_Q", 'Q');
		GameEngineInput::GetInst()->CreateKey("RIGHT_E", 'E');
	}

	// �÷��̾� �⺻ ����
	GameServer::GetInst()->SetPlayerColorID(0);
}

void LobbyLevel::Update(float _DeltaTime)
{
	Player_->SetPlayerColor(GameServer::GetInst()->PlayerColor_);

	StateManager_.Update(_DeltaTime);

	//GlobalBGM::GetInst()->GetBGM().Volume(Volume_);

	if (LobbySet_->GetTopMenu().lock()->MyState_==MenuState::Home)
	{
		Player_->GetTransform().SetWorldRotation({ 0,160,0 });
		{
			float4 CurrentPos = Player_->GetTransform().GetWorldPosition();
			float4 DestinationPos = (float4{ 0, -15, 0});
			Player_->GetTransform().SetWorldPosition({ float4::Lerp(CurrentPos, DestinationPos, GameEngineTime::GetDeltaTime() * 5.f) });
		}

		{
			float4 CurrentPos = Chair_->GetTransform().GetWorldPosition();
			float4 DestinationPos = (float4{ 0, 0, 0 });
			Chair_->GetTransform().SetWorldPosition({ float4::Lerp(CurrentPos, DestinationPos, GameEngineTime::GetDeltaTime() * 5.f) });
		}
	}

	if (LobbySet_->GetTopMenu().lock()->MyState_ == MenuState::Option)
	{
		Player_->GetTransform().SetWorldRotation({ 0,160,0 });
		{
			float4 CurrentPos = Player_->GetTransform().GetWorldPosition();
			float4 DestinationPos = (float4{ -20, -15, 0 });
			Player_->GetTransform().SetWorldPosition({ float4::Lerp(CurrentPos, DestinationPos, GameEngineTime::GetDeltaTime() * 5.f) });
		}

		{
			float4 CurrentPos = Chair_->GetTransform().GetWorldPosition();
			float4 DestinationPos = (float4{ -20, 0, 0 });
			Chair_->GetTransform().SetWorldPosition({ float4::Lerp(CurrentPos, DestinationPos, GameEngineTime::GetDeltaTime() * 5.f) });
		}
	}
}

void LobbyLevel::End()
{
}

void LobbyLevel::LevelStartEvent()
{
	// ���� GUIŴ
	ContentsCore::GetInst()->ServerGUIOn();

	FallTime_ = 0.0f;

	Player_ = CreateActor<LobbyPlayer>();
	Player_->GetTransform().SetWorldPosition({ 0, -15, 0});//���� z�� ������ �ȹ���
	Player_->GetTransform().SetWorldRotation({ 0,160,0 });//���������� ����

	Chair_ = CreateActor<FloorActor>();
	Chair_->On();

	StateManager_.ChangeState("Lobby");
	
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	LobbySet_ = CreateActor<LobbySetUI>();
	LobbySet_->GetTopMenu().lock()->MyState_ = MenuState::Home;

	UserFont_ = CreateActor<FontActor>();
	UserFont_->SetFont("������ ��", "Noto Sans CJK SC", 25.f,{800,750},LeftAndRightSort::CENTER);
	UserFont_->Off();

	NumberFont_ = CreateActor<FontActor>();
	NumberFont_->SetFont("0", "Titan One", 70.f, { 800,680 }, LeftAndRightSort::CENTER);
	NumberFont_->Off();

	WaitingFont_ = CreateActor<FontActor>();
	WaitingFont_->SetFont("�÷��̾ ��ٸ��� ��", "Noto Sans CJK SC", 25.f, { 200,850 }, LeftAndRightSort::CENTER);
	WaitingFont_->Off();

	Bingle_ = CreateActor<Bingle>();
	Bingle_->Off();

	Mouse = CreateActor<Cursor>();
}

void LobbyLevel::LevelEndEvent()
{
	// ���� ����

	LobbySet_->Death();

	Player_->Death();

	Mouse->Death();

	Chair_->Death();

	NumberFont_->Death();
	UserFont_->Death();
	WaitingFont_->Death();

	Bingle_->Death();
	
	ContentsCore::GetInst()->ReleaseCurLevelResource();
	GameServerGUI::GameStart_ = false;
}

void LobbyLevel::LobbyStart(const StateInfo& _Info)
{
	//������ ���͸������������ ���� ����
	Player_->ChangeAnimationIdle();
	Player_->GetTransform().SetWorldPosition({ 0, -15, 0 });
	Player_->GetTransform().SetWorldRotation({ 0,160,0 });
}

void LobbyLevel::LobbyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// �÷��� ��ư ����
	if (true == LobbySet_->GetPlayButton().lock()->GetIsLevelChange())
	{
		StateManager_.ChangeState("Falling");
		return;
	}
}

void LobbyLevel::FallingStart(const StateInfo& _Info)
{
	LobbySet_->GetTopMenu().lock()->MyState_ = MenuState::Fall;

	Player_->ChangeAnimationFall();
	Player_->GetTransform().SetWorldPosition({ 0, 40, 50 });
	Player_->GetTransform().SetWorldRotation({ 0,180,0 });

	Chair_->Off();

	LobbySet_->AllOff();

	UserFont_->On();
	NumberFont_->On();
	WaitingFont_->On();
	Bingle_->On();

	//����
	GameServer::GetInst()->ServerStart();
	
}

void LobbyLevel::FallingUpdate(float _DeltaTime, const StateInfo& _Info)
{


	// ȣ��Ʈ�� ��� ���� �� �Ѿ�� ���º���
	if (true == GameServer::IsHost_)
	{
		if (true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_GameStartChangeOver))
		{
			ContentsCore::GetInst()->ChangeLevelByLoading(FirstStage);
			return;
		}
	}
	// ���� �����ñ׳� Ȯ�εǸ� ����
	else
	{
		if (true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_GameStartChangeReady))
		{
			GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_GameStartChangeReady);
			ContentsCore::GetInst()->ChangeLevelByLoading(FirstStage);
			return;
		}
	}


	FallTime_ -= GameEngineTime::GetDeltaTime()*20.0f;

	if (Player_->GetTransform().GetWorldPosition().y > -10.0f)
	{
		Player_->GetTransform().SetWorldPosition({ 0.0f, 40.0f + FallTime_, 50.0f});
	}

	{
		//������ �ϴ� z���� �ȸԴ°� ����..?
		/*float4 CurrentPos = Player_->GetTransform().GetWorldPosition();
		float4 DestinationPos = (float4{ 0, 0, 50 ,1 });
		Player_->GetTransform().SetWorldScale({ float4::Lerp(CurrentPos, DestinationPos, GameEngineTime::GetDeltaTime() * 15.f) });*/
	}

	// �ڡڡ� ���� �ڡڡ�
	if (PrevUserCount_ != GameServer::GetInst()->GetAllPlayersCount())
	{
		PrevUserCount_ = GameServer::GetInst()->GetAllPlayersCount();
		NumberFont_->SetFont(std::to_string(PrevUserCount_), "Titan One", 70.f, {800,680}, LeftAndRightSort::CENTER);

	}

	// ~~~ ���� ~~~
}

