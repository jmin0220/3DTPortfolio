#include "PreCompile.h"
#include "GameSuccess.h"
#include "RoundEnd.h"

GameSuccess::GameSuccess()
	:IsPop_(false)
	, PopUpTime_(0.0f)
	, IsOut_(false)
{
}

GameSuccess::~GameSuccess() 
{
}

void GameSuccess::Start()
{
	SlicePos_ = float4(1, 0, 0, 0);
	SetRenderer_ = CreateComponent<GameEngineUIRenderer>();
	//SetRenderer_->GetRenderUnit().SetPipeLine("TextureLoop");
	SetRenderer_->GetRenderUnit().SetPipeLine("RtoLSlice");

	SetRenderer_->GetTransform().SetWorldScale({ 2048.0f, 336.0f });
	SetRenderer_->GetTransform().SetWorldPosition({ 0.0f, 0.0f });
	SetRenderer_->SetPivot(PIVOTMODE::LEFT);
	SetRenderer_->SetTexture("round-over-border-set.png");

	SetRenderer_->GetRenderUnit().EngineShaderResourcesSetting(SetRenderer_);

	if (true == SetRenderer_->GetRenderUnit().ShaderResources.IsConstantBuffer("SliceData"))
	{
		SetRenderer_->GetRenderUnit().ShaderResources.SetConstantBufferLink("SliceData", SlicePos_);
	}


	CrownRenderer_ = CreateComponent<GameEngineUIRenderer>();
	CrownRenderer_->GetTransform().SetWorldScale({ 2048.0f, 336.0f });
	CrownRenderer_->GetTransform().SetWorldPosition({ 0.0f, 3.0f });
	CrownRenderer_->SetPivot(PIVOTMODE::LEFT);
	CrownRenderer_->SetTexture("round-over-white.png");

	CrownRenderer_->GetRenderUnit().SetPipeLine("TextureLoop");
	CrownRenderer_->GetRenderUnit().EngineShaderResourcesSetting(CrownRenderer_);
	CrownRenderer_->GetRenderUnit().ShaderResources.SetTexture("Tex", "crown-pattern-blue.png");
	if (true == CrownRenderer_->GetRenderUnit().ShaderResources.IsConstantBuffer("SliceData"))
	{
		CrownRenderer_->GetRenderUnit().ShaderResources.SetConstantBufferLink("SliceData", SlicePos_);
	}
	
	CrownRenderer_->GetRenderUnit().ShaderResources.SetTexture("Mask", "round-over-white.png");
	

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
	SlicePos_ = float4(1, 0, 0, 0);

	Text_->GetPixelData().MulColor.a = 0.0f;
	IsPop_ = false;
	IsOut_ = false;
	PopUpTime_ = 0.0f;

	Text_->On();
	Text_->GetTransform().SetWorldScale({ 300.5f, 157.5f });
	Text_->GetTransform().SetWorldRotation({ 0.0f, 0.0f, 3.0f });

	SetRenderer_->GetTransform().SetWorldScale({ 2048.0f, 336.0f });
	CrownRenderer_->GetTransform().SetWorldScale({ 2048.0f, 336.0f });
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
	//일정 시간 후 Circle렌더러들 X가 0으로 Lerp되서 사라지고 글자도 0으로 줄어들어 사라진다
	//SetRenderer_->GetPixelData().Slice;????
	UIOff();

	if (IsOut_ == true)
	{
		SlicePos_.x -= 0.1f;
	}

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
		//왼쪽 큰 원
		float4 f4CurrentScale = SideCircle1_->GetTransform().GetWorldScale();
		float4 f4DestinationScale = { 0.0f,141.0f };

		SideCircle1_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 3.f) });

		//오른쪽 큰 원
		float4 f4CurrentScale2 = SideCircle3_->GetTransform().GetWorldScale();
		float4 f4DestinationScale2 = { 0.0f,140.0f };

		SideCircle3_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale2, f4DestinationScale2, GameEngineTime::GetDeltaTime() * 3.f) });
	}

	if (SideCircle1_->GetTransform().GetWorldScale().x <= 300.0f)
	{
		//왼쪽 작은원
		float4 f4CurrentScale = SideCircle2_->GetTransform().GetWorldScale();
		float4 f4DestinationScale = { 0.0f,92.0f };

		SideCircle2_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 4.f) });

		//오른쪽 작은 원
		float4 f4CurrentScale2 = SideCircle4_->GetTransform().GetWorldScale();
		float4 f4DestinationScale2 = { 0.0f,70.0f };

		SideCircle4_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale2, f4DestinationScale2, GameEngineTime::GetDeltaTime() * 4.f) });

		IsOut_ = true;
		//글자
		float4 f4CurrentScale4 = Text_->GetTransform().GetWorldScale();
		float4 f4DestinationScale4 = { 0.0f, 0.0f };

		Text_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale4, f4DestinationScale4, GameEngineTime::GetDeltaTime() * 6.f) });
	}
}

void GameSuccess::Reset()
{
	SlicePos_ = float4(1, 0, 0, 0);

	Text_->GetPixelData().MulColor.a = 0.0f;
	IsPop_ = false;
	IsOut_ = false;
	PopUpTime_ = 0.0f;

	Text_->On();

	SetRenderer_->GetTransform().SetWorldScale({ 2048.0f, 336.0f });
	CrownRenderer_->GetTransform().SetWorldScale({ 2048.0f, 336.0f });
	SideCircle1_->GetTransform().SetWorldScale({ 459.0f, 141.0f });
	SideCircle2_->GetTransform().SetWorldScale({ 300.0f, 92.0f });
	SideCircle3_->GetTransform().SetWorldScale({ 400.0f, 140.0f });
	SideCircle4_->GetTransform().SetWorldScale({ 400.0f, 70.0f });
	Text_->GetTransform().SetWorldScale({ 300.5f, 157.5f });
	Text_->GetTransform().SetWorldRotation({ 0.0f, 0.0f, 3.0f });
}