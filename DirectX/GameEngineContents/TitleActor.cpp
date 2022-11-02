#include "PreCompile.h"
#include "TitleActor.h"

TitleActor::TitleActor() 
	:Swap_(false)
{
}

TitleActor::~TitleActor() 
{
}

void TitleActor::Start()
{
	{
		Logo_ = CreateComponent<GameEngineTextureRenderer>();
		Logo_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
		Logo_->GetTransform().SetWorldPosition({ 0.0f, 70.0f });
		Logo_->SetPivot(PIVOTMODE::CENTER);

		Logo_->SetTexture("Logo.png");
	}

	{
		Font_ = CreateComponent<GameEngineFontRenderer>();
		Font_->ChangeCamera(CAMERAORDER::UICAMERA);
		Font_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
		Font_->SetScreenPostion({ 825.0f,700.0f });
		Font_->SetSize(0.0f);
		Font_->SetText("시작!", "Noto Sans CJK SC");
		Font_->Off();
	}
}

void TitleActor::Update(float _DeltaTime)
{
	LogoSizeAnimation();
	FontSizeAnimation();
}

void TitleActor::LevelStartEvent()
{
	Logo_->GetTransform().SetWorldScale({ 0.0f,0.0f });
	Swap_ = false;
	FontSize_ = 0.0f;
	Font_->Off();
}

void TitleActor::LogoSizeAnimation()
{
	{	//뿅~커졌다가
		if (Swap_ == false)
		{
			float4 f4CurrentScale = Logo_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 900.0f,600.0f };
			Logo_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
			if (Logo_->GetTransform().GetWorldScale().x >= f4DestinationScale.x - 1.0f)
			{
				//제 사이즈 되려면 딜레이가 너무 커서 1정도 오차 줌
				Swap_ = true;
			}
		}
	}

	{	//제자리로 줄어들기
		if (Swap_ == true)
		{
			float4 f4CurrentScale = Logo_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 836.0f,536.0f };
			Logo_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
		}
	}
}

void TitleActor::FontSizeAnimation()
{
	{
		if (FontSize_ < 30.0f && Swap_==true)
		{
			Font_->On();
			FontSize_ += GameEngineTime::GetDeltaTime() * 70.0f;
			Font_->SetSize(FontSize_);
		}
	}
}
