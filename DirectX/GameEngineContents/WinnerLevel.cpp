#include "PreCompile.h"
#include "WinnerLevel.h"

#include "Winner.h"
#include "LobbyPlayer.h"
#include "WinnerBG.h"
#include "FloorActor.h"
#include "UISkyBoxActor.h"

#include "OptionActor.h"

WinnerLevel::WinnerLevel() 
	:ChairTime_(0.0f)
{
}

WinnerLevel::~WinnerLevel() 
{
}

void WinnerLevel::Start()
{
}

void WinnerLevel::Update(float _DeltaTime)
{
	ChairTime_ += _DeltaTime;
	if (ChairTime_ > 9.0f)
	{
		Chair_->Off();
	}
}

void WinnerLevel::End()
{
}

void WinnerLevel::LevelStartEvent()
{
	GlobalBGM::GetInst()->GetBGM().Stop();
	GlobalBGM::GetInst()->SetBGM(GameEngineSound::SoundPlayControl("6 - Didn't Fall! (You Win).mp3"));
	GlobalBGM::GetInst()->GetBGM().Volume(OptionActor::VolumeRatio_);

	ChairTime_ = 0.0f;

	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
	
	//ContentsCore::GetInst()->LoadLevelResource(LEVELS::WINNNER);//경로설정
	BG_ = CreateActor<WinnerBG>();
	Sky_ = CreateActor<UISkyBoxActor>();

	Winner_ = CreateActor<Winner>();

	Player_ = CreateActor<LobbyPlayer>();
	Player_->GetTransform().SetWorldRotation({ 0,180,0 });
	Player_->GetTransform().SetWorldPosition({ 0,-15,0 });

	Player_->ChangeAnimationWin();

	Chair_ = CreateActor<FloorActor>();
	Chair_->On();

	// 서버
	std::shared_ptr<GameServer>& Server = GameServer::GetInst();
	if (true == Server->IsServerStart())
	{
		std::map<int, std::shared_ptr<class PlayerStatePacket>>::iterator StartIt = Server->OtherPlayersInfo_.begin();
		std::map<int, std::shared_ptr<class PlayerStatePacket>>::iterator EndIt = Server->OtherPlayersInfo_.end();

		int ListIdx = 0;
		for (; StartIt != EndIt; ++StartIt)
		{
			std::shared_ptr<PlayerStatePacket> Packet = (*StartIt).second;
			AllServerPlayers_.emplace_back(Packet->PlayerColor, Packet->PlayerScore, Packet->PlayerName);
		}
		// 자기정보도 넣는다
		
		ServerPlayerInfo MyInfo;
		MyInfo.Color_ = Server->PlayerColorID_;
		MyInfo.Score_ = Server->PlayerScore_;
		MyInfo.Name_ = Server->UserName_;
		AllServerPlayers_.push_back(MyInfo);

		std::sort(AllServerPlayers_.begin(), AllServerPlayers_.end(), ScoreBigger);

		// 1위
		Player_->SetPlayerColor(GameServer::GetInst()->GetPlayerColorReturn(AllServerPlayers_[0].Color_));
		Winner_->SetWinnerFont(AllServerPlayers_[0].Name_);
	}
}

void WinnerLevel::LevelEndEvent()
{
	Sky_->Death();
	BG_->Death();
	Winner_->Death();
	Player_->Death();
	Chair_->Death();

	ContentsCore::GetInst()->ReleaseCurLevelResource();
}
