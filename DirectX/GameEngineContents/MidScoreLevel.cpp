#include "PreCompile.h"
#include "MidScoreLevel.h"

#include "LobbyPlayer.h"
#include "FloorActor.h"
#include "GoalTipActor.h"
#include "MidScoreBGActor.h"
#include "FontActor.h"

#include <GameEngineBase/GameEngineRandom.h>

float4 FirstActorPos = float4(-20, 0, 100); // 다음+ (40, -15, 0) 체어  y+ 15.5f
float4 FirstActorRot = float4(0, 160, 0);


MidScoreLevel::MidScoreLevel()
	: FallingTime_(0.0f)
	, PlayerScores_{}
	, BeforeScoreTime_(0.0f)
	, IsScoreOn_(false)
	, Once_(false)
	, LevelChanged_(false)
	, MidScoreTime_(0.0f)
	, LerpTime_(0.0f)
	, ScoreSetted_(false)
{
}

MidScoreLevel::~MidScoreLevel()
{
}

void MidScoreLevel::Start()
{
}

void MidScoreLevel::Update(float _DeltaTime)
{
	{
		//꼴찌 플레이어 추락 애니메이션

		if (LobbyPlayers_[AllServerPlayersCount_ - 1]->GetTransform().GetWorldPosition().y > -400.0f)
		{
			LobbyPlayers_[AllServerPlayersCount_ - 1]->GetTransform().SetWorldMove(float4::DOWN * _DeltaTime * 100.0f);
		}
		else
		{
			LobbyPlayers_[AllServerPlayersCount_ - 1]->GetTransform().SetWorldPosition(LastActorPos_);
		}
	}

	{
		// 파칭코마냥 돌리다가
		// 시간지나면 점수 세팅
		RandomSocre();

		// 점수가 세팅됬으면(UI도) 자기점수 보여주는 시간 업데이트 시작
		if (IsScoreOn_ == true)
		{
			BeforeScoreTime_ += _DeltaTime;
		}

		// 그 시간이 2초 지나면 정렬 시작
		if (BeforeScoreTime_ > 2.0f && true == IsScoreOn_)
		{
			BubbleSortLerp();
			IsScoreOn_ = false;
			BeforeScoreTime_ = 0.0f;
			Once_ = true;	// 정렬 다했으면 UI러프 시작신호 On
		}

		RenderBubbleSort();

		ChaseNameToScore();
	}


	// 서버
	MidScoreTime_ += _DeltaTime;
	if (true == GameServer::GetInst()->IsServerStart())
	{
		if (MidScoreTime_ < 10.0f)
		{
			return;
		}

		// 3. 유저/호스트 상태변경
		if (false == LevelChanged_
			&& true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageMidScoreChangeReady))
		{
			if (true == GameServer::IsHost_)
			{
				// 호스트는 모든 유저가 넘어가면 넘어간다
				if (true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_StageMidScoreChangeReady)
					&& true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StageMidScoreChangeOver))
				{
					// 다음 스테이지로
					std::string_view NextStage = ContentsCore::GetInst()->GetNextStage();
					ContentsCore::GetInst()->ChangeLevelByLoading(ContentsCore::GetInst()->GetNextStage());
					LevelChanged_ = true;
				}
			}
			else
			{
				// 유저는 서버신호 받으면 바로 넘어감
				if (true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageMidScoreChangeReady))
				{
					// 다음 스테이지로
					std::string_view NextStage = ContentsCore::GetInst()->GetNextStage();
					ContentsCore::GetInst()->ChangeLevelByLoading(ContentsCore::GetInst()->GetNextStage());
					LevelChanged_ = true;
				}
			}
		}


		// 2. 서버가 모든 유저 준비됐는지 확인
		if (true == GameServer::IsHost_
			&& !GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageMidScoreChangeReady))
		{
			// 서버는 자신과 플레이어들 준비 다 됐는지 확인하면
			if (GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_StageMidScoreChangeReady)
				&& GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StageMidScoreChangeReady))
			{
				// 서버신호 '다음으로넘어가라'로
				GameServer::GetInst()->SetServerSignal(ServerFlag::S_StageMidScoreChangeReady);
			}
		}


		// 1. 시간 지나면 유저 준비됨
		if (true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_None))
		{
			GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_StageMidScoreChangeReady);
		}
	}
	// ~~~~~~ 서버

}



void MidScoreLevel::End()
{
}

void MidScoreLevel::LevelStartEvent()
{
	// 1st, 2nd
	Font1st_ = CreateActor<FontActor>();
	Font1st_->SetFont("1st.   ", FONT_TITAN_ONE, 60.0f, { 20,200 }, LeftAndRightSort::LEFT);
	Font2nd_ = CreateActor<FontActor>();
	Font2nd_->SetFont("2nd. ", FONT_TITAN_ONE, 60.0f, { 20,320 }, LeftAndRightSort::LEFT);

	// 서버
	// 모든 플레이어의 점수 정보를 자료구조로 던져줄 예정
	if (true == GameServer::GetInst()->IsServerStart())
	{
		MidScoreTime_ = 0.0f;
		LevelChanged_ = false;

		ServerSetting();
	}
	// 서버 안킴
	else
	{
		NoServerSetting();
	}

	//if (false == GameEngineInput::GetInst()->IsKey("RandomScore"))
	//{
	//	GameEngineInput::GetInst()->CreateKey("RandomScore", VK_RETURN);
	//}

	Once_ = false;
	IsScoreOn_ = false;
	ScoreSetted_ = false;
	BeforeScoreTime_ = 0.0f;
	LerpTime_ = 0.0f;
	FallingTime_ = 0.0f;
	MidScoreTime_ = 0.0f;

	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	BG_ = CreateActor<MidScoreBGActor>();

	Score_ = CreateActor<GoalTipActor>();
	Score_->GetFont().lock()->SetText("현재 점수!", FONT_NOTO_SANS_CJK_SC);

}

void MidScoreLevel::LevelEndEvent()
{
	Score_->Death();

	Font1st_->Death();
	Font2nd_->Death();

	for (std::shared_ptr<FontActor> Font : FontScore_)
	{
		Font->Death();
	}

	for (std::shared_ptr<FontActor> Font : Font_PlayerName)
	{
		Font->Death();
	}

	for (std::shared_ptr<LobbyPlayer> LobbyPlayer : LobbyPlayers_)
	{
		LobbyPlayer->Death();
	}

	for (std::shared_ptr<FloorActor> Chair : Chairs_)
	{
		Chair->Death();
	}

	ContentsCore::GetInst()->ReleaseCurLevelResource();
}

void MidScoreLevel::RandomSocre()
{
	if (false == IsScoreOn_ && false == ScoreSetted_)
	{
		for (int i = 0; i < PlayerScores_.size(); ++i)
		{
			PlayerScores_[i] = GameEngineRandom::MainRandom.RandomInt(0, 999);

			Font_PlayerName[i]->SetFont(PlayerName_[i], FONT_TITAN_ONE);
			FontScore_[i]->SetFont(std::to_string(PlayerScores_[i]), FONT_NOTO_SANS_CJK_SC, 50.0f, LeftAndRightSort::LEFT);
		}
	}

	if (MidScoreTime_ < 3.0f)
	{
		return;
	}
	

	// 점수 세팅하고 러프시작
	if (false == ScoreSetted_ && MidScoreTime_ > 3.0f)
	{
		ScoreSetted_ = true;
		IsScoreOn_ = true;

		for (int i = 0; i < PlayerScores_.size(); ++i)
		{
			PlayerScores_[i] = AllServerPlayers_[i].Score_;
			Font_PlayerName[i]->SetFont(PlayerName_[i], FONT_TITAN_ONE);
			FontScore_[i]->SetFont(std::to_string(PlayerScores_[i]), FONT_NOTO_SANS_CJK_SC, 50.0f, LeftAndRightSort::LEFT);
		}

	}



}

void MidScoreLevel::BubbleSortLerp()
{
	for (int i = static_cast<int>(PlayerScores_.size()-1); i > 0; --i)//5개를 두개씩 비교하면 4번해야함->4부터 시작해야 죽 훑음 0부터해서 ++하니 안됨
	{
		for (int j = 0; j < i; ++j)
		{
			if (PlayerScores_[j] < PlayerScores_[j + 1])//앞에거보다 뒤에게 크면 앞으로(자리바꿈)
			{
				int Temp = PlayerScores_[j];
				PlayerScores_[j] = PlayerScores_[j + 1];
				PlayerScores_[j + 1] = Temp;

				std::shared_ptr<FontActor> FTemp = FontScore_[j];
				FontScore_[j] = FontScore_[j + 1];
				FontScore_[j + 1] = FTemp;

				std::string STemp = PlayerName_[j];
				PlayerName_[j] = PlayerName_[j + 1];
				PlayerName_[j + 1] = STemp;
			}
		}
	}
	
}

void MidScoreLevel::RenderBubbleSort()
{
	if (Once_ == true) //버블소트로 실제 정돈이 끝난후 그걸 토대로 러프 하는 부분(함수로 정돈하자)
	{
		for (int i = 0; i < FontScore_.size(); ++i)
		{
			for (int j = 0; j < FontScore_.size(); ++j)
			{
				if (FontScore_[i]->GetFont()->GetText() == std::to_string(PlayerScores_[j]) && i==j)
				{
					float4 Temp = FontScore_[i]->GetFont()->GetScreenPosition();
					FontScore_[i]->GetFont()->SetScreenPostion(float4::Lerp(Temp, { 170.0f, 250.0f + (120.0f * static_cast<float>(j)) }, GameEngineTime::GetDeltaTime() * 10.0f));
					//문제 하나 있음 같은 점수+둘다 러프해야하면 위치가 겹침
				}
				
				if (FontScore_[FontScore_.size()-1]->GetFont()->GetScreenPosition().y == (250.0f + (120.0f * static_cast<float>(j))))
				{
					LerpTime_ += GameEngineTime::GetDeltaTime();
				}
			}
		}
	}

	
}

void MidScoreLevel::ChaseNameToScore()
{
	for (int i = 0; i < Font_PlayerName.size(); ++i)
	{
		Font_PlayerName[i]->SetFont(PlayerName_[i], FONT_TITAN_ONE, 60.0f, {FontScore_[i]->GetFont()->GetScreenPosition().x,FontScore_[i]->GetFont()->GetScreenPosition().y - 50.0f}, LeftAndRightSort::LEFT);
	}
}

void MidScoreLevel::ServerSetting()
{
	// 자기제외 모든 플레이어 + 자신
	AllServerPlayersCount_ = static_cast<int>(GameServer::GetInst()->OtherPlayersInfo_.size() + 1);
	AllServerPlayers_.clear();

	std::map<int, std::shared_ptr<class PlayerStatePacket>>::iterator StartIt = GameServer::GetInst()->OtherPlayersInfo_.begin();
	std::map<int, std::shared_ptr<class PlayerStatePacket>>::iterator EndIt = GameServer::GetInst()->OtherPlayersInfo_.end();

	int ListIdx = 0;
	for (; StartIt != EndIt; ++StartIt)
	{
		std::shared_ptr<PlayerStatePacket> Packet = (*StartIt).second;
		AllServerPlayers_.emplace_back(Packet->PlayerID, Packet->PlayerColor, Packet->PlayerScore, Packet->PlayerName);
	}
	// 자기정보도 넣는다
	std::shared_ptr<GameServer>& Server = GameServer::GetInst();
	ServerPlayerInfo MyInfo;
	MyInfo.ID_ = Server->PlayerID_;
	MyInfo.Color_ = Server->PlayerColorID_;
	MyInfo.Score_ = Server->PlayerScore_;
	MyInfo.Name_ = Server->UserName_;
	AllServerPlayers_.push_back(MyInfo);

	// ID순으로 정렬
	std::sort(AllServerPlayers_.begin(), AllServerPlayers_.end(), IDSmaller);

	// 점수 설정
	PlayerScores_.clear();
	PlayerScores_.resize(AllServerPlayersCount_);
	PlayerName_.clear();
	FontScore_.clear();
	Font_PlayerName.clear();
	LastActorPos_ = float4::ZERO;

	// 폰트 정보 설정
	for (int i = 0; i < AllServerPlayers_.size(); i++)
	{
		// UI
		// 플레이어 이름
		PlayerName_.push_back(AllServerPlayers_[i].Name_);

		// 플레이어 점수 '폰트엑터'
		std::shared_ptr<FontActor> FontScore = CreateActor<FontActor>();
		FontScore->SetFont(std::to_string(AllServerPlayers_[i].Score_), FONT_NOTO_SANS_CJK_SC, 50.0f, { 170,250 + i * 120.0f }, LeftAndRightSort::LEFT);
		FontScore_.push_back(FontScore);

		// 플레이어 이름 '폰트엑터'
		std::shared_ptr<FontActor> FontPlayerName = CreateActor<FontActor>();
		FontPlayerName->SetFont(PlayerName_[i], FONT_TITAN_ONE, 60.0f, { 170, 200 + i * 120.0f }, LeftAndRightSort::LEFT);
		Font_PlayerName.push_back(FontPlayerName);
	}

	
	// *최상위 4명의 색정보 필요
	std::sort(AllServerPlayers_.begin(), AllServerPlayers_.end(), ScoreBigger);

	int LobbyPlayersCount = AllServerPlayersCount_ > 4 ? 4 : AllServerPlayersCount_;

	// 로비 플레이어, 발판 생성
	for (int i = 0; i < LobbyPlayersCount; i++)
	{
		// 로비플레이어 엑터 2명 생성
		std::shared_ptr<LobbyPlayer> Player = CreateActor<LobbyPlayer>();
		float4 PlayerColor = GameServer::GetInst()->GetPlayerColorReturn(AllServerPlayers_[i].Color_);
		Player->SetPlayerColor(PlayerColor);

		float4 PlayerPos = FirstActorPos + float4(i * 40.0f, i * -15.0f, 0);
		Player->GetTransform().SetWorldPosition(PlayerPos);
		Player->GetTransform().SetWorldRotation(FirstActorRot + float4(0, i * 10.0f, 0));

		LobbyPlayers_.push_back(Player);

		// 의자는 로비플레이어 -1 개 생성
		// 마지막 로비플레이어
		if (i == LobbyPlayersCount - 1)
		{
			Player->GetTransform().SetWorldMove({ 0, 300, 140 });
			LastActorPos_ = Player->GetTransform().GetWorldPosition();

			break;
		}

		std::shared_ptr<FloorActor> Chair = CreateActor<FloorActor>();

		Chair->GetTransform().SetWorldPosition(PlayerPos + float4(0, 15.5f, 0));

		Chairs_.push_back(Chair);

	}

	// 애니메이션 설정
	if (AllServerPlayersCount_ == 2)
	{
		LobbyPlayers_[0]->ChangeAnimationGasp();
		LobbyPlayers_[1]->ChangeAnimationTumbel();
	}
	else if (AllServerPlayersCount_ == 3)
	{
		LobbyPlayers_[0]->ChangeAnimationGasp();
		LobbyPlayers_[1]->ChangeAnimationJogging();
		LobbyPlayers_[2]->ChangeAnimationFall();
	}
	else if (AllServerPlayersCount_ >= 4)
	{
		LobbyPlayers_[0]->ChangeAnimationGasp();
		LobbyPlayers_[1]->ChangeAnimationJogging();
		LobbyPlayers_[2]->ChangeAnimationIdle();
		LobbyPlayers_[3]->ChangeAnimationTumbel();
	}

	// 처음에 보여줄때는 ID순서대로
	std::sort(AllServerPlayers_.begin(), AllServerPlayers_.end(), IDSmaller);

}

void MidScoreLevel::NoServerSetting()
{
	// 2명만 생성해라
	AllServerPlayersCount_ = 4;

	AllServerPlayers_.emplace_back(0, 0, 200);
	AllServerPlayers_.emplace_back(1, 3, 500);
	AllServerPlayers_.emplace_back(2, 2, 100);
	AllServerPlayers_.emplace_back(3, 4, 400);

	// 점수 설정
	PlayerScores_.resize(AllServerPlayersCount_);

	for (int i = 0; i < AllServerPlayersCount_; i++)
	{
		// 로비플레이어 엑터 2명 생성
		std::shared_ptr<LobbyPlayer> Player = CreateActor<LobbyPlayer>();
		float4 PlayerPos = FirstActorPos + float4(i * 40.0f, i * -15.0f, 0);
		Player->GetTransform().SetWorldPosition(PlayerPos);
		Player->GetTransform().SetWorldRotation(FirstActorRot + float4(0, i * 10.0f, 0));

		LobbyPlayers_.push_back(Player);
		
		// UI
		// 플레이어 이름
		PlayerName_.push_back("Player" + std::to_string(i));

		// 플레이어 점수 '폰트엑터'
		std::shared_ptr<FontActor> FontScore = CreateActor<FontActor>();
		FontScore->SetFont("Score" + std::to_string(PlayerScores_[i]), FONT_NOTO_SANS_CJK_SC, 50.0f, {170,250 + i * 120.0f}, LeftAndRightSort::LEFT);
		FontScore_.push_back(FontScore);

		// 플레이어 이름 '폰트엑터'
		std::shared_ptr<FontActor> FontPlayerName = CreateActor<FontActor>();
		FontPlayerName->SetFont(PlayerName_[i] + "번 플레이어", FONT_TITAN_ONE, 60.0f, {170, 200 + i * 120.0f}, LeftAndRightSort::LEFT);
		Font_PlayerName.push_back(FontPlayerName);

		// 의자는 로비플레이어 -1 개 생성
		// 마지막 로비플레이어
		if (i == AllServerPlayersCount_ - 1)
		{
			Player->GetTransform().SetWorldMove({ 0, 300, 140 });
			LastActorPos_ = Player->GetTransform().GetWorldPosition();

			break;
		}

		std::shared_ptr<FloorActor> Chair = CreateActor<FloorActor>();

		Chair->GetTransform().SetWorldPosition(PlayerPos + float4(0, 15.5f, 0));

		Chairs_.push_back(Chair);
	}

	// 애니메이션 설정
	if (AllServerPlayersCount_ == 2)
	{
		LobbyPlayers_[0]->ChangeAnimationGasp();
		LobbyPlayers_[1]->ChangeAnimationTumbel();
	}
	else if (AllServerPlayersCount_ == 3)
	{
		LobbyPlayers_[0]->ChangeAnimationGasp();
		LobbyPlayers_[1]->ChangeAnimationJogging();
		LobbyPlayers_[2]->ChangeAnimationFall();
	}
	else if (AllServerPlayersCount_ >= 4)
	{
		LobbyPlayers_[0]->ChangeAnimationGasp();
		LobbyPlayers_[1]->ChangeAnimationJogging();
		LobbyPlayers_[2]->ChangeAnimationIdle();
		LobbyPlayers_[3]->ChangeAnimationTumbel();
	}


	LobbyPlayers_[0]->SetPlayerColor(GameServer::GetInst()->GetPlayerColorReturn(AllServerPlayers_[0].Color_));
	LobbyPlayers_[1]->SetPlayerColor(GameServer::GetInst()->GetPlayerColorReturn(AllServerPlayers_[1].Color_));
	LobbyPlayers_[2]->SetPlayerColor(GameServer::GetInst()->GetPlayerColorReturn(AllServerPlayers_[2].Color_));
	LobbyPlayers_[3]->SetPlayerColor(GameServer::GetInst()->GetPlayerColorReturn(AllServerPlayers_[3].Color_));

}


void MidScoreLevel::QuickSort(int arr[], int _First, int _Last)
{
	if (_First >= _Last)
	{
		//비교할 인덱스가 겹치거나 넘어간다면
		return;
	}

	int Pivot = _First;
	int i = _First + 1;//맨 처음걸 피봇(기준)잡기에 그 다음걸 First로 두기위해 + 1
	int j = _Last;
	int Temp;

	while (i <= j)
	{
		while ((arr[i] > arr[Pivot]) && (i <= _Last))
		{
			//arr[i]값이 arr[Pivot]의 값보다 작고 인덱스i가 _Last인덱스보다 작거나 같다면(작은게 앞으로 오는 기준)
			i++;
		}
		while ((arr[j] <= arr[Pivot]) && (j > _First))
		{
			//끝에서부터 한칸한칸 왼쪽으로 이동하니 --
			j--;
		}

		if (i >= j)//i가 j와 겹쳐지거나 넘어간다면 while문을 멈춘다
		{
			break;
		}

		//서로 자리를 바꾼다
		Temp = arr[i];
		arr[i] = arr[j];
		arr[j] = Temp;

		std::shared_ptr<FontActor> FTemp = FontScore_[i];
		FontScore_[i] = FontScore_[j];
		FontScore_[j] = FTemp;
	}

	Temp = arr[j];
	arr[j] = arr[Pivot];
	arr[Pivot] = Temp;

	std::shared_ptr<FontActor> FTemp = FontScore_[j];
	FontScore_[j] = FontScore_[Pivot];
	FontScore_[Pivot] = FTemp;

	QuickSort(arr, _First, j - 1);
	QuickSort(arr, j + 1, _Last);
}
