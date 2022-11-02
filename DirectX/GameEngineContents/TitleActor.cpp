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
		Font->SetText("����!", "Noto Sans CJK SC");
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
	{	//��~Ŀ���ٰ�
		if (Swap == false)
		{
			float4 f4CurrentScale = Logo->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 900,600 };
			Logo->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
			if (Logo->GetTransform().GetWorldScale().x >= f4DestinationScale.x - 1.0f)
			{
				//�� ������ �Ƿ��� �����̰� �ʹ� Ŀ�� 1���� ���� ��
				Swap = true;
			}
		}
	}

	{	//���ڸ��� �پ���
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
