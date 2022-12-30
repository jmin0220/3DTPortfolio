#include "PreCompile.h"
#include "RankingActor.h"

#include <GameEngineBase/GameEngineRandom.h>

#include <algorithm>
#include "HoopsScoreRing.h"

RankingActor::RankingActor()
	: S_PlayersCount_(0)
	, SortingCycle_(5.0f)
	, SortingTime_(0.0f)
{
}

RankingActor::~RankingActor() 
{
}

void RankingActor::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("RandomScore"))
	{
		GameEngineInput::GetInst()->CreateKey("RandomScore", VK_RETURN);
	}


	if (false == GameServer::GetInst()->IsServerStart())
	{
		for (int i = 0; i < 5; ++i)
		{
			Renderer_[4 - i] = CreateComponent<GameEngineUIRenderer>();
			Renderer_[4 - i]->SetTexture("HUD_yellow_team_1080p.png");
			Renderer_[4 - i]->GetTransform().SetWorldScale({ 176,80 });
			Renderer_[4 - i]->GetTransform().SetWorldPosition({ -700.0f,-200.0f + 100.0f * static_cast<float>(4 - i) });

			Font_[i] = CreateComponent<GameEngineFontRenderer>();
			Font_[i]->SetText("Player" + std::to_string(i), FONT_TITAN_ONE);
			Font_[i]->ChangeCamera(CAMERAORDER::UICAMERA);
			Font_[i]->SetLeftAndRightSort(LeftAndRightSort::CENTER);
			Font_[i]->SetScreenPostion({ 100,220 + 100 * static_cast<float>(i) });

			Score_[i] = 0;

			ScoreFont_[i] = CreateComponent<GameEngineFontRenderer>();
			ScoreFont_[i]->SetText(std::to_string(Score_[i]), FONT_NOTO_SANS_CJK_SC);
			ScoreFont_[i]->ChangeCamera(CAMERAORDER::UICAMERA);
			ScoreFont_[i]->SetLeftAndRightSort(LeftAndRightSort::CENTER);
			ScoreFont_[i]->SetScreenPostion({ 100,240 + 100 * static_cast<float>(i) });
			ScoreFont_[i]->SetSize(25.0f);
		}
	}
	else
	{
		S_Players.resize(5);

		S_PlayersCount_ = GameServer::GetInst()->GetAllPlayersCount();

		S_Renderer_.resize(S_PlayersCount_);
		S_Font_.resize(S_PlayersCount_);
		S_Score_.resize(S_PlayersCount_);
		S_ScoreFont_.resize(S_PlayersCount_);

		std::vector<ServerPlayerInfo> ServerPlayers;
		GameServer::GetInst()->GetAllPlayersInfo(ServerPlayers);

		for (int i = 0; i < S_PlayersCount_; ++i)
		{
			S_Renderer_[S_PlayersCount_ -1 - i] = CreateComponent<GameEngineUIRenderer>();
			S_Renderer_[S_PlayersCount_ - 1 - i]->SetTexture("HUD_yellow_team_1080p.png");
			S_Renderer_[S_PlayersCount_ - 1 - i]->GetTransform().SetWorldScale({ 176,80 });
			S_Renderer_[S_PlayersCount_ - 1 - i]->GetTransform().SetWorldPosition({ -700.0f,-200.0f + 100.0f * static_cast<float>(S_PlayersCount_ - 1 - i) });

			S_Font_[i] = CreateComponent<GameEngineFontRenderer>();
			S_Font_[i]->SetText(ServerPlayers[i].Name_, FONT_TITAN_ONE);
			S_Font_[i]->ChangeCamera(CAMERAORDER::UICAMERA);
			S_Font_[i]->SetLeftAndRightSort(LeftAndRightSort::CENTER);
			S_Font_[i]->SetScreenPostion({ 100,220 + 100 * static_cast<float>(i) });

			S_Score_[i] = static_cast<int>(ServerPlayers[i].Score_);

			S_ScoreFont_[i] = CreateComponent<GameEngineFontRenderer>();
			S_ScoreFont_[i]->SetText(std::to_string(S_Score_[i]), FONT_NOTO_SANS_CJK_SC);
			S_ScoreFont_[i]->ChangeCamera(CAMERAORDER::UICAMERA);
			S_ScoreFont_[i]->SetLeftAndRightSort(LeftAndRightSort::CENTER);
			S_ScoreFont_[i]->SetScreenPostion({ 100,240 + 100 * static_cast<float>(i) });
			S_ScoreFont_[i]->SetSize(25.0f);
		}
	}

}

void RankingActor::Update(float _DeltaTime)
{
	if (false == GameServer::GetInst()->IsServerStart())
	{
		if (GameEngineInput::GetInst()->IsDown("RandomScore"))
		{
			for (int i = 0; i < 5; ++i)
			{
				Score_[i] = GameEngineRandom::MainRandom.RandomInt(0, 2);

				ScoreFont_[i]->SetText(std::to_string(Score_[i]), FONT_NOTO_SANS_CJK_SC);
			}

			BubbleSort();
		}

		ChaseNameToScore();
	}
	else
	{
		// 정보가 바뀌었을 때만 정렬 하면 됨
		GameServer::GetInst()->GetAllPlayersInfo(S_Players);

		if (true == HoopsScoreRing::IsScoreChanged())
		{
			for (int i = 0; i < S_PlayersCount_; i++)
			{
				S_Score_[i] = static_cast<int>(S_Players[i].Score_);

				S_ScoreFont_[i]->SetText(std::to_string(S_Score_[i]), FONT_NOTO_SANS_CJK_SC);

				S_Font_[i]->SetText(S_Players[i].Name_);
			}

			S_BubbleSort();

			HoopsScoreRing::ScoreChanged_ = false;
		}
		
		S_ChaseNameToScore();

	}

}

void RankingActor::LevelStartEvent()
{
}

void RankingActor::LevelEndEvent()
{
}

void RankingActor::BubbleSort()
{
	bool SwapFlg = false;
	do
	{
		SwapFlg = false;

		for (int j = 0; j < 4; ++j)
		{
			if (Score_[j] < Score_[j + 1])//앞에거보다 뒤에게 크면 앞으로(자리바꿈)
			{
				SwapFlg = true;

				GameEngineDebug::OutPutString("Swap >> " + std::to_string(Score_[j])
					+ "  " + std::to_string(Score_[j + 1]));

				int Temp = Score_[j];
				Score_[j] = Score_[j + 1];
				Score_[j + 1] = Temp;

				std::shared_ptr<GameEngineFontRenderer> FTemp = ScoreFont_[j];
				ScoreFont_[j] = ScoreFont_[j + 1];
				ScoreFont_[j + 1] = FTemp;

				std::shared_ptr<GameEngineFontRenderer> STemp = Font_[j];
				Font_[j] = Font_[j + 1];
				Font_[j + 1] = STemp;

				std::shared_ptr<GameEngineUIRenderer> UITemp = Renderer_[4-j-1];
				Renderer_[4-j-1] = Renderer_[4-j];
				Renderer_[4-j] = UITemp;
			}
		}
	} while (SwapFlg);
}

void RankingActor::ChaseNameToScore()
{
	for (int i = 0; i < 5; ++i)
	{
		float4 Temp = ScoreFont_[i]->GetScreenPosition();
		ScoreFont_[i]->SetScreenPostion(float4::Lerp(Temp, { 100.0f, 240.0f + (100.0f * static_cast<float>(i)) }, GameEngineTime::GetDeltaTime() * 3.0f));

		Font_[i]->SetScreenPostion({ScoreFont_[i]->GetScreenPosition().x,ScoreFont_[i]->GetScreenPosition().y - 20.0f });
		Renderer_[4-i]->GetTransform().SetWorldPosition({ ScoreFont_[i]->GetScreenPosition().x - 800.0f, 440.0f - ScoreFont_[i]->GetScreenPosition().y });
	}
}

void RankingActor::S_BubbleSort()
{
	bool SwapFlg = false;
	do
	{
		SwapFlg = false;

		for (int j = 0; j < S_PlayersCount_ - 1; ++j)
		{
			if (S_Score_[j] < S_Score_[j + 1])//앞에거보다 뒤에게 크면 앞으로(자리바꿈)
			{
				SwapFlg = true;

				GameEngineDebug::OutPutString("Swap >> " + std::to_string(j) + "  " + std::to_string(S_Score_[j])
					+ "  " + std::to_string(Score_[j + 1]));

				int Temp = S_Score_[j];
				S_Score_[j] = S_Score_[j + 1];
				S_Score_[j + 1] = Temp;

				std::shared_ptr<GameEngineFontRenderer> FTemp = S_ScoreFont_[j];
				S_ScoreFont_[j] = S_ScoreFont_[j + 1];
				S_ScoreFont_[j + 1] = FTemp;

				std::shared_ptr<GameEngineFontRenderer> STemp = S_Font_[j];
				S_Font_[j] = S_Font_[j + 1];
				S_Font_[j + 1] = STemp;

				std::shared_ptr<GameEngineUIRenderer> UITemp = S_Renderer_[S_PlayersCount_ - 1 - j - 1];
				S_Renderer_[S_PlayersCount_ - 1 - j - 1] = S_Renderer_[S_PlayersCount_ - 1 - j];
				S_Renderer_[S_PlayersCount_ - 1 - j] = UITemp;
			}
		}
	} while (SwapFlg);
}

void RankingActor::S_ChaseNameToScore()
{
	for (int i = 0; i < S_PlayersCount_; ++i)
	{
		float4 Temp = S_ScoreFont_[i]->GetScreenPosition();
		S_ScoreFont_[i]->SetScreenPostion(float4::Lerp(Temp, { 100.0f, 240.0f + (100.0f * static_cast<float>(i)) }, GameEngineTime::GetDeltaTime() * 3.0f));

		S_Font_[i]->SetScreenPostion({ S_ScoreFont_[i]->GetScreenPosition().x,S_ScoreFont_[i]->GetScreenPosition().y - 20.0f });
		S_Renderer_[S_PlayersCount_ - 1 - i]->GetTransform().SetWorldPosition({ S_ScoreFont_[i]->GetScreenPosition().x - 800.0f, 440.0f - S_ScoreFont_[i]->GetScreenPosition().y });
	}
}