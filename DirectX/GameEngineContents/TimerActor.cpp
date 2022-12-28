#include "PreCompile.h"
#include "TimerActor.h"

const float PivotX = -400;
const float PivotY = 100;

TimerActor::TimerActor() 
{
}

TimerActor::~TimerActor() 
{
}

void TimerActor::Start()
{
	Plate_ = CreateComponent<GameEngineUIRenderer>();
	Plate_->GetTransform().SetWorldScale({ 452, 103,1 });
	Plate_->SetPivot(PIVOTMODE::RIGHTTOP);
	Plate_->GetTransform().SetWorldPosition({ 1000.0f + PivotX, 400.0f + PivotY, 0 });
	Plate_->SetTexture("Success.png");

	FontOneMinute_ = CreateComponent<GameEngineFontRenderer>();
	FontOneMinute_->ChangeCamera(CAMERAORDER::UICAMERA);
	FontOneMinute_->SetText("0", FONT_TITAN_ONE);
	FontOneMinute_->SetSize(40.0f);
	FontOneMinute_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	FontOneMinute_->SetScreenPostion({ 1450.0f + PivotX, 75.0f + PivotY });

	Colon_ = CreateComponent<GameEngineFontRenderer>();
	Colon_->ChangeCamera(CAMERAORDER::UICAMERA);
	Colon_->SetText(":", FONT_TITAN_ONE);
	Colon_->SetSize(40.0f);
	Colon_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	Colon_->SetScreenPostion({ 1475.0f + PivotX, 70.0f + PivotY });

	FontTenSecond_ = CreateComponent<GameEngineFontRenderer>();
	FontTenSecond_->ChangeCamera(CAMERAORDER::UICAMERA);
	FontTenSecond_->SetText("0", FONT_TITAN_ONE);
	FontTenSecond_->SetSize(40.0f);
	FontTenSecond_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	FontTenSecond_->SetScreenPostion({ 1500.0f + PivotX, 75.0f + PivotY });

	FontOneSecond_ = CreateComponent<GameEngineFontRenderer>();
	FontOneSecond_->ChangeCamera(CAMERAORDER::UICAMERA);
	FontOneSecond_->SetText("0", FONT_TITAN_ONE);
	FontOneSecond_->SetSize(40.0f);
	FontOneSecond_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	FontOneSecond_->SetScreenPostion({ 1530.0f + PivotX, 75.0f + PivotY });
}

void TimerActor::Update(float _DeltaTime)
{
	Time_ -= _DeltaTime;

	OneMinute_ = static_cast<int>(Time_) / 60;
	OneSecond_ = static_cast<int>(Time_) % 10;
	TenSecond_ = static_cast<int>(Time_) % 60 / 10;

	FontOneMinute_->SetText(std::to_string(OneMinute_), FONT_TITAN_ONE);
	FontTenSecond_->SetText(std::to_string(TenSecond_), FONT_TITAN_ONE);
	FontOneSecond_->SetText(std::to_string(OneSecond_), FONT_TITAN_ONE);

	if (Time_ <= 0.0f)
	{
		Time_ = 0.0f;
	}
}

void TimerActor::LevelStartEvent()
{
	OneSecond_ = 0;
	TenSecond_ = 0;
	OneMinute_ = 2;
	Time_ = 120.0f;
}
