#include "PreCompile.h"
#include "TopMenu.h"
#include "GlobalValues.h"

TopMenu::TopMenu() 
	:ButtonCheck1_(false)
	,ButtonCheck2_(false)
	,ButtonCheck3_(false)
{
}

TopMenu::~TopMenu() 
{
}

void TopMenu::Start()
{
	MyState_ = MenuState::Home;

	BG_ = CreateComponent<GameEngineUIRenderer>();
	BG_->GetTransform().SetLocalScale({ 580.0f,72.0f });
	BG_->SetTexture("TopUI.png");
	BG_->SetPivot(PIVOTMODE::TOP);
	BG_->GetTransform().SetWorldPosition({ 0.f,450.f });

	LeftKey_ = CreateComponent<GameEngineUIRenderer>();
	LeftKey_->GetTransform().SetLocalScale({ 55 * 0.8f,55 * 0.8f });
	LeftKey_->SetTexture("Q.png");
	LeftKey_->SetPivot(PIVOTMODE::CENTER);
	LeftKey_->GetTransform().SetWorldPosition({ -200.f,415.f });

	RightKey_ = CreateComponent<GameEngineUIRenderer>();
	RightKey_->GetTransform().SetLocalScale({ 55 * 0.8f,55 * 0.8f });
	RightKey_->SetTexture("E.png");
	RightKey_->SetPivot(PIVOTMODE::CENTER);
	RightKey_->GetTransform().SetWorldPosition({ 200.f,415.f });

	Panel1_ = CreateComponent<GameEngineUIRenderer>();
	Panel1_->GetTransform().SetLocalScale({ 100 * 0.7f,74 * 0.7f });
	Panel1_->SetTexture("UI_select_panel.png");
	Panel1_->SetPivot(PIVOTMODE::CENTER);
	Panel1_->GetTransform().SetWorldPosition({ -135.f,413.f });

	PanelCol1_ = CreateComponent<GameEngineCollision>();
	PanelCol1_->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,1.0f,0.0f,0.3f });
	PanelCol1_->GetTransform().SetWorldScale({ 70.0f,48.8f, 1.0f });
	PanelCol1_->ChangeOrder(UICOLLISION::Button);
	PanelCol1_->GetTransform().SetWorldPosition({ -135.f,415.f });
	PanelCol1_->SetUIDebugCamera();

	Panel2_ = CreateComponent<GameEngineUIRenderer>();
	Panel2_->GetTransform().SetLocalScale({ 100 * 0.7f,74 * 0.7f });
	Panel2_->SetTexture("UI_basic_panel.png");
	Panel2_->SetPivot(PIVOTMODE::CENTER);
	Panel2_->GetTransform().SetWorldPosition({ -45.f,413.f });

	PanelCol2_ = CreateComponent<GameEngineCollision>();
	PanelCol2_->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,1.0f,0.0f,0.3f });
	PanelCol2_->GetTransform().SetWorldScale({ 70.0f,48.8f, 1.0f });
	PanelCol2_->ChangeOrder(UICOLLISION::Button);
	PanelCol2_->GetTransform().SetWorldPosition({ -45.f,415.f });
	PanelCol2_->SetUIDebugCamera();

	Panel3_ = CreateComponent<GameEngineUIRenderer>();
	Panel3_->GetTransform().SetLocalScale({ 100 * 0.7f,74 * 0.7f });
	Panel3_->SetTexture("UI_basic_panel.png");
	Panel3_->SetPivot(PIVOTMODE::CENTER);
	Panel3_->GetTransform().SetWorldPosition({ 43.f,413.f });

	PanelCol3_ = CreateComponent<GameEngineCollision>();
	PanelCol3_->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,1.0f,0.0f,0.3f });
	PanelCol3_->GetTransform().SetWorldScale({ 70.0f,48.8f, 1.0f });
	PanelCol3_->ChangeOrder(UICOLLISION::Button);
	PanelCol3_->GetTransform().SetWorldPosition({ 43.f,415.f });
	PanelCol3_->SetUIDebugCamera();

	Panel4_ = CreateComponent<GameEngineUIRenderer>();
	Panel4_->GetTransform().SetWorldScale({ 100 * 0.7f,74 * 0.7f });
	Panel4_->SetTexture("UI_basic_panel.png");
	Panel4_->SetPivot(PIVOTMODE::CENTER);
	Panel4_->GetTransform().SetLocalPosition({ 135.f,413.f });

	PanelCol4_ = CreateComponent<GameEngineCollision>();
	PanelCol4_->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,1.0f,0.0f,0.3f });
	PanelCol4_->GetTransform().SetWorldScale({ 70.0f,48.8f, 1.0f });
	PanelCol4_->ChangeOrder(UICOLLISION::Button);
	PanelCol4_->GetTransform().SetWorldPosition({ 135.f,415.f });
	PanelCol4_->SetUIDebugCamera();

	Home_ = CreateComponent<GameEngineUIRenderer>();
	Home_->GetTransform().SetLocalScale({ 36.f,34.f });
	Home_->SetTexture("UI_HomeIcon.png");
	Home_->SetPivot(PIVOTMODE::CENTER);
	Home_->GetTransform().SetLocalPosition({ -135.f,415.f });

	Event_ = CreateComponent<GameEngineUIRenderer>();
	Event_->GetTransform().SetLocalScale({ 32.f,36.f });
	Event_->SetTexture("UI_icon_settings_1080p.png");
	Event_->SetPivot(PIVOTMODE::CENTER);
	Event_->GetTransform().SetWorldPosition({ -45.f,415.f });

	Custom_ = CreateComponent<GameEngineUIRenderer>();
	Custom_->GetTransform().SetLocalScale({ 36.f,33.f });
	Custom_->SetTexture("UI_CustomIcon.png");
	Custom_->SetPivot(PIVOTMODE::CENTER);
	Custom_->GetTransform().SetWorldPosition({ 43.f,415.f });

	Store_ = CreateComponent<GameEngineUIRenderer>();
	Store_->GetTransform().SetLocalScale({ 39.f,33.f });
	Store_->SetTexture("UI_StoreIcon.png");
	Store_->SetPivot(PIVOTMODE::CENTER);
	Store_->GetTransform().SetWorldPosition({ 135.f,415.f });
}

void TopMenu::Update(float _DeltaTime)
{
	MenuAnimation();

	MyMenuUpdate();
}

void TopMenu::MyMenuUpdate()
{
	if (MyState_ == MenuState::Home && true == GameEngineInput::GetInst()->IsDown("RIGHT_E"))
	{
		MyState_ = MenuState::Option;
		Panel1_->SetTexture("UI_basic_panel.png");
		Panel2_->SetTexture("UI_select_panel.png");
	}

	if (MyState_ == MenuState::Option && true == GameEngineInput::GetInst()->IsDown("LEFT_Q"))
	{
		MyState_ = MenuState::Home;
		Panel1_->SetTexture("UI_select_panel.png");
		Panel2_->SetTexture("UI_basic_panel.png");
	}
}

void TopMenu::MenuAnimation()
{
	{
		//�� ���ǹ� ���ƴ� Pikable �ڵ� ���� ����..[=]�̰� ���� �� ��; ���ٽ�..?�Լ�������..? ��ư �ؼ� true false�� ����
		ButtonCheck1_ = PanelCol1_->IsCollision(CollisionType::CT_OBB2D, UICOLLISION::Mouse, CollisionType::CT_OBB2D,
			[=](std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
			{
				if (MyState_ == MenuState::Option && true == GameEngineInput::GetInst()->IsDown("Click"))
				{
					MyState_ = MenuState::Home;
					Panel1_->SetTexture("UI_select_panel.png");
					Panel2_->SetTexture("UI_basic_panel.png");
				}
				return CollisionReturn::Break;
			});
		ButtonCheck2_ = PanelCol2_->IsCollision(CollisionType::CT_OBB2D, UICOLLISION::Mouse, CollisionType::CT_OBB2D,
			[=](std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
			{
				if (MyState_ == MenuState::Home && true == GameEngineInput::GetInst()->IsDown("Click"))
				{
					MyState_ = MenuState::Option;
					Panel1_->SetTexture("UI_basic_panel.png");
					Panel2_->SetTexture("UI_select_panel.png");
				}
				return CollisionReturn::Break;
			});
		ButtonCheck3_ = PanelCol3_->IsCollision(CollisionType::CT_OBB2D, UICOLLISION::Mouse, CollisionType::CT_OBB2D,
			[=](std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
			{
				return CollisionReturn::Break;
			});
		ButtonCheck4_ = PanelCol4_->IsCollision(CollisionType::CT_OBB2D, UICOLLISION::Mouse, CollisionType::CT_OBB2D,
			[=](std::shared_ptr<GameEngineCollision> _This, std::shared_ptr<GameEngineCollision> _Other)
			{
				return CollisionReturn::Break;
			});

		if (ButtonCheck1_ == false)
		{
			//�浹�� �ƴ϶�� ���� ������� ���ư���
			float4 f4CurrentScale = Panel1_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 70.f,51.8f };
			Panel1_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
		}
		else
		{
			float4 f4CurrentScale = Panel1_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 90.f,51.8f };
			Panel1_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
		}
		if (ButtonCheck2_ == false)
		{
			//�浹�� �ƴ϶�� ���� ������� ���ư���
			float4 f4CurrentScale = Panel2_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 70.f,51.8f };
			Panel2_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
		}
		else
		{
			float4 f4CurrentScale = Panel2_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 90.f,51.8f };
			Panel2_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
		}
		if (ButtonCheck3_ == false)
		{
			//�浹�� �ƴ϶�� ���� ������� ���ư���
			float4 f4CurrentScale = Panel3_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 70.f,51.8f };
			Panel3_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
		}
		else
		{
			float4 f4CurrentScale = Panel3_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 90.f,51.8f };
			Panel3_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
		}
		if (ButtonCheck4_ == false)
		{
			//�浹�� �ƴ϶�� ���� ������� ���ư���
			float4 f4CurrentScale = Panel4_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 70.f,51.8f };
			Panel4_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
		}
		else
		{
			float4 f4CurrentScale = Panel4_->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 90.f,51.8f };
			Panel4_->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
		}
	}
}