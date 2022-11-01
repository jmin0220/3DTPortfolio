#include "PreCompile.h"
#include "TitleActor.h"

TitleActor::TitleActor() 
	:Swap(false)
{
}

TitleActor::~TitleActor() 
{
}

void TitleActor::Start()
{
	{
		Renderer2 = CreateComponent<GameEngineTextureRenderer>();
		Renderer2->GetTransform().SetLocalScale({ 1600, 900, 1 });
		Renderer2->SetPivot(PIVOTMODE::CENTER);
		Renderer2->GetTransform().SetLocalPosition({ -18,-82 });
				
		Renderer2->SetTexture("LobbySketch.png");
		Renderer2->Off();
	}

	{
		Logo = CreateComponent<GameEngineTextureRenderer>();
		Logo->GetTransform().SetLocalScale({ 8.36, 5.72, 1 });
		Logo->SetPivot(PIVOTMODE::CENTER);

		Logo->SetTexture("Logo.png");
	}

	{
		Font = CreateComponent<GameEngineFontRenderer>();
		Font->ChangeCamera(CAMERAORDER::UICAMERA);
		Font->SetLeftAndRightSort(LeftAndRightSort::CENTER);
		Font->SetScreenPostion({ 825,700 });
		Font->SetSize(0.0f);
		Font->SetText("시작!", "Noto Sans CJK SC");
		Font->Off();
	}
}

void TitleActor::Update(float _DeltaTime)
{
	LogoSizeAnimation();
	FontSizeAnimation();
}

void TitleActor::LogoSizeAnimation()
{
	{	//뿅~커졌다가
		if (Swap == false)
		{
			float4 f4CurrentScale = Logo->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 900,600 };
			Logo->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
			if (Logo->GetTransform().GetWorldScale().x >= f4DestinationScale.x - 1.0f)
			{
				//제 사이즈 되려면 딜레이가 너무 커서 1정도 오차 줌
				Swap = true;
			}
		}
	}

	{	//제자리로 줄어들기
		if (Swap == true)
		{
			float4 f4CurrentScale = Logo->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 836,536 };
			Logo->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
		}
	}
}

void TitleActor::FontSizeAnimation()
{
	{
		//폰트 사이즈가 30이 될때까지 0에서 점점 커진다

		if (FontSize < 30.0f && Swap==true)
		{
			Font->On();
			FontSize += GameEngineTime::GetDeltaTime() * 70.0f;
			Font->SetSize(FontSize);
		}
	}
}
