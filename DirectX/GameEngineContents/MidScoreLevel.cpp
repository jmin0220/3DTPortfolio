#include "PreCompile.h"
#include "MidScoreLevel.h"

#include "LobbyPlayer.h"
#include "FloorActor.h"
#include "GoalTipActor.h"
#include "MidScoreBGActor.h"
#include "FontActor.h"

#include <GameEngineBase/GameEngineRandom.h>

MidScoreLevel::MidScoreLevel()
	: FallingTime_(0.0f)
	, PlayerScores_{}
	, BeforeScoreTime_(0.0f)
	, IsScoreOn_(false)
	, Index_{}
	, IsLerpStart_(false)
	, Once_(false)
	, LevelChanged_(false)
	, MidScoreTime_(0.0f)
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
	// ����
	if (true == GameServer::GetInst()->IsServerStart())
	{
		MidScoreTime_ += _DeltaTime;
		if (MidScoreTime_ < 7.0f)
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
					return;
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
					return;
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


	{
		//���� �÷��̾� �߶� �ִϸ��̼�
		if (Player4_->GetTransform().GetWorldPosition().y > -400.0f)
		{
			FallingTime_ += _DeltaTime * 100.0f;
			Player4_->GetTransform().SetWorldPosition({ 40, 100 - FallingTime_, 140 });
		}
		else
		{
			Player4_->GetTransform().SetWorldPosition({ 40, 100, 140 });
			FallingTime_ = 0.0f;
		}
	}

	{	
		//���ʹ����� ���� ���� ����
		if (true == GameEngineInput::GetInst()->IsDown("RandomScore"))
		{
			for (int i = 0; i < 5; ++i)
			{
				PlayerScores_[i] = GameEngineRandom::MainRandom.RandomInt(10, 200);

				Font_PlayerName[i]->SetFont(PlayerName_[i], FONT_TITAN_ONE);
				FontScore_[i]->SetFont(std::to_string(PlayerScores_[i]), FONT_NOTO_SANS_CJK_SC, 50.0f, LeftAndRightSort::LEFT);
			}
			IsScoreOn_ = true;
		}
		
		if (IsScoreOn_ == true)
		{
			BeforeScoreTime_ += _DeltaTime;
		}

		if (BeforeScoreTime_ > 2.0f)
		{
			BubbleSortLerp();
			IsScoreOn_ = false;
			BeforeScoreTime_ = 0.0f;
			Once_ = true;
		}
	}

	if (Once_ == true)
	{
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (FontScore_[i]->GetFont().lock()->GetText() == std::to_string(PlayerScores_[j]))
				{
					float4 Temp = FontScore_[i]->GetFont().lock()->GetScreenPosition();
					FontScore_[i]->GetFont().lock()->SetScreenPostion(float4::Lerp(Temp, { 170.0f, 250.0f + (120.0f * static_cast<float>(j)) }, _DeltaTime * 10.0f));
				}
			}
		}
	}
}



void MidScoreLevel::End()
{
}

void MidScoreLevel::LevelStartEvent()
{
	// ����
	// ��� �÷��̾��� ���� ������ �ڷᱸ���� ������ ����
	MidScoreTime_ = 0.0f;
	LevelChanged_ = false;
	// ~ ����


	if (false == GameEngineInput::GetInst()->IsKey("RandomScore"))
	{
		GameEngineInput::GetInst()->CreateKey("RandomScore", VK_RETURN);
	}


	FallingTime_ = 0.0f;

	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	BG_ = CreateActor<MidScoreBGActor>();

	Score_ = CreateActor<GoalTipActor>();
	Score_->GetFont().lock()->SetText("���� ����!", FONT_NOTO_SANS_CJK_SC);

	{
		//�÷��̾� 1��
		Player1_ = CreateActor<LobbyPlayer>();
		Player1_->GetTransform().SetWorldPosition({ -20, 0, 100 });
		Player1_->GetTransform().SetWorldRotation({ 0,160,0 });
		Player1_->ChangeAnimationJogging();

		PlayerName_[0] = "CAT";
		PlayerName_[1] = "DOG";
		PlayerName_[2] = "COW";
		PlayerName_[3] = "ANT";
		PlayerName_[4] = "NOM";

		Chair1_ = CreateActor<FloorActor>();
		Chair1_->GetTransform().SetWorldPosition({ -20.0f, 15.5f, 100.0f });
	}
	{
		//�÷��̾� 2��
		Player2_ = CreateActor<LobbyPlayer>();
		Player2_->GetTransform().SetWorldPosition({ 20, -15, 100 });
		Player2_->GetTransform().SetWorldRotation({ 0,170,0 });
		Player2_->ChangeAnimationGasp();

		//Player2Name_ = "Player 2";

		Chair2_ = CreateActor<FloorActor>();
		Chair2_->GetTransform().SetWorldPosition({ 20.0f, 0.5f, 100.0f });
	}
	{
		//�÷��̾� 3��
		Player3_ = CreateActor<LobbyPlayer>();
		Player3_->GetTransform().SetWorldPosition({ 60, -30, 100 });
		Player3_->GetTransform().SetWorldRotation({ 0,180,0 });

		Chair3_ = CreateActor<FloorActor>();
		Chair3_->GetTransform().SetWorldPosition({ 60.0f, -14.5f, 100.0f });
	}
	{
		Player4_ = CreateActor<LobbyPlayer>();
		Player4_->GetTransform().SetWorldPosition({ 40, -100, 140 });
		Player4_->GetTransform().SetWorldRotation({ 0,180,0 });
		Player4_->ChangeAnimationTumbel();
	}

	{
		//1�� �г���+���� ǥ��
		Font1_ = CreateActor<FontActor>();
		Font1_->SetFont("1st.   ", FONT_TITAN_ONE, 60.0f, { 20,200 }, LeftAndRightSort::LEFT);
		
		Font_PlayerName[0] = CreateActor<FontActor>();
		Font_PlayerName[0]->SetFont(PlayerName_[0], FONT_TITAN_ONE, 60.0f, { 170,200 }, LeftAndRightSort::LEFT);
	
		FontScore_[0] = CreateActor<FontActor>();
		FontScore_[0]->SetFont(std::to_string(PlayerScores_[0]), FONT_NOTO_SANS_CJK_SC, 50.0f, { 170,250 }, LeftAndRightSort::LEFT);
	}
	{
		//2�� �г���+���� ǥ��
		Font2_ = CreateActor<FontActor>();
		Font2_->SetFont("2nd. ", FONT_TITAN_ONE, 60.0f, { 20,320 }, LeftAndRightSort::LEFT);

		Font_PlayerName[1] = CreateActor<FontActor>();
		Font_PlayerName[1]->SetFont(PlayerName_[1], FONT_TITAN_ONE, 60.0f, { 170,320 }, LeftAndRightSort::LEFT);

		FontScore_[1] = CreateActor<FontActor>();
		FontScore_[1]->SetFont(std::to_string(PlayerScores_[1]), FONT_NOTO_SANS_CJK_SC, 50.0f, { 170,370 }, LeftAndRightSort::LEFT);

		{
			Font_PlayerName[2] = CreateActor<FontActor>();
			Font_PlayerName[2]->SetFont(PlayerName_[2], FONT_TITAN_ONE, 60.0f, { 170,440 }, LeftAndRightSort::LEFT);
			FontScore_[2] = CreateActor<FontActor>();
			FontScore_[2]->SetFont(std::to_string(PlayerScores_[2]), FONT_NOTO_SANS_CJK_SC, 50.0f, { 170,490 }, LeftAndRightSort::LEFT);

			Font_PlayerName[3] = CreateActor<FontActor>();
			Font_PlayerName[3]->SetFont(PlayerName_[3], FONT_TITAN_ONE, 60.0f, { 170,560 }, LeftAndRightSort::LEFT);
			FontScore_[3] = CreateActor<FontActor>();
			FontScore_[3]->SetFont(std::to_string(PlayerScores_[3]), FONT_NOTO_SANS_CJK_SC, 50.0f, { 170,610 }, LeftAndRightSort::LEFT);

			Font_PlayerName[4] = CreateActor<FontActor>();
			Font_PlayerName[4]->SetFont(PlayerName_[4], FONT_TITAN_ONE, 60.0f, { 170,680 }, LeftAndRightSort::LEFT);
			FontScore_[4] = CreateActor<FontActor>();
			FontScore_[4]->SetFont(std::to_string(PlayerScores_[4]), FONT_NOTO_SANS_CJK_SC, 50.0f, { 170,730 }, LeftAndRightSort::LEFT);
		}
	}
}

void MidScoreLevel::LevelEndEvent()
{
	Player1_->Death();
	Chair1_->Death();
	Player2_->Death();
	Chair2_->Death();
	Player3_->Death();
	Chair3_->Death();

	Score_->Death();

	Font1_->Death();
	FontScore_[0]->Death();
	Font2_->Death();
	FontScore_[1]->Death();

	Player4_->Death();
	ContentsCore::GetInst()->ReleaseCurLevelResource();
}


void MidScoreLevel::FakeSort()
{
	{
		if (PlayerScores_[0] < PlayerScores_[1])
		{
			float4 f4CurrentScale1 = Font_PlayerName[0]->GetFont().lock()->GetScreenPosition();
			float4 f4DestinationScale1 = { 170.0f,320.0f };
			Font_PlayerName[0]->GetFont().lock()->SetScreenPostion({float4::Lerp(f4CurrentScale1, f4DestinationScale1, GameEngineTime::GetDeltaTime() * 10.f)});

			float4 f4CurrentScale1s = FontScore_[0]->GetFont().lock()->GetScreenPosition();
			float4 f4DestinationScale1s = { 170.0f,370.0f };
			FontScore_[0]->GetFont().lock()->SetScreenPostion({float4::Lerp(f4CurrentScale1s, f4DestinationScale1s, GameEngineTime::GetDeltaTime() * 10.f)});

			float4 f4CurrentScale2 = Font_PlayerName[1]->GetFont().lock()->GetScreenPosition();
			float4 f4DestinationScale2 = { 170.0f,200.0f };
			Font_PlayerName[1]->GetFont().lock()->SetScreenPostion({float4::Lerp(f4CurrentScale2, f4DestinationScale2, GameEngineTime::GetDeltaTime() * 10.f)});

			float4 f4CurrentScale2s = FontScore_[1]->GetFont().lock()->GetScreenPosition();
			float4 f4DestinationScale2s = { 170.0f,250.0f };
			FontScore_[1]->GetFont().lock()->SetScreenPostion({float4::Lerp(f4CurrentScale2s, f4DestinationScale2s, GameEngineTime::GetDeltaTime() * 10.f)});
		}
		else
		{
			float4 f4CurrentScale1 = Font_PlayerName[0]->GetFont().lock()->GetScreenPosition();
			float4 f4DestinationScale1 = { 170.0f,200.0f };
			Font_PlayerName[0]->GetFont().lock()->SetScreenPostion({float4::Lerp(f4CurrentScale1, f4DestinationScale1, GameEngineTime::GetDeltaTime() * 10.f)});

			float4 f4CurrentScale1s = FontScore_[0]->GetFont().lock()->GetScreenPosition();
			float4 f4DestinationScale1s = { 170.0f,250.0f };
			FontScore_[0]->GetFont().lock()->SetScreenPostion({float4::Lerp(f4CurrentScale1s, f4DestinationScale1s, GameEngineTime::GetDeltaTime() * 10.f)});

			float4 f4CurrentScale2 = Font_PlayerName[1]->GetFont().lock()->GetScreenPosition();
			float4 f4DestinationScale2 = { 170.0f,320.0f };
			Font_PlayerName[1]->GetFont().lock()->SetScreenPostion({float4::Lerp(f4CurrentScale2, f4DestinationScale2, GameEngineTime::GetDeltaTime() * 10.f)});

			float4 f4CurrentScale2s = FontScore_[1]->GetFont().lock()->GetScreenPosition();
			float4 f4DestinationScale2s = { 170.0f,370.0f };
			FontScore_[1]->GetFont().lock()->SetScreenPostion({float4::Lerp(f4CurrentScale2s, f4DestinationScale2s, GameEngineTime::GetDeltaTime() * 10.f)});
		}
	}

}

void MidScoreLevel::BubbleSort()
{
	//����
	for (int i = 4; i > 0; --i)//5���� �ΰ��� ���ϸ� 4���ؾ���->4���� �����ؾ� �� ���� 0�����ؼ� ++�ϴ� �ȵ�
	{
		for (int j = 0; j < i; ++j)
		{
			if (PlayerScores_[j] < PlayerScores_[j + 1])//�տ��ź��� �ڿ��� ũ�� ������(�ڸ��ٲ�)
			{
				int Temp = PlayerScores_[j];
				PlayerScores_[j] = PlayerScores_[j + 1];
				PlayerScores_[j + 1] = Temp;
				FontScore_[j]->SetFont(std::to_string(PlayerScores_[j]), FONT_NOTO_SANS_CJK_SC, 50.0f, LeftAndRightSort::LEFT);
				FontScore_[j+1]->SetFont(std::to_string(PlayerScores_[j+1]), FONT_NOTO_SANS_CJK_SC, 50.0f, LeftAndRightSort::LEFT);

				std::string Temps = PlayerName_[j];
				PlayerName_[j] = PlayerName_[j + 1];
				PlayerName_[j + 1] = Temps;

				Font_PlayerName[j]->SetFont(PlayerName_[j], FONT_TITAN_ONE);
				Font_PlayerName[j+1]->SetFont(PlayerName_[j+1], FONT_TITAN_ONE);
			}
		}
	}
}

void MidScoreLevel::BubbleSortLerp()
{
	for (int i = 4; i > 0; --i)//5���� �ΰ��� ���ϸ� 4���ؾ���->4���� �����ؾ� �� ���� 0�����ؼ� ++�ϴ� �ȵ�
	{
		for (int j = 0; j < i; ++j)
		{
			if (PlayerScores_[j] < PlayerScores_[j + 1])//�տ��ź��� �ڿ��� ũ�� ������(�ڸ��ٲ�)
			{
				int Temp = PlayerScores_[j];
				PlayerScores_[j] = PlayerScores_[j + 1];
				PlayerScores_[j + 1] = Temp;

			/*	FontScore_[j]->SetFont(std::to_string(PlayerScores_[j]), FONT_NOTO_SANS_CJK_SC, 50.0f, LeftAndRightSort::LEFT);
				FontScore_[j + 1]->SetFont(std::to_string(PlayerScores_[j + 1]), FONT_NOTO_SANS_CJK_SC, 50.0f, LeftAndRightSort::LEFT);

				std::string Temps = PlayerName_[j];
				PlayerName_[j] = PlayerName_[j + 1];
				PlayerName_[j + 1] = Temps;

				Font_PlayerName[j]->SetFont(PlayerName_[j], FONT_TITAN_ONE);
				Font_PlayerName[j + 1]->SetFont(PlayerName_[j + 1], FONT_TITAN_ONE);*/
			}
		}
	}
	
}
}

