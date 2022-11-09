#include "PreCompile.h"
#include "RoundEnd.h"

RoundEnd::RoundEnd() 
	:Pop_(false)
	,PopUpTime_(0.0f)
	,IsOut_(false)
{
}

RoundEnd::~RoundEnd() 
{
}

void RoundEnd::Start()
{
	SetRenderer_ = CreateComponent<GameEngineUIRenderer>();
	SetRenderer_->GetTransform().SetWorldScale({2048, 336});
	SetRenderer_->SetTexture("round-over-set.png");
	SetRenderer_->SetPivot(PIVOTMODE::LEFT);
	SetRenderer_->GetTransform().SetWorldPosition({-1024.0f,0});
	SetRenderer_->GetPixelData().MulColor.a = 0.5f;

	SideCircle1_ = CreateComponent<GameEngineUIRenderer>();
	SideCircle1_->GetTransform().SetWorldScale({ 459.0f, 141.0f });
	SideCircle1_->GetTransform().SetWorldPosition({ -1030.0f, 100.0f });
	SideCircle1_->GetTransform().SetWorldRotation({ 0.0f, 0.0f, 3.0f });
	SideCircle1_->SetPivot(PIVOTMODE::LEFT);
	SideCircle1_->SetTexture("large-pill-pink.png");
	SideCircle1_->GetPixelData().MulColor.a = 0.5f;

	SideCircle2_ = CreateComponent<GameEngineUIRenderer>();
	SideCircle2_->GetTransform().SetWorldScale({ 300.0f, 141.0f });
	SideCircle2_->GetTransform().SetWorldPosition({ -850.0f, 60.0f });
	SideCircle2_->SetPivot(PIVOTMODE::LEFT);
	SideCircle2_->SetTexture("large-pill-blue.png");
	SideCircle2_->GetPixelData().MulColor.a = 0.5f;

	SideCircle3_ = CreateComponent<GameEngineUIRenderer>();
	SideCircle3_->GetTransform().SetWorldScale({ 400.0f, 140.0f });
	SideCircle3_->GetTransform().SetWorldPosition({ 900.0f, -80.0f });
	SideCircle3_->SetPivot(PIVOTMODE::RIGHT);
	SideCircle3_->SetTexture("large-pill-blue.png");
	SideCircle3_->GetPixelData().MulColor.a = 0.5f;

	SideCircle4_ = CreateComponent<GameEngineUIRenderer>();
	SideCircle4_->GetTransform().SetWorldScale({ 400.0f, 70.0f });
	SideCircle4_->GetTransform().SetWorldPosition({ 850, -130.0f });
	SideCircle4_->SetPivot(PIVOTMODE::RIGHT);
	SideCircle4_->SetTexture("large-pill-pink.png");
	SideCircle4_->GetPixelData().MulColor.a = 0.5f;

	Text_ = CreateComponent<GameEngineUIRenderer>();
	Text_->GetTransform().SetWorldScale({ 383.0f, 324.0f });
	Text_->GetTransform().SetWorldPosition({ 0.0f, 20.0f });
	Text_->GetTransform().SetWorldRotation({ 0.0f, 0.0f, 3.0f });
	Text_->SetPivot(PIVOTMODE::CENTER);
	Text_->SetTexture("RoundEnd.png");
	Text_->GetPixelData().MulColor.a = 0.5f;
}

void RoundEnd::Update(float _DeltaTime)
{
	PopUpTime_ += _DeltaTime;
	StartAnimation();
	EndAnimation();
}

void RoundEnd::LevelStartEvent()
{
	SetRenderer_->GetTransform().SetWorldScale({ 0.0f, 336.0f });
	SideCircle1_->GetTransform().SetWorldScale({ 0.0f, 141.0f });
	SideCircle2_->GetTransform().SetWorldScale({ 0.0f, 92.0f });
	SideCircle3_->GetTransform().SetWorldScale({ 0.0f, 140.0f });
	SideCircle4_->GetTransform().SetWorldScale({ 0.0f, 70.0f });

	Text_->GetTransform().SetWorldScale({ 0.0f, 0.0f });

	Pop_ = false;
	IsOut_ = false;
	PopUpTime_ = 0.0f;
}

void RoundEnd::StartAnimation()
{
	{	//��~Ŀ���ٰ�
		if (Pop_ == false)
		{
			float4 f4CurrentScale = Text_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 483.0f, 424.0f };
			Text_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 7.f) });

			float4 f4CurrentScale2 = SetRenderer_->GetTransform().GetWorldScale();
			float4 f4DestinationScale2 = { 2048.0f, 336.0f };
			SetRenderer_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale2, f4DestinationScale2, GameEngineTime::GetDeltaTime() * 15.f) });

			//������ ū ��
			float4 f4CurrentScale3 = SideCircle1_->GetTransform().GetWorldScale();
			float4 f4DestinationScale3 = { 459.0f,141.0f };

			SideCircle1_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale3, f4DestinationScale3, GameEngineTime::GetDeltaTime() * 10.f) });

			float4 f4CurrentScale4 = SideCircle3_->GetTransform().GetWorldScale();
			float4 f4DestinationScale4 = { 400.0f,140.0f };

			SideCircle3_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale4, f4DestinationScale4, GameEngineTime::GetDeltaTime() * 10.f) });

			if (SideCircle1_->GetTransform().GetWorldScale().x <= 300.0f)
			{
				//���� ������
				float4 f4CurrentScale = SideCircle2_->GetTransform().GetWorldScale();
				float4 f4DestinationScale = { 300.0f, 92.0f };

				SideCircle2_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });

				//������ ���� ��
				float4 f4CurrentScale2 = SideCircle4_->GetTransform().GetWorldScale();
				float4 f4DestinationScale2 = { 400.0f, 70.0f };

				SideCircle4_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale2, f4DestinationScale2, GameEngineTime::GetDeltaTime() * 10.f) });

			}
			if (Text_->GetTransform().GetWorldScale().x >= f4DestinationScale.x - 5.0f)
			{
				//�� ������ �Ƿ��� �����̰� �ʹ� Ŀ�� 1���� ���� ��
				Pop_ = true;
			}
		}
	}

	{	//���ڸ��� �پ���
		if (Pop_ == true && IsOut_ == false)
		{
			float4 f4CurrentScale = Text_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 383.0f,324.0f };
			Text_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
		}
	}
}

void RoundEnd::EndAnimation()
{
	if (PopUpTime_ > 3.0f)
	{
		IsOut_ = true;

		//���� ū ��
		float4 f4CurrentScale = SideCircle1_->GetTransform().GetWorldScale();
		float4 f4DestinationScale = { 0.0f,141.0f };

		SideCircle1_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 3.f) });

		//������ ū ��
		float4 f4CurrentScale2 = SideCircle3_->GetTransform().GetWorldScale();
		float4 f4DestinationScale2 = { 0.0f,140.0f };

		SideCircle3_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale2, f4DestinationScale2, GameEngineTime::GetDeltaTime() * 3.f) });
	}

	if (SideCircle1_->GetTransform().GetWorldScale().x <= 300.0f)
	{
		//���� ������
		float4 f4CurrentScale = SideCircle2_->GetTransform().GetWorldScale();
		float4 f4DestinationScale = { 0.0f,92.0f };

		SideCircle2_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 4.f) });

		//������ ���� ��
		float4 f4CurrentScale2 = SideCircle4_->GetTransform().GetWorldScale();
		float4 f4DestinationScale2 = { 0.0f,70.0f };

		SideCircle4_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale2, f4DestinationScale2, GameEngineTime::GetDeltaTime() * 4.f) });

		//����
		float4 f4CurrentScale3 = SetRenderer_->GetTransform().GetWorldScale();
		float4 f4DestinationScale3 = { 0.0f, 336.0f };

		SetRenderer_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale3, f4DestinationScale3, GameEngineTime::GetDeltaTime() * 10.f) });


		//����
		float4 f4CurrentScale4 = Text_->GetTransform().GetWorldScale();
		float4 f4DestinationScale4 = { 0.0f, 0.0f };

		Text_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale4, f4DestinationScale4, GameEngineTime::GetDeltaTime() * 15.f) });
	}
}