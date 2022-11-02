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
		Logo = CreateComponent<GameEngineTextureRenderer>();
		Logo->GetTransform().SetWorldScale({ 0, 0 });
		Logo->GetTransform().SetWorldPosition({ 0, 70 });
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

void TitleActor::LevelStartEvent()
{
	Logo->GetTransform().SetWorldScale({ 0,0 });
	Swap = false;
	FontSize = 0.0f;
	Font->Off();
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
		if (FontSize < 30.0f && Swap==true)
		{
			Font->On();
			FontSize += GameEngineTime::GetDeltaTime() * 70.0f;
			Font->SetSize(FontSize);
		}
	}
}
