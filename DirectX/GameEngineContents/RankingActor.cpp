#include "PreCompile.h"
#include "RankingActor.h"

#include <GameEngineBase/GameEngineRandom.h>

#include <algorithm>

RankingActor::RankingActor() 
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

	for (int i = 0; i < 5; ++i)
	{
		Renderer_[4-i] = CreateComponent<GameEngineUIRenderer>();
		Renderer_[4-i]->SetTexture("HUD_yellow_team_1080p.png");
		Renderer_[4-i]->GetTransform().SetWorldScale({ 176,80 });
		Renderer_[4-i]->GetTransform().SetWorldPosition({ -700.0f,-200.0f + 100.0f * static_cast<float>(4-i) });

		Font_[i] = CreateComponent<GameEngineFontRenderer>();
		Font_[i]->SetText("Player" + std::to_string(i), FONT_TITAN_ONE);
		Font_[i]->ChangeCamera(CAMERAORDER::UICAMERA);
		Font_[i]->SetLeftAndRightSort(LeftAndRightSort::CENTER);
		Font_[i]->SetScreenPostion({100,220+100* static_cast<float>(i) });

		Score_[i] = 0;

		ScoreFont_[i] = CreateComponent<GameEngineFontRenderer>();
		ScoreFont_[i]->SetText(std::to_string(Score_[i]), FONT_NOTO_SANS_CJK_SC);
		ScoreFont_[i]->ChangeCamera(CAMERAORDER::UICAMERA);
		ScoreFont_[i]->SetLeftAndRightSort(LeftAndRightSort::CENTER);
		ScoreFont_[i]->SetScreenPostion({ 100,240 + 100 * static_cast<float>(i) });
		ScoreFont_[i]->SetSize(25.0f);
	}
}

void RankingActor::Update(float _DeltaTime)
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