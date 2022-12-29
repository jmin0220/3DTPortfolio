#include "PreCompile.h"
#include "MidScoreLevel.h"

#include "LobbyPlayer.h"
#include "FloorActor.h"
#include "GoalTipActor.h"
#include "MidScoreBGActor.h"
#include "FontActor.h"

#include <GameEngineBase/GameEngineRandom.h>

float4 FirstActorPos = float4(-20, 0, 100); // ����+ (40, -15, 0) ü��  y+ 15.5f
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
		//���� �÷��̾� �߶� �ִϸ��̼�

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
		// ��Ī�ڸ��� �����ٰ�
		// �ð������� ���� ����
		RandomSocre();

		// ������ ���É�����(UI��) �ڱ����� �����ִ� �ð� ������Ʈ ����
		if (IsScoreOn_ == true)
		{
			BeforeScoreTime_ += _DeltaTime;
		}

		// �� �ð��� 2�� ������ ���� ����
		if (BeforeScoreTime_ > 2.0f && true == IsScoreOn_)
		{
			BubbleSortLerp();
			IsScoreOn_ = false;
			BeforeScoreTime_ = 0.0f;
			Once_ = true;	// ���� �������� UI���� ���۽�ȣ On
		}

		RenderBubbleSort();

		ChaseNameToScore();
	}


	// ����
	MidScoreTime_ += _DeltaTime;
	if (true == GameServer::GetInst()->IsServerStart())
	{
		if (MidScoreTime_ < 10.0f)
		{
			return;
		}

		// 3. ����/ȣ��Ʈ ���º���
		if (false == LevelChanged_
			&& true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageMidScoreChangeReady))
		{
			if (true == GameServer::IsHost_)
			{
				// ȣ��Ʈ�� ��� ������ �Ѿ�� �Ѿ��
				if (true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_StageMidScoreChangeReady)
					&& true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StageMidScoreChangeOver))
				{
					// ���� ����������
					std::string_view NextStage = ContentsCore::GetInst()->GetNextStage();
					ContentsCore::GetInst()->ChangeLevelByLoading(ContentsCore::GetInst()->GetNextStage());
					LevelChanged_ = true;
				}
			}
			else
			{
				// ������ ������ȣ ������ �ٷ� �Ѿ
				if (true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageMidScoreChangeReady))
				{
					// ���� ����������
					std::string_view NextStage = ContentsCore::GetInst()->GetNextStage();
					ContentsCore::GetInst()->ChangeLevelByLoading(ContentsCore::GetInst()->GetNextStage());
					LevelChanged_ = true;
				}
			}
		}


		// 2. ������ ��� ���� �غ�ƴ��� Ȯ��
		if (true == GameServer::IsHost_
			&& !GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageMidScoreChangeReady))
		{
			// ������ �ڽŰ� �÷��̾�� �غ� �� �ƴ��� Ȯ���ϸ�
			if (GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_StageMidScoreChangeReady)
				&& GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StageMidScoreChangeReady))
			{
				// ������ȣ '�������γѾ��'��
				GameServer::GetInst()->SetServerSignal(ServerFlag::S_StageMidScoreChangeReady);
			}
		}


		// 1. �ð� ������ ���� �غ��
		if (true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_None))
		{
			GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_StageMidScoreChangeReady);
		}
	}
	// ~~~~~~ ����

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

	// ����
	// ��� �÷��̾��� ���� ������ �ڷᱸ���� ������ ����
	if (true == GameServer::GetInst()->IsServerStart())
	{
		MidScoreTime_ = 0.0f;
		LevelChanged_ = false;

		ServerSetting();
	}
	// ���� ��Ŵ
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
	Score_->GetFont().lock()->SetText("���� ����!", FONT_NOTO_SANS_CJK_SC);

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
	

	// ���� �����ϰ� ��������
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
	for (int i = static_cast<int>(PlayerScores_.size()-1); i > 0; --i)//5���� �ΰ��� ���ϸ� 4���ؾ���->4���� �����ؾ� �� ���� 0�����ؼ� ++�ϴ� �ȵ�
	{
		for (int j = 0; j < i; ++j)
		{
			if (PlayerScores_[j] < PlayerScores_[j + 1])//�տ��ź��� �ڿ��� ũ�� ������(�ڸ��ٲ�)
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
	if (Once_ == true) //�����Ʈ�� ���� ������ ������ �װ� ���� ���� �ϴ� �κ�(�Լ��� ��������)
	{
		for (int i = 0; i < FontScore_.size(); ++i)
		{
			for (int j = 0; j < FontScore_.size(); ++j)
			{
				if (FontScore_[i]->GetFont()->GetText() == std::to_string(PlayerScores_[j]) && i==j)
				{
					float4 Temp = FontScore_[i]->GetFont()->GetScreenPosition();
					FontScore_[i]->GetFont()->SetScreenPostion(float4::Lerp(Temp, { 170.0f, 250.0f + (120.0f * static_cast<float>(j)) }, GameEngineTime::GetDeltaTime() * 10.0f));
					//���� �ϳ� ���� ���� ����+�Ѵ� �����ؾ��ϸ� ��ġ�� ��ħ
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
	// �ڱ����� ��� �÷��̾� + �ڽ�
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
	// �ڱ������� �ִ´�
	std::shared_ptr<GameServer>& Server = GameServer::GetInst();
	ServerPlayerInfo MyInfo;
	MyInfo.ID_ = Server->PlayerID_;
	MyInfo.Color_ = Server->PlayerColorID_;
	MyInfo.Score_ = Server->PlayerScore_;
	MyInfo.Name_ = Server->UserName_;
	AllServerPlayers_.push_back(MyInfo);

	// ID������ ����
	std::sort(AllServerPlayers_.begin(), AllServerPlayers_.end(), IDSmaller);

	// ���� ����
	PlayerScores_.clear();
	PlayerScores_.resize(AllServerPlayersCount_);
	PlayerName_.clear();
	FontScore_.clear();
	Font_PlayerName.clear();
	LastActorPos_ = float4::ZERO;

	// ��Ʈ ���� ����
	for (int i = 0; i < AllServerPlayers_.size(); i++)
	{
		// UI
		// �÷��̾� �̸�
		PlayerName_.push_back(AllServerPlayers_[i].Name_);

		// �÷��̾� ���� '��Ʈ����'
		std::shared_ptr<FontActor> FontScore = CreateActor<FontActor>();
		FontScore->SetFont(std::to_string(AllServerPlayers_[i].Score_), FONT_NOTO_SANS_CJK_SC, 50.0f, { 170,250 + i * 120.0f }, LeftAndRightSort::LEFT);
		FontScore_.push_back(FontScore);

		// �÷��̾� �̸� '��Ʈ����'
		std::shared_ptr<FontActor> FontPlayerName = CreateActor<FontActor>();
		FontPlayerName->SetFont(PlayerName_[i], FONT_TITAN_ONE, 60.0f, { 170, 200 + i * 120.0f }, LeftAndRightSort::LEFT);
		Font_PlayerName.push_back(FontPlayerName);
	}

	
	// *�ֻ��� 4���� ������ �ʿ�
	std::sort(AllServerPlayers_.begin(), AllServerPlayers_.end(), ScoreBigger);

	int LobbyPlayersCount = AllServerPlayersCount_ > 4 ? 4 : AllServerPlayersCount_;

	// �κ� �÷��̾�, ���� ����
	for (int i = 0; i < LobbyPlayersCount; i++)
	{
		// �κ��÷��̾� ���� 2�� ����
		std::shared_ptr<LobbyPlayer> Player = CreateActor<LobbyPlayer>();
		float4 PlayerColor = GameServer::GetInst()->GetPlayerColorReturn(AllServerPlayers_[i].Color_);
		Player->SetPlayerColor(PlayerColor);

		float4 PlayerPos = FirstActorPos + float4(i * 40.0f, i * -15.0f, 0);
		Player->GetTransform().SetWorldPosition(PlayerPos);
		Player->GetTransform().SetWorldRotation(FirstActorRot + float4(0, i * 10.0f, 0));

		LobbyPlayers_.push_back(Player);

		// ���ڴ� �κ��÷��̾� -1 �� ����
		// ������ �κ��÷��̾�
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

	// �ִϸ��̼� ����
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

	// ó���� �����ٶ��� ID�������
	std::sort(AllServerPlayers_.begin(), AllServerPlayers_.end(), IDSmaller);

}

void MidScoreLevel::NoServerSetting()
{
	// 2�� �����ض�
	AllServerPlayersCount_ = 4;

	AllServerPlayers_.emplace_back(0, 0, 200);
	AllServerPlayers_.emplace_back(1, 3, 500);
	AllServerPlayers_.emplace_back(2, 2, 100);
	AllServerPlayers_.emplace_back(3, 4, 400);

	// ���� ����
	PlayerScores_.resize(AllServerPlayersCount_);

	for (int i = 0; i < AllServerPlayersCount_; i++)
	{
		// �κ��÷��̾� ���� 2�� ����
		std::shared_ptr<LobbyPlayer> Player = CreateActor<LobbyPlayer>();
		float4 PlayerPos = FirstActorPos + float4(i * 40.0f, i * -15.0f, 0);
		Player->GetTransform().SetWorldPosition(PlayerPos);
		Player->GetTransform().SetWorldRotation(FirstActorRot + float4(0, i * 10.0f, 0));

		LobbyPlayers_.push_back(Player);
		
		// UI
		// �÷��̾� �̸�
		PlayerName_.push_back("Player" + std::to_string(i));

		// �÷��̾� ���� '��Ʈ����'
		std::shared_ptr<FontActor> FontScore = CreateActor<FontActor>();
		FontScore->SetFont("Score" + std::to_string(PlayerScores_[i]), FONT_NOTO_SANS_CJK_SC, 50.0f, {170,250 + i * 120.0f}, LeftAndRightSort::LEFT);
		FontScore_.push_back(FontScore);

		// �÷��̾� �̸� '��Ʈ����'
		std::shared_ptr<FontActor> FontPlayerName = CreateActor<FontActor>();
		FontPlayerName->SetFont(PlayerName_[i] + "�� �÷��̾�", FONT_TITAN_ONE, 60.0f, {170, 200 + i * 120.0f}, LeftAndRightSort::LEFT);
		Font_PlayerName.push_back(FontPlayerName);

		// ���ڴ� �κ��÷��̾� -1 �� ����
		// ������ �κ��÷��̾�
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

	// �ִϸ��̼� ����
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
		//���� �ε����� ��ġ�ų� �Ѿ�ٸ�
		return;
	}

	int Pivot = _First;
	int i = _First + 1;//�� ó���� �Ǻ�(����)��⿡ �� ������ First�� �α����� + 1
	int j = _Last;
	int Temp;

	while (i <= j)
	{
		while ((arr[i] > arr[Pivot]) && (i <= _Last))
		{
			//arr[i]���� arr[Pivot]�� ������ �۰� �ε���i�� _Last�ε������� �۰ų� ���ٸ�(������ ������ ���� ����)
			i++;
		}
		while ((arr[j] <= arr[Pivot]) && (j > _First))
		{
			//���������� ��ĭ��ĭ �������� �̵��ϴ� --
			j--;
		}

		if (i >= j)//i�� j�� �������ų� �Ѿ�ٸ� while���� �����
		{
			break;
		}

		//���� �ڸ��� �ٲ۴�
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
