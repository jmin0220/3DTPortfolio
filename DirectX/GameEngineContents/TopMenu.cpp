#include "PreCompile.h"
#include "TopMenu.h"
#include "GlobalValues.h"

TopMenu::TopMenu() 
	:ButtonCheck_(false)
{
}

TopMenu::~TopMenu() 
{
}

void TopMenu::Start()
{
	BG_ = CreateComponent<GameEngineUIRenderer>();
	BG_->GetTransform().SetLocalScale({ 580.0f,72.0f });
	BG_->SetTexture("TopUI.png");
	BG_->SetPivot(PIVOTMODE::TOP);
	BG_->GetTransform().SetLocalPosition({ 0.f,450.f });

	LeftKey_ = CreateComponent<GameEngineUIRenderer>();
	LeftKey_->GetTransform().SetLocalScale({ 55 * 0.8f,55 * 0.8f });
	LeftKey_->SetTexture("Q.png");
	LeftKey_->SetPivot(PIVOTMODE::CENTER);
	LeftKey_->GetTransform().SetLocalPosition({ -200.f,415.f });

	RightKey_ = CreateComponent<GameEngineUIRenderer>();
	RightKey_->GetTransform().SetLocalScale({ 55 * 0.8f,55 * 0.8f });
	RightKey_->SetTexture("E.png");
	RightKey_->SetPivot(PIVOTMODE::CENTER);
	RightKey_->GetTransform().SetLocalPosition({ 200.f,415.f });

	Panel1_ = CreateComponent<GameEngineUIRenderer>();
	Panel1_->GetTransform().SetLocalScale({ 100 * 0.7f,74 * 0.7f });
	Panel1_->SetTexture("UI_select_panel.png");
	Panel1_->SetPivot(PIVOTMODE::CENTER);
	Panel1_->GetTransform().SetLocalPosition({ -135.f,413.f });

	PanelCol1_ = CreateComponent<GameEngineCollision>();
	PanelCol1_->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,1.0f,0.0f,0.3f });
	PanelCol1_->GetTransform().SetWorldScale({ 70.0f,48.8f, 1.0f });
	PanelCol1_->ChangeOrder(UICOLLISION::Button);
	PanelCol1_->GetTransform().SetLocalPosition({ -135.f,415.f });
	PanelCol1_->SetUIDebugCamera();

	Panel2_ = CreateComponent<GameEngineUIRenderer>();
	Panel2_->GetTransform().SetLocalScale({ 100 * 0.7f,74 * 0.7f });
	Panel2_->SetTexture("UI_basic_panel.png");
	Panel2_->SetPivot(PIVOTMODE::CENTER);
	Panel2_->GetTransform().SetLocalPosition({ -45.f,413.f });

	Panel3_ = CreateComponent<GameEngineUIRenderer>();
	Panel3_->GetTransform().SetLocalScale({ 100 * 0.7f,74 * 0.7f });
	Panel3_->SetTexture("UI_basic_panel.png");
	Panel3_->SetPivot(PIVOTMODE::CENTER);
	Panel3_->GetTransform().SetLocalPosition({ 43.f,413.f });

	Panel4_ = CreateComponent<GameEngineUIRenderer>();
	Panel4_->GetTransform().SetLocalScale({ 100 * 0.7f,74 * 0.7f });
	Panel4_->SetTexture("UI_basic_panel.png");
	Panel4_->SetPivot(PIVOTMODE::CENTER);
	Panel4_->GetTransform().SetLocalPosition({ 135.f,413.f });

	Home_ = CreateComponent<GameEngineUIRenderer>();
	Home_->GetTransform().SetLocalScale({ 36.f,34.f });
	Home_->SetTexture("UI_HomeIcon.png");
	Home_->SetPivot(PIVOTMODE::CENTER);
	Home_->GetTransform().SetLocalPosition({ -135.f,415.f });

	Event_ = CreateComponent<GameEngineUIRenderer>();
	Event_->GetTransform().SetLocalScale({ 32.f,36.f });
	Event_->SetTexture("UI_EventIcon.png");
	Event_->SetPivot(PIVOTMODE::CENTER);
	Event_->GetTransform().SetLocalPosition({ -45.f,415.f });

	Custom_ = CreateComponent<GameEngineUIRenderer>();
	Custom_->GetTransform().SetLocalScale({ 36.f,33.f });
	Custom_->SetTexture("UI_CustomIcon.png");
	Custom_->SetPivot(PIVOTMODE::CENTER);
	Custom_->GetTransform().SetLocalPosition({ 43.f,415.f });

	Store_ = CreateComponent<GameEngineUIRenderer>();
	Store_->GetTransform().SetLocalScale({ 39.f,33.f });
	Store_->SetTexture("UI_StoreIcon.png");
	Store_->SetPivot(PIVOTMODE::CENTER);
	Store_->GetTransform().SetLocalPosition({ 135.f,415.f });
}

void TopMenu::Update(float _DeltaTime)
{
	{
		PanelCol1_->IsCollision(CollisionType::CT_OBB2D, UICOLLISION::Mouse, CollisionType::CT_OBB2D,
			std::bind(&TopMenu::ButtonOn, this, std::placeholders::_1, std::placeholders::_2));
	}
	
	{
		//이 조건문 성훈님 Pikable 코드 베껴 적음..[=]이게 뭔지 모름 ㅎ; 람다식..?함수포인터..? 암튼 해서 true false를 받음
		ButtonCheck_ = PanelCol1_->IsCollision(CollisionType::CT_OBB, CollisionGroup::Ray, CollisionType::CT_OBB,
			[=](std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
			{
				return CollisionReturn::Break;
			});

		if (ButtonCheck_ == false)
		{
			//충돌이 아니라면 원래 사이즈로 돌아간다
			float4 f4CurrentScale = Panel1_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 70.f,51.8f };
			Panel1_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
		}
	}
}

CollisionReturn TopMenu::ButtonOn(std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
{
	//충돌하면 약간 버튼이 늘어남
	float4 f4CurrentScale = Panel1_->GetTransform().GetWorldScale();
	float4 f4DestinationScale = { 90.f,51.8f };
	Panel1_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
	return CollisionReturn::Break;
}
