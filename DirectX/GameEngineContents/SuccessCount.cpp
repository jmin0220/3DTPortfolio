#include "PreCompile.h"
#include "SuccessCount.h"

int SuccessCount::Score_ = 0;
//int SuccessCount::Player1Score_ = 0;
//int SuccessCount::Player2Score_ = 0;
//int SuccessCount::Player3Score_ = 0;
//int SuccessCount::Player4Score_ = 0;//나중에 멀티용 다른 플레이어 점수

SuccessCount::SuccessCount() 
	:MaxCount_(30)
	,CurrentCount_(0)
{
}

SuccessCount::~SuccessCount() 
{
}

void SuccessCount::Start()
{
	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->GetTransform().SetWorldScale({ 452,103,1 });
	Renderer_->SetPivot(PIVOTMODE::RIGHTTOP);
	Renderer_->GetTransform().SetWorldPosition({ 1000.0f, 400.0f,0 });
	Renderer_->SetTexture("Success.png");

	SuccessFont_ = CreateComponent<GameEngineFontRenderer>();
	SuccessFont_->SetSize(22.0f);
	SuccessFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	SuccessFont_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	SuccessFont_->SetText("내 점수", "Noto Sans CJK SC");
	SuccessFont_->SetScreenPostion({ 1490.0f, 60.0f });

	/*MaxFont_ = CreateComponent<GameEngineFontRenderer>();
	MaxFont_->SetSize(30.0f);
	MaxFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	MaxFont_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	MaxFont_->SetText(std::to_string(CurrentCount_) + "/" + std::to_string(MaxCount_), "Titan One");
	MaxFont_->SetScreenPostion({ 1490.0f, 90.0f });*/

	ScoreFont_ = CreateComponent<GameEngineFontRenderer>();
	ScoreFont_->SetSize(30.0f);
	ScoreFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	ScoreFont_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	ScoreFont_->SetText(std::to_string(Score_), "Titan One");
	ScoreFont_->SetScreenPostion({ 1490.0f, 90.0f });
}

void SuccessCount::Update(float _DeltaTime)
{
	ScoreFont_->SetText(std::to_string(Score_), "Titan One");
}

