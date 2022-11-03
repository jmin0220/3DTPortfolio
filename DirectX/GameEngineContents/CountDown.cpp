#include "PreCompile.h"
#include "CountDown.h"

CountDown::CountDown() 
	:IsThreePop_(false)
	,IsTwoPop_(false)
	,IsOnePop_(false)
	,IsThreeEnd_(false)
	,IsOneEnd_(false)
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
}

void CountDown::Update(float _DeltaTime)
{
}

void CountDown::LevelStartEvent()
{
	//ó���� �� ��������
	IsThreePop_ = false;
	IsThreeEnd_ = false;
	Three_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
	Three_->On();

	IsTwoPop_ = false;
	IsTwoEnd_ = false;
	Two_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
	Two_->On();

	IsOnePop_ = false;
	IsOneEnd_ = false;
	One_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
	One_->On();

	IsGoPop_ = false;
	IsGoEnd_ = false;
	Go_->GetTransform().SetWorldScale({ 0.0f, 0.0f });
	Go_->On();
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
				//�� ������ �Ƿ��� �����̰� �ʹ� Ŀ�� 1���� ���� ��
				IsThreePop_ = true;
			}
		}

		//���ڸ��� �پ���
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
			float4 f4CurrentScale = Three_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 0.0f,0.0f };
			Three_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });
		}
	}

	{
		//========================================2===========================================
		if (IsTwoPop_ == false && IsThreeEnd_ == true && IsTwoEnd_==false && Three_->GetTransform().GetWorldScale().x<=1.0f) //3�� �������� �����ؾ��ϴ� üũ�׸� �ϳ� �� �߰�
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

		//���ڸ��� �پ���
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
			float4 f4CurrentScale = Two_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 0.0f,0.0f };
			Two_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });
		}
	}

	{
		//========================================1===========================================
		if (IsOnePop_ == false && IsTwoEnd_ == true && IsOneEnd_ == false && Two_->GetTransform().GetWorldScale().x <= 1.0f) //3�� �������� �����ؾ��ϴ� üũ�׸� �ϳ� �� �߰�
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

		//���ڸ��� �پ���
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
			float4 f4CurrentScale = One_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 0.0f,0.0f };
			One_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });
		}
	}

	{
		//========================================GO===========================================
		if (IsGoPop_ == false && IsOneEnd_ == true && IsGoEnd_ == false && One_->GetTransform().GetWorldScale().x <= 1.0f) //3�� �������� �����ؾ��ϴ� üũ�׸� �ϳ� �� �߰�
		{
			One_->Off();
			float4 f4CurrentScale = Go_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 472.0f, 250.0f };
			Go_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 10.f) });

			if (Go_->GetTransform().GetWorldScale().x >= f4DestinationScale.x - 1.0f)
			{
				IsGoPop_ = true;
			}
		}

		//���ڸ��� �پ���
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