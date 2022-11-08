#include "PreCompile.h"
#include "GameSuccess.h"

GameSuccess::GameSuccess() 
	:IsPop_(false)
	,PopUpTime_(0.0f)
	,IsOut_(false)
{
}

GameSuccess::~GameSuccess() 
{
}

void GameSuccess::Start()
{
	SetRenderer_ = CreateComponent<GameEngineUIRenderer>();
	SetRenderer_->GetTransform().SetWorldScale({ 2048.0f, 336.0f });
	SetRenderer_->GetTransform().SetWorldPosition({ -1024.0f, 0.0f });
	SetRenderer_->SetPivot(PIVOTMODE::LEFT);
	SetRenderer_->SetTexture("round-over-set.png");

	SideCircle1_ = CreateComponent<GameEngineUIRenderer>();
	SideCircle1_->GetTransform().SetWorldScale({ 459.0f, 141.0f });
	SideCircle1_->GetTransform().SetWorldPosition({ -1030.0f, 100.0f });
	SideCircle1_->SetPivot(PIVOTMODE::LEFT);
	SideCircle1_->SetTexture("large-pill-grey.png");

	SideCircle2_ = CreateComponent<GameEngineUIRenderer>();
	SideCircle2_->GetTransform().SetWorldScale({ 300.0f, 92.0f });
	SideCircle2_->GetTransform().SetWorldPosition({ -950.0f, 60.0f });
	SideCircle2_->SetPivot(PIVOTMODE::LEFT);
	SideCircle2_->SetTexture("large-pill-pink.png");

	SideCircle3_ = CreateComponent<GameEngineUIRenderer>();
	SideCircle3_->GetTransform().SetWorldScale({ 400.0f, 140.0f });
	SideCircle3_->GetTransform().SetWorldPosition({ 900.0f, -80.0f });
	SideCircle3_->SetPivot(PIVOTMODE::RIGHT);
	SideCircle3_->SetTexture("large-pill-pink.png");

	SideCircle4_ = CreateComponent<GameEngineUIRenderer>();
	SideCircle4_->GetTransform().SetWorldScale({ 400.0f, 70.0f });
	SideCircle4_->GetTransform().SetWorldPosition({ 1000.0f, -130.0f });
	SideCircle4_->SetPivot(PIVOTMODE::RIGHT);
	SideCircle4_->SetTexture("large-pill-grey.png");

	Text_ = CreateComponent<GameEngineUIRenderer>();
	Text_->GetTransform().SetWorldScale({ 300.5f, 157.5f });
	Text_->GetTransform().SetWorldPosition({ 0.0f, 20.0f });
	Text_->GetTransform().SetWorldRotation({ 0.0f, 0.0f, 3.0f });
	Text_->SetPivot(PIVOTMODE::CENTER);
	Text_->SetTexture("SungGong.png");
	Text_->GetPixelData().MulColor.a = 0.0f;
}

void GameSuccess::LevelStartEvent()
{
	Text_->GetPixelData().MulColor.a = 0.0f;
	IsPop_ = false;
	IsOut_ = false;
	PopUpTime_ = 0.0f;

	SetRenderer_->GetTransform().SetWorldScale({ 2048.0f, 336.0f });
	SideCircle1_->GetTransform().SetWorldScale({ 459.0f, 141.0f });
	SideCircle2_->GetTransform().SetWorldScale({ 300.0f, 92.0f });
	SideCircle3_->GetTransform().SetWorldScale({ 400.0f, 140.0f });
	SideCircle4_->GetTransform().SetWorldScale({ 400.0f, 70.0f });
}

void GameSuccess::Update(float _DeltaTime)
{
	PopUpTime_ += _DeltaTime;
	AlphaSet();
	TextRendererPop();
	//���� �ð� �� Circle�������� X�� 0���� Lerp�Ǽ� ������� ���ڵ� 0���� �پ��� �������
	//SetRenderer_->GetPixelData().Slice;????
	UIOff();
}

void GameSuccess::AlphaSet()
{
	if (Text_->GetPixelData().MulColor.a <= 1.0f)
	{
		Text_->GetPixelData().MulColor.a += GameEngineTime::GetDeltaTime() * 8.0f;
	}
}

void GameSuccess::TextRendererPop()
{
	if (Text_->GetPixelData().MulColor.a >= 1.0f && IsPop_==false)
	{
		float4 f4CurrentScale = Text_->GetTransform().GetWorldScale();
		float4 f4DestinationScale = { 400.5f, 257.5f };
		Text_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });
		IsPop_ = true;
	}

	if (IsPop_ == true && IsOut_ == false)
	{
		float4 f4CurrentScale = Text_->GetTransform().GetWorldScale();
		float4 f4DestinationScale = { 300.5f, 157.5f };
		Text_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });
	}
}

void GameSuccess::UIOff()
{
	if (PopUpTime_ > 3.0f)
	{
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

		IsOut_ = true;
		//����
		float4 f4CurrentScale4 = Text_->GetTransform().GetWorldScale();
		float4 f4DestinationScale4 = { 0.0f, 0.0f };

		Text_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale4, f4DestinationScale4, GameEngineTime::GetDeltaTime() * 6.f) });
	}
}