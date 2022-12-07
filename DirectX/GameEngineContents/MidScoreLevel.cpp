#include "PreCompile.h"
#include "MidScoreLevel.h"

#include "LobbyPlayer.h"
#include "FloorActor.h"
#include "GoalTipActor.h"

MidScoreLevel::MidScoreLevel() 
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
}

void MidScoreLevel::End()
{
}

void MidScoreLevel::LevelStartEvent()
{
	Player_ = CreateActor<LobbyPlayer>();
	Player_->GetTransform().SetWorldPosition({ 0, -15, 0 });
	Player_->GetTransform().SetWorldRotation({ 0,160,0 });

	Chair_ = CreateActor<FloorActor>();

	Score_ = CreateActor<GoalTipActor>();
	Score_->GetFont().lock()->SetText("현재 점수!", FONT_NOTO_SANS_CJK_SC);
}

void MidScoreLevel::LevelEndEvent()
{
	Player_->Death();
	Chair_->Death();
	Score_->Death();
}
