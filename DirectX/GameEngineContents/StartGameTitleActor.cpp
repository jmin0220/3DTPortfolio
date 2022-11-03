#include "PreCompile.h"
#include "StartGameTitleActor.h"

StartGameTitleActor::StartGameTitleActor() 
	:Swap_(false)
	,IsFirstAniEnd_(false)
{
}

StartGameTitleActor::~StartGameTitleActor() 
{
}

void StartGameTitleActor::Start()
{
	BlackTitle_ = CreateComponent<GameEngineUIRenderer>();
	BlackTitle_->GetTransform().SetWorldScale({ 0.0f, 109.0f });
	BlackTitle_->GetTransform().SetWorldPosition({ -700.0f, -350.0f });
	BlackTitle_->SetPivot(PIVOTMODE::LEFT);
	BlackTitle_->SetTexture("title-tab-B.png");

	WhiteTitle_ = CreateComponent<GameEngineUIRenderer>();
	WhiteTitle_->GetTransform().SetWorldScale({ 0.0f, 109.0f });
	WhiteTitle_->GetTransform().SetWorldPosition({ -800.0f, -350.0f });
	WhiteTitle_->SetPivot(PIVOTMODE::LEFT);
	WhiteTitle_->SetTexture("title-tab-W.png");

	GreenTitle_ = CreateComponent<GameEngineUIRenderer>();
	GreenTitle_->GetTransform().SetWorldScale({ 0.0f, 109.0f });
	GreenTitle_->GetTransform().SetWorldPosition({ -800.0f, -350.0f });
	GreenTitle_->SetPivot(PIVOTMODE::LEFT);
	GreenTitle_->SetTexture("title-tab.png");

	GameIcon_ = CreateComponent<GameEngineUIRenderer>();
	GameIcon_->GetTransform().SetWorldScale({ 77.0f, 61.0f });
	GameIcon_->GetTransform().SetWorldPosition({ 150.0f, -350.0f });
	GameIcon_->SetPivot(PIVOTMODE::CENTER);
	GameIcon_->SetTexture("UI_Medal_Icon_DoorDash.png");
	GameIcon_->Off();

	TitleFont_ = CreateComponent<GameEngineFontRenderer>();
	TitleFont_->SetSize(40.0f);
	TitleFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	TitleFont_->SetScreenPostion({ 150.0f, 770 });
	TitleFont_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	TitleFont_->Off();

	SubTitleFont_ = CreateComponent<GameEngineFontRenderer>();
	SubTitleFont_->SetSize(20.0f);
	SubTitleFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	SubTitleFont_->SetScreenPostion({ 700.0f, 785 });
	SubTitleFont_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	SubTitleFont_->Off();
}

void StartGameTitleActor::Update(float _DeltaTime)
{
	SetTitleText("게임 제목", "부가설명" , "UI_Medal_Icon_DoorDash.png");
	TitlebarAnimation();
}

void StartGameTitleActor::LevelStartEvent()
{
	GreenTitle_->GetTransform().SetWorldScale({ 0.0f, 109.0f });
	WhiteTitle_->GetTransform().SetWorldScale({ 0.0f, 109.0f });
	WhiteTitle_->GetTransform().SetWorldPosition({ -800.0f, -350.0f });
	BlackTitle_->GetTransform().SetWorldScale({ 0.0f, 109.0f });
	Swap_ = false;
	IsFirstAniEnd_ = false;
	IsSecondAniEnd_ = false;
	TitleFont_->Off();
	SubTitleFont_->Off();
	GameIcon_->Off();
}

void StartGameTitleActor::TitlebarAnimation()
{
	{	//뿅~커졌다가
		if (Swap_ == false)
		{
			float4 f4CurrentScale = GreenTitle_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 400.0f,130.0f };
			GreenTitle_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
			if (GreenTitle_->GetTransform().GetWorldScale().x >= f4DestinationScale.x - 1.0f)
			{
				//제 사이즈 되려면 딜레이가 너무 커서 1정도 오차 줌
				Swap_ = true;
			}
		}
	}

	{	//제자리로 줄어들기
		if (Swap_ == true)
		{
			TitleFont_->On();
			float4 f4CurrentScale = GreenTitle_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 350.0f, 109.0f };
			GreenTitle_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
			
			if (GreenTitle_->GetTransform().GetWorldScale().x <= 352.0f)
			{
				IsFirstAniEnd_ = true;
			}
		}
	}

	{
		//그 다음 하얀색 타이틀바 삐쭉 등장
		if (IsFirstAniEnd_ == true)
		{
			WhiteTitle_->GetTransform().SetWorldScale({ 350.0f, 109.0f });

			float4 f4CurrentPosition = WhiteTitle_->GetTransform().GetWorldPosition();
			float4 f4DestinationPosition = { -770.0f, -350.0f };

			WhiteTitle_->GetTransform().SetWorldPosition({ float4::Lerp(f4CurrentPosition, f4DestinationPosition, GameEngineTime::GetDeltaTime() * 15.f)});

			if (WhiteTitle_->GetTransform().GetWorldPosition().x >= -772.0f)
			{
				IsSecondAniEnd_ = true;
			}
		}
	}

	{
		//마지막 게임 설명바 등장
		if (IsSecondAniEnd_ == true)
		{
			float4 f4CurrentScale = BlackTitle_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 1000.0f, 109.0f };
			BlackTitle_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
			
			if (BlackTitle_->GetTransform().GetWorldScale().x >= 998.0f)
			{
				SubTitleFont_->On();
				GameIcon_->On();

			}
		}
	}
}