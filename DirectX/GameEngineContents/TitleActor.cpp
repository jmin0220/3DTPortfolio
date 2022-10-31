#include "PreCompile.h"
#include "TitleActor.h"

TitleActor::TitleActor() 
	:FontSize(0.0f)
	,XImageSize(8.36f)
	,YImageSize(5.72f)
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
		Font->SetSize(FontSize);
		Font->SetText("시작!", "Noto Sans CJK SC");
	}
}

void TitleActor::Update(float _DeltaTime)
{
	LogoSizeAnimation();
	FontSizeAnimation();
}

void TitleActor::LogoSizeAnimation()
{
	if (Logo->IsUpdate() == true && Logo->GetTransform().GetLocalScale().x <= 836)
	{
		XImageSize += GameEngineTime::GetDeltaTime() * 3000.0f;
		YImageSize += GameEngineTime::GetDeltaTime() * 2000.0f;
		Logo->GetTransform().SetLocalScale({XImageSize,  YImageSize });
	}
}

void TitleActor::FontSizeAnimation()
{
	{
		//폰트 사이즈가 30이 될때까지 0에서 점점 커진다

		if (Font->IsUpdate() == true && FontSize < 30.0f)
		{
			Font->On();
			FontSize += GameEngineTime::GetDeltaTime() * 70.0f;
			Font->SetSize(FontSize);
		}
		
	}
}
