#include "PreCompile.h"
#include "PlayButton.h"

PlayButton::PlayButton() 
	:ButtonCheck_(false)
	,IsPop_(false)
	,IsEnd_(false)
{
}

PlayButton::~PlayButton() 
{
}

void PlayButton::Start()
{
	Button_ = CreateComponent<GameEngineUIRenderer>();
	Button_->SetTexture("Play.png");
	Button_->GetTransform().SetWorldScale({ 350.0f, 110.0f });
	Button_->GetTransform().SetWorldPosition({ 600.0f,-380.0f });

	ButtonCol_ = CreateComponent<GameEngineCollision>();
	ButtonCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,1.0f,0.0f,0.3f });
	ButtonCol_->SetUIDebugCamera();
	ButtonCol_->GetTransform().SetWorldScale({ 350.0f, 90.0f });
	ButtonCol_->GetTransform().SetWorldPosition({ 600.0f,-375.0f });
	ButtonCol_->ChangeOrder(UICOLLISION::Button);

	Key_ = CreateComponent<GameEngineUIRenderer>();
	Key_->SetTexture("Spacebar.png");
	Key_->GetTransform().SetWorldScale({ 114 * 0.5f, 55 * 0.5f });
	Key_->GetTransform().SetWorldPosition({ 600.0f,-420.0f });

	Font_ = CreateComponent<GameEngineFontRenderer>();
	Font_->ChangeCamera(CAMERAORDER::UICAMERA);
	Font_->SetText("플레이!", "Noto Sans CJK SC");
	Font_->SetSize(25.0f);
	Font_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	Font_->SetScreenPostion({ 1400.0f,805.0f });
}

void PlayButton::Update(float _DeltaTime)
{
	ButtonCheck_ = ButtonCol_->IsCollision(CollisionType::CT_OBB2D, UICOLLISION::Mouse, CollisionType::CT_OBB2D,
		[=](std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
		{
			return CollisionReturn::Break;
		});

	{
		if (ButtonCheck_ == true)
		{
			Button_->SetTexture("Play_Pink.png");
			if (IsPop_ == false && IsEnd_ == false)
			{
				IsEnd_ = false;
				//충돌했을때 한번커지고
				float4 f4CurrentScale = Button_->GetTransform().GetWorldScale();
				float4 f4DestinationScale = { 400.f,160.0f };
				Button_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
				
				if (Button_->GetTransform().GetWorldScale().x >= 380.0f)
				{
					IsPop_ = true;
				}
			}


			if (IsPop_ == true && IsEnd_ == false)
			{
				//제자리로
				float4 f4CurrentScale = Button_->GetTransform().GetWorldScale();
				float4 f4DestinationScale = { 350.f,110.0f };
				Button_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });

				if (Button_->GetTransform().GetWorldScale().x <= 351.0f)
				{
					IsEnd_ = true;
				}
			}
		}

		else if (ButtonCheck_ == false)
		{
			Button_->SetTexture("Play.png");
			//충돌이 아니라면 원래 사이즈로 돌아간다
			IsPop_ = false;
			IsEnd_ = false;
			float4 f4CurrentScale = Button_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 350.0f, 110.0f };
			Button_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
		}
	}
}