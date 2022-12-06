#include "PreCompile.h"
#include "TitleActor.h"
#include <conio.h>

TitleActor::TitleActor() 
	:Swap_(false)
{
}

TitleActor::~TitleActor() 
{
}

void TitleActor::Start()
{
	SlicePos_ = float4(1, 0, 0, 0);


	{
		BG_ = CreateComponent<GameEngineTextureRenderer>();
		BG_->GetTransform().SetWorldScale({ 1600.0f, 900.0f });
		BG_->GetTransform().SetWorldPosition({ 0.0f, 0.0f });
		BG_->SetPivot(PIVOTMODE::CENTER);
		
		BG_->SetTexture("LogoBG.png");
	}

	{
		Pattern_ = CreateComponent<GameEngineTextureRenderer>();
		Pattern_->GetTransform().SetWorldScale({ 1600.0f, 900.0f });
		Pattern_->GetTransform().SetWorldPosition({ 0.0f, 0.0f });
		Pattern_->SetPivot(PIVOTMODE::CENTER);

		Pattern_->SetTexture("LogoBG.png");

		Pattern_->GetRenderUnit()->SetMaterial("TextureLoop");
		Pattern_->GetRenderUnit()->EngineShaderResourcesSetting(Pattern_);
		Pattern_->GetRenderUnit()->ShaderResources.SetTexture("Tex", "LogoPattern.png");

		if (true == Pattern_->GetRenderUnit()->ShaderResources.IsConstantBuffer("SliceData"))
		{
			Pattern_->GetRenderUnit()->ShaderResources.SetConstantBufferLink("SliceData", SlicePos_);
		}

		Pattern_->GetRenderUnit()->ShaderResources.SetTexture("Mask", "LogoBG.png");

	}

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
	
	LevelChangeEvent();
}

void TitleActor::LevelStartEvent()
{
	Logo_->GetTransform().SetWorldScale({ 0.0f,0.0f });
	Swap_ = false;
	EndStart_ = false;
	FontEndStart_ = false;
	IsLevelChange_ = false;
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
		if (Swap_ == true && EndStart_ == false)
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
		if (FontSize_ < 30.0f && Swap_==true && EndStart_ == false)
		{
			Font_->On();
			FontSize_ += GameEngineTime::GetDeltaTime() * 50.0f;
			Font_->SetSize(FontSize_);
		}

		if (GameEngineInput::GetInst()->IsDown(KEY_ENTER))
		{
			//나중에 이걸 아무키나 누르면 Endstart시작으로
			//_getch();??안댐..
			EndStart_ = true;
		}

	}
}

void TitleActor::LevelChangeEvent()
{
	if (EndStart_ == true)
	{
		//아무키나 입력하면 로고가 사라지고 레벨체인지
		{
			float4 f4CurrentScale = Logo_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 0.0f,0.0f };
			Logo_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
		}
	}

	if (Logo_->GetTransform().GetWorldScale().x <= 1.0f)
	{
		FontEndStart_ = true;
	}

	if (EndStart_ == true && FontEndStart_ == true)
	{
		FontSize_ -= GameEngineTime::GetDeltaTime() * 1000.0f;
		Font_->SetSize(FontSize_);

		if (FontSize_ <= 0.0f)
		{
			Font_->SetSize(0.0f);
			Font_->Off();
			IsLevelChange_ = true;
		}
	}
}