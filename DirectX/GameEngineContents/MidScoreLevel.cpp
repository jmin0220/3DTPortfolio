#include "PreCompile.h"
#include "MidScoreLevel.h"

#include "LobbyPlayer.h"
#include "FloorActor.h"
#include "GoalTipActor.h"
#include "MidScoreBGActor.h"
#include "FontActor.h"

MidScoreLevel::MidScoreLevel() 
	:FallingTime_(0.0f)
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
}

void MidScoreLevel::End()
{
}

void MidScoreLevel::LevelStartEvent()
{
	FallingTime_ = 0.0f;

	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	BG_ = CreateActor<MidScoreBGActor>();

	Score_ = CreateActor<GoalTipActor>();
	Score_->GetFont().lock()->SetText("현재 점수!", FONT_NOTO_SANS_CJK_SC);

	{
		//플레이어 1번
		Player1_ = CreateActor<LobbyPlayer>();
		Player1_->GetTransform().SetWorldPosition({ -20, 0, 100 });
		Player1_->GetTransform().SetWorldRotation({ 0,160,0 });
		Player1_->ChangeAnimationJogging();

		Player1Name_ = "Player 1";

		Chair1_ = CreateActor<FloorActor>();
		Chair1_->GetTransform().SetWorldPosition({ -20.0f, 15.5f, 100.0f });
	}
	{
		//플레이어 2번
		Player2_ = CreateActor<LobbyPlayer>();
		Player2_->GetTransform().SetWorldPosition({ 20, -15, 100 });
		Player2_->GetTransform().SetWorldRotation({ 0,170,0 });
		Player2_->ChangeAnimationGasp();

		Player2Name_ = "Player 2";

		Chair2_ = CreateActor<FloorActor>();
		Chair2_->GetTransform().SetWorldPosition({ 20.0f, 0.5f, 100.0f });
	}
	{
		//플레이어 3번
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
		//1등 닉네임+점수 표시
		Font1_ = CreateActor<FontActor>();
		Font1_->SetFont("1st.   " + Player1Name_, FONT_TITAN_ONE, 60.0f, { 20,200 }, LeftAndRightSort::LEFT);
		
		Font1Score_ = CreateActor<FontActor>();
		Font1Score_->SetFont("123120", FONT_NOTO_SANS_CJK_SC, 50.0f, { 20,250 }, LeftAndRightSort::LEFT);
	}
	{
		//2등 닉네임+점수 표시
		Font2_ = CreateActor<FontActor>();
		Font2_->SetFont("2nd. " + Player2Name_, FONT_TITAN_ONE, 60.0f, { 20,320 }, LeftAndRightSort::LEFT);

		Font2Score_ = CreateActor<FontActor>();
		Font2Score_->SetFont("77777", FONT_NOTO_SANS_CJK_SC, 50.0f, { 20,370 }, LeftAndRightSort::LEFT);
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
	Font1Score_->Death();
	Font2_->Death();
	Font2Score_->Death();
}
