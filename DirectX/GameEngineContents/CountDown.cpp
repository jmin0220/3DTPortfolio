#include "PreCompile.h"
#include "CountDown.h"

CountDown::CountDown() 
	:IsThreePop_(false)
	,IsThreeEnd_(false)
	,IsTwoPop_(false)
	,IsTwoEnd_(false)
	,IsOnePop_(false)
	,IsOneEnd_(false)
	,IsAniOn_(false)
	,IsGoEnd_(false)
	,IsGoPop_(false)
{
}

CountDown::~CountDown() 
{
}

void CountDown::Start()
{
	{
		Three_ = CreateComponent<GameEngineUIRenderer>();
		//Three_->GetTransform().SetWorldScale({ 195.0f, 246.0f });
		Three_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
		Three_->GetTransform().SetWorldPosition({ 0.0f, 0.0f });
		Three_->SetPivot(PIVOTMODE::CENTER);
		Three_->SetTexture("countdown_sequence_3.png");
	}

	{
		Two_ = CreateComponent<GameEngineUIRenderer>();
		//Two_->GetTransform().SetWorldScale({ 196.0f, 244.0f });
		Two_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
		Two_->GetTransform().SetWorldPosition({ 0.0f, 0.0f });
		Two_->SetPivot(PIVOTMODE::CENTER);
		Two_->SetTexture("countdown_sequence_2.png");
	}

	{
		One_ = CreateComponent<GameEngineUIRenderer>();
		//One_->GetTransform().SetWorldScale({ 152.0f, 241.0f });
		One_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
		One_->GetTransform().SetWorldPosition({ 0.0f, 0.0f });
		One_->SetPivot(PIVOTMODE::CENTER);
		One_->SetTexture("countdown_sequence_1.png");
	}

	{
		Go_ = CreateComponent<GameEngineUIRenderer>();
		//Go_->GetTransform().SetWorldScale({ 462.0f, 240.0f });
		Go_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
		Go_->GetTransform().SetWorldPosition({ 0.0f, 0.0f });
		Go_->SetPivot(PIVOTMODE::CENTER);
		Go_->SetTexture("countdown_sequence_GO.png");
	}

	{
		GameEngineTexture::Cut("Pop_Frames.png", 5, 1);

		PopAni1_ = CreateComponent<GameEngineUIRenderer>();
		PopAni1_->GetTransform().SetWorldScale({ 26.0f, 101.0f });
		PopAni1_->GetTransform().SetWorldPosition({ -150.0f, 200.0f });
		PopAni1_->GetTransform().SetWorldRotation({ 0.0f, 0.0f, 35.0f, 0.0f });
		PopAni1_->SetPivot(PIVOTMODE::CENTER);
		PopAni1_->SetTexture("Pop_Frames.png");

		PopAni2_ = CreateComponent<GameEngineUIRenderer>();
		PopAni2_->GetTransform().SetWorldScale({ 26.0f, 101.0f });
		PopAni2_->GetTransform().SetWorldPosition({ -150.0f, -200.0f });
		PopAni2_->GetTransform().SetWorldRotation({ -180.0f, 0.0f, 35.0f, 0.0f });
		PopAni2_->SetPivot(PIVOTMODE::CENTER);
		PopAni2_->SetTexture("Pop_Frames.png");

		PopAni3_ = CreateComponent<GameEngineUIRenderer>();
		PopAni3_->GetTransform().SetWorldScale({ 26.0f, 101.0f });
		PopAni3_->GetTransform().SetWorldPosition({ -300.0f, 0.0f });
		PopAni3_->GetTransform().SetWorldRotation({ 0.0f, 0.0f, 90.0f, 0.0f });
		PopAni3_->SetPivot(PIVOTMODE::CENTER);
		PopAni3_->SetTexture("Pop_Frames.png");

		PopAni4_ = CreateComponent<GameEngineUIRenderer>();
		PopAni4_->GetTransform().SetWorldScale({ 26.0f, 101.0f });
		PopAni4_->GetTransform().SetWorldPosition({ 300.0f, 0.0f });
		PopAni4_->GetTransform().SetWorldRotation({ 0.0f, 0.0f, -90.0f, 0.0f });
		PopAni4_->SetPivot(PIVOTMODE::CENTER);
		PopAni4_->SetTexture("Pop_Frames.png");

		PopAni5_ = CreateComponent<GameEngineUIRenderer>();
		PopAni5_->GetTransform().SetWorldScale({ 26.0f, 101.0f });
		PopAni5_->GetTransform().SetWorldPosition({ 150.0f, 200.0f });
		PopAni5_->GetTransform().SetWorldRotation({ 0.0f, 0.0f, -35.0f, 0.0f });
		PopAni5_->SetPivot(PIVOTMODE::CENTER);
		PopAni5_->SetTexture("Pop_Frames.png");

		PopAni6_ = CreateComponent<GameEngineUIRenderer>();
		PopAni6_->GetTransform().SetWorldScale({ 26.0f, 101.0f });
		PopAni6_->GetTransform().SetWorldPosition({ 150.0f, -200.0f });
		PopAni6_->GetTransform().SetWorldRotation({ -180.0f, 0.0f, -35.0f, 0.0f });
		PopAni6_->SetPivot(PIVOTMODE::CENTER);
		PopAni6_->SetTexture("Pop_Frames.png");

		std::vector<unsigned int> Five = { 0, 1, 2, 3, 4 };
		PopAni1_->CreateFrameAnimationCutTexture("Pop", GameEngineRenderingEvent("Pop_Frames.png", Five, 0.1f, false));
		PopAni1_->ChangeFrameAnimation("Pop");
		PopAni1_->Off();
		PopAni1_->AnimationBindEnd("Pop", std::bind(&CountDown::PopEnd, this));

		PopAni2_->CreateFrameAnimationCutTexture("Pop", GameEngineRenderingEvent("Pop_Frames.png", Five, 0.1f, false));
		PopAni2_->ChangeFrameAnimation("Pop");
		PopAni2_->Off();
		PopAni2_->AnimationBindEnd("Pop", std::bind(&CountDown::PopEnd, this));

		PopAni3_->CreateFrameAnimationCutTexture("Pop", GameEngineRenderingEvent("Pop_Frames.png", Five, 0.1f, false));
		PopAni3_->ChangeFrameAnimation("Pop");
		PopAni3_->Off();
		PopAni3_->AnimationBindEnd("Pop", std::bind(&CountDown::PopEnd, this));

		PopAni4_->CreateFrameAnimationCutTexture("Pop", GameEngineRenderingEvent("Pop_Frames.png", Five, 0.1f, false));
		PopAni4_->ChangeFrameAnimation("Pop");
		PopAni4_->Off();
		PopAni4_->AnimationBindEnd("Pop", std::bind(&CountDown::PopEnd, this));

		PopAni5_->CreateFrameAnimationCutTexture("Pop", GameEngineRenderingEvent("Pop_Frames.png", Five, 0.1f, false));
		PopAni5_->ChangeFrameAnimation("Pop");
		PopAni5_->Off();
		PopAni5_->AnimationBindEnd("Pop", std::bind(&CountDown::PopEnd, this));

		PopAni6_->CreateFrameAnimationCutTexture("Pop", GameEngineRenderingEvent("Pop_Frames.png", Five, 0.1f, false));
		PopAni6_->ChangeFrameAnimation("Pop");
		PopAni6_->Off();
		PopAni6_->AnimationBindEnd("Pop", std::bind(&CountDown::PopEnd, this));
	}
}

void CountDown::Update(float _DeltaTime)
{
}

void CountDown::LevelStartEvent()
{
	//처음에 다 꺼놔야함
	IsThreePop_ = false;
	IsThreeEnd_ = false;
	Three_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
	Three_->GetTransform().SetWorldRotation({ 0,0,0,0 });
	Three_->On();

	IsTwoPop_ = false;
	IsTwoEnd_ = false;
	Two_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
	Two_->GetTransform().SetWorldRotation({ 0,0,0,0 });
	Two_->On();

	IsOnePop_ = false;
	IsOneEnd_ = false;
	One_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
	One_->GetTransform().SetWorldRotation({ 0,0,0,0 });
	One_->On();

	IsGoPop_ = false;
	IsGoEnd_ = false;
	Go_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
	Go_->On();

	IsAniOn_ = false;
	PopAni1_->CurAnimationReset();
	PopAni2_->CurAnimationReset();
	PopAni3_->CurAnimationReset();
	PopAni4_->CurAnimationReset();
	PopAni5_->CurAnimationReset();
	PopAni6_->CurAnimationReset();
}

void CountDown::CountDownStart()
{
	{
		//========================================3===========================================
		if (IsThreePop_ == false && IsThreeEnd_==false)
		{
			float4 f4CurrentScale = Three_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 205.0f, 256.0f };
			Three_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });

			if (Three_->GetTransform().GetWorldScale().x >= f4DestinationScale.x - 1.0f)
			{
				//제 사이즈 되려면 딜레이가 너무 커서 1정도 오차 줌
				IsThreePop_ = true;
			}
		}

		//제자리로 줄어들기
		if (IsThreePop_ == true)
		{
			float4 f4CurrentScale = Three_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 195.0f,246.0f };
			Three_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });
			
			if (Three_->GetTransform().GetWorldScale().x <= f4DestinationScale.x + 2.0f)
			{
				IsThreePop_ = false;
				IsThreeEnd_ = true;
			}
		}
		
		if (IsThreePop_ == false && IsThreeEnd_ == true)
		{	
			//제 사이즈 후 0으로 작아지기
			Three_->GetTransform().SetAddWorldRotation({ 0,0,GameEngineTime::GetDeltaTime() * -2000.0f,0});
			float4 f4CurrentScale = Three_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 0.0f,0.0f };
			Three_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });
		}
	}

	{
		//========================================2===========================================
		if (IsTwoPop_ == false && IsThreeEnd_ == true && IsTwoEnd_==false && Three_->GetTransform().GetWorldScale().x<=1.0f) //3이 끝낫을때 시작해야하니 체크항목 하나 더 추가
		{
			Three_->Off();
			float4 f4CurrentScale = Two_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 206.0f, 254.0f };
			Two_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });

			if (Two_->GetTransform().GetWorldScale().x >= f4DestinationScale.x - 1.0f)
			{
				IsTwoPop_ = true;
			}
		}

		//제자리로 줄어들기
		if (IsTwoPop_ == true)
		{
			float4 f4CurrentScale = Two_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 196.0f, 244.0f };
			Two_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });

			if (Two_->GetTransform().GetWorldScale().x <= f4DestinationScale.x + 2.0f)
			{
				IsTwoPop_ = false;
				IsTwoEnd_ = true;
			}
		}

		if (IsTwoPop_ == false && IsTwoEnd_ == true)
		{
			Two_->GetTransform().SetAddWorldRotation({ 0,0,GameEngineTime::GetDeltaTime() * -2000.0f,0 });
			float4 f4CurrentScale = Two_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 0.0f,0.0f };
			Two_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });
		}
	}

	{
		//========================================1===========================================
		if (IsOnePop_ == false && IsTwoEnd_ == true && IsOneEnd_ == false && Two_->GetTransform().GetWorldScale().x <= 1.0f) //3이 끝낫을때 시작해야하니 체크항목 하나 더 추가
		{
			Two_->Off();
			float4 f4CurrentScale = One_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 162.0f, 251.0f };
			One_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });

			if (One_->GetTransform().GetWorldScale().x >= f4DestinationScale.x - 1.0f)
			{
				IsOnePop_ = true;
			}
		}

		//제자리로 줄어들기
		if (IsOnePop_ == true)
		{
			float4 f4CurrentScale = One_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 152.0f, 241.0f };
			One_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });

			if (One_->GetTransform().GetWorldScale().x <= f4DestinationScale.x + 2.0f)
			{
				IsOnePop_ = false;
				IsOneEnd_ = true;
			}
		}

		if (IsOnePop_ == false && IsOneEnd_ == true)
		{
			One_->GetTransform().SetAddWorldRotation({ 0,0,GameEngineTime::GetDeltaTime() * -2000.0f,0 });
			float4 f4CurrentScale = One_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 0.0f,0.0f };
			One_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });
		}
	}

	{
		//========================================GO===========================================
		if (IsGoPop_ == false && IsOneEnd_ == true && IsGoEnd_ == false && One_->GetTransform().GetWorldScale().x <= 1.0f) //3이 끝낫을때 시작해야하니 체크항목 하나 더 추가
		{
			One_->Off();

			if (IsAniOn_ == false)
			{
				PopAni1_->On();
				PopAni2_->On();
				PopAni3_->On();
				PopAni4_->On();
				PopAni5_->On();
				PopAni6_->On();
				IsAniOn_ = true;
			}
			//PopAni1_->ChangeFrameAnimation("Pop");

			float4 f4CurrentScale = Go_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 472.0f, 250.0f };
			Go_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });

			if (Go_->GetTransform().GetWorldScale().x >= f4DestinationScale.x - 1.0f)
			{
				IsGoPop_ = true;
			}
		}

		//제자리로 줄어들기
		if (IsGoPop_ == true)
		{
			float4 f4CurrentScale = Go_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 462.0f, 240.0f };
			Go_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });

			if (Go_->GetTransform().GetWorldScale().x <= f4DestinationScale.x + 2.0f)
			{
				IsGoPop_ = false;
				IsGoEnd_ = true;
			}
		}

		if (IsGoPop_ == false && IsGoEnd_ == true)
		{
			float4 f4CurrentScale = Go_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 0.0f,0.0f };
			Go_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });

			if (Go_->GetTransform().GetWorldScale().x <= 1.0f)
			{
				Go_->Off();
			}
		}
	}
}

void CountDown::PopEnd()
{
	PopAni1_->Off();
	PopAni2_->Off();
	PopAni3_->Off();
	PopAni4_->Off();
	PopAni5_->Off();
	PopAni6_->Off();
}

void CountDown::Reset()
{
	//처음에 다 꺼놔야함
	IsThreePop_ = false;
	IsThreeEnd_ = false;
	Three_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
	Three_->GetTransform().SetWorldRotation({ 0,0,0,0 });
	Three_->On();

	IsTwoPop_ = false;
	IsTwoEnd_ = false;
	Two_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
	Two_->GetTransform().SetWorldRotation({ 0,0,0,0 });
	Two_->On();

	IsOnePop_ = false;
	IsOneEnd_ = false;
	One_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
	One_->GetTransform().SetWorldRotation({ 0,0,0,0 });
	One_->On();

	IsGoPop_ = false;
	IsGoEnd_ = false;
	Go_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
	Go_->On();

	IsAniOn_ = false;
	PopAni1_->CurAnimationReset();
	PopAni2_->CurAnimationReset();
	PopAni3_->CurAnimationReset();
	PopAni4_->CurAnimationReset();
	PopAni5_->CurAnimationReset();
	PopAni6_->CurAnimationReset();
}