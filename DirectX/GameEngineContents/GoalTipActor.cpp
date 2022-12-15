#include "PreCompile.h"
#include "GoalTipActor.h"

GoalTipActor::GoalTipActor() 
{
}

GoalTipActor::~GoalTipActor() 
{
}

void GoalTipActor::Start()
{
	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->GetTransform().SetWorldScale({ 452.0f, 103.0f });
	Renderer_->GetTransform().SetWorldPosition({ -800.0f, 400.0f });
	Renderer_->SetPivot(PIVOTMODE::LEFTTOP);
	Renderer_->SetTexture("Goal.png");

	Font_ = CreateComponent<GameEngineFontRenderer>();
	Font_->SetSize(30.0f);
	Font_->ChangeCamera(CAMERAORDER::UICAMERA);
	Font_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	Font_->SetText("결승선에 도달하세요!", "Noto Sans CJK SC");
	Font_->SetScreenPostion({ 210.0f, 70.0f });

}

void GoalTipActor::Update(float _DeltaTime)
{
}

