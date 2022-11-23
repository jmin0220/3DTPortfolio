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
	PopUpTime_ = 0.0f;

	SlicePos_ = float4(0, 0, 0, 0);

	SetRenderer_ = CreateComponent<GameEngineUIRenderer>();
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
	CrownRenderer_->GetRenderUnit().ShaderResources.SetTexture("Tex", "crown-pattern-black.png");
	if (true == CrownRenderer_->GetRenderUnit().ShaderResources.IsConstantBuffer("SliceData"))
	{
		CrownRenderer_->GetRenderUnit().ShaderResources.SetConstantBufferLink("SliceData", SlicePos_);
	}

	CrownRenderer_->GetRenderUnit().ShaderResources.SetTexture("Mask", "round-over-white.png");

	SideCircle1_ = CreateComponent<GameEngineUIRenderer>();
	//SideCircle1_->GetTransform().SetWorldScale({ 459.0f, 141.0f });
	SideCircle1_->GetTransform().SetWorldScale({ 0.0f, 141.0f });
	SideCircle1_->GetTransform().SetWorldPosition({ -1030.0f, 100.0f });
	SideCircle1_->GetTransform().SetWorldRotation({ 0.0f, 0.0f, 3.0f });
	SideCircle1_->SetPivot(PIVOTMODE::LEFT);
	SideCircle1_->SetTexture("large-pill-pink.png");
	//SideCircle1_->GetPixelData().MulColor.a = 0.5f;

	SideCircle2_ = CreateComponent<GameEngineUIRenderer>();
	//SideCircle2_->GetTransform().SetWorldScale({ 300.0f, 141.0f });
	SideCircle2_->GetTransform().SetWorldScale({ 0.0f, 141.0f });
	SideCircle2_->GetTransform().SetWorldPosition({ -850.0f, 60.0f });
	SideCircle2_->SetPivot(PIVOTMODE::LEFT);
	SideCircle2_->SetTexture("large-pill-blue.png");
	//SideCircle2_->GetPixelData().MulColor.a = 0.5f;

	SideCircle3_ = CreateComponent<GameEngineUIRenderer>();
	//SideCircle3_->GetTransform().SetWorldScale({ 400.0f, 140.0f });
	SideCircle3_->GetTransform().SetWorldScale({ 0.0f, 140.0f });
	SideCircle3_->GetTransform().SetWorldPosition({ 900.0f, -80.0f });
	SideCircle3_->SetPivot(PIVOTMODE::RIGHT);
	SideCircle3_->SetTexture("large-pill-blue.png");
	//SideCircle3_->GetPixelData().MulColor.a = 0.5f;

	SideCircle4_ = CreateComponent<GameEngineUIRenderer>();
	//SideCircle4_->GetTransform().SetWorldScale({ 400.0f, 70.0f });
	SideCircle4_->GetTransform().SetWorldScale({ 0.0f, 70.0f });
	SideCircle4_->GetTransform().SetWorldPosition({ 850, -130.0f });
	SideCircle4_->SetPivot(PIVOTMODE::RIGHT);
	SideCircle4_->SetTexture("large-pill-pink.png");
	//SideCircle4_->GetPixelData().MulColor.a = 0.5f;

	Text_ = CreateComponent<GameEngineUIRenderer>();
	//Text_->GetTransform().SetWorldScale({ 383.0f, 324.0f });
	Text_->GetTransform().SetWorldScale({ 0.0f, 324.0f });
	Text_->GetTransform().SetWorldPosition({ 0.0f, 20.0f });
	Text_->GetTransform().SetWorldRotation({ 0.0f, 0.0f, 3.0f });
	Text_->SetPivot(PIVOTMODE::CENTER);
	Text_->SetTexture("RoundEnd.png");
	//Text_->GetPixelData().MulColor.a = 0.5f;
}

void RoundEnd::Update(float _DeltaTime)
{
	PopUpTime_ += _DeltaTime;
	StartAnimation();
	EndAnimation();

	if (IsOut_ == true)
	{
		SlicePos_.x -= 0.1f;
	}

	if (IsOut_ ==false && SlicePos_.x <= 1.0f)
	{
		SlicePos_.x += _DeltaTime * 5.0f;
	}
}

void RoundEnd::LevelStartEvent()
{
	SlicePos_ = float4(0, 0, 0, 0);

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
	{	//뿅~커졌다가
		if (Pop_ == false)
		{
			float4 f4CurrentScale = Text_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 483.0f, 424.0f };
			Text_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 7.f) });

			float4 f4CurrentScale2 = SetRenderer_->GetTransform().GetWorldScale();
			float4 f4DestinationScale2 = { 2048.0f, 336.0f };
			SetRenderer_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale2, f4DestinationScale2, GameEngineTime::GetDeltaTime() * 15.f) });

			//오른쪽 큰 원
			float4 f4CurrentScale3 = SideCircle1_->GetTransform().GetWorldScale();
			float4 f4DestinationScale3 = { 459.0f,141.0f };

			SideCircle1_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale3, f4DestinationScale3, GameEngineTime::GetDeltaTime() * 10.f) });

			float4 f4CurrentScale4 = SideCircle3_->GetTransform().GetWorldScale();
			float4 f4DestinationScale4 = { 400.0f,140.0f };

			SideCircle3_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale4, f4DestinationScale4, GameEngineTime::GetDeltaTime() * 10.f) });

			if (SideCircle1_->GetTransform().GetWorldScale().x <= 300.0f)
			{
				//왼쪽 작은원
				float4 f4CurrentScale = SideCircle2_->GetTransform().GetWorldScale();
				float4 f4DestinationScale = { 300.0f, 92.0f };

				SideCircle2_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });

				//오른쪽 작은 원
				float4 f4CurrentScale2 = SideCircle4_->GetTransform().GetWorldScale();
				float4 f4DestinationScale2 = { 400.0f, 70.0f };

				SideCircle4_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale2, f4DestinationScale2, GameEngineTime::GetDeltaTime() * 10.f) });

			}
			if (Text_->GetTransform().GetWorldScale().x >= f4DestinationScale.x - 5.0f)
			{
				//제 사이즈 되려면 딜레이가 너무 커서 1정도 오차 줌
				Pop_ = true;
			}
		}
	}

	{	//제자리로 줄어들기
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

		////판자
		//float4 f4CurrentScale3 = SetRenderer_->GetTransform().GetWorldScale();
		//float4 f4DestinationScale3 = { 0.0f, 336.0f };

		//SetRenderer_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale3, f4DestinationScale3, GameEngineTime::GetDeltaTime() * 10.f) });


		//글자
		float4 f4CurrentScale4 = Text_->GetTransform().GetWorldScale();
		float4 f4DestinationScale4 = { 0.0f, 0.0f };

		Text_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale4, f4DestinationScale4, GameEngineTime::GetDeltaTime() * 15.f) });
	}
}

void RoundEnd::Reset()
{
	SlicePos_ = float4(0, 0, 0, 0);

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