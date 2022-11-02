#include "PreCompile.h"
#include "TopMenu.h"
#include "GlobalValues.h"

TopMenu::TopMenu() 
	:ButtonCheck(false)
{
}

TopMenu::~TopMenu() 
{
}

void TopMenu::Start()
{
	BG = CreateComponent<GameEngineUIRenderer>();
	BG->GetTransform().SetLocalScale({ 580,72 });
	BG->SetTexture("TopUI.png");
	BG->SetPivot(PIVOTMODE::TOP);
	BG->GetTransform().SetLocalPosition({ 0,450 });

	LeftKey = CreateComponent<GameEngineUIRenderer>();
	LeftKey->GetTransform().SetLocalScale({ 55 * 0.8f,55 * 0.8f });
	LeftKey->SetTexture("Q.png");
	LeftKey->SetPivot(PIVOTMODE::CENTER);
	LeftKey->GetTransform().SetLocalPosition({ -200,415 });

	RightKey = CreateComponent<GameEngineUIRenderer>();
	RightKey->GetTransform().SetLocalScale({ 55 * 0.8f,55 * 0.8f });
	RightKey->SetTexture("E.png");
	RightKey->SetPivot(PIVOTMODE::CENTER);
	RightKey->GetTransform().SetLocalPosition({ 200,415 });

	Panel1 = CreateComponent<GameEngineUIRenderer>();
	Panel1->GetTransform().SetLocalScale({ 100 * 0.7f,74 * 0.7f });
	Panel1->SetTexture("UI_select_panel.png");
	Panel1->SetPivot(PIVOTMODE::CENTER);
	Panel1->GetTransform().SetLocalPosition({ -135,413 });

	PanelCol1 = CreateComponent<GameEngineCollision>();
	PanelCol1->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.0f,1.0f,0.0f,0.3f });
	PanelCol1->GetTransform().SetWorldScale({ 70.0f,48.8f, 1.0f });
	PanelCol1->ChangeOrder(UICOLLISION::Button);
	PanelCol1->GetTransform().SetLocalPosition({ -135,415 });
	PanelCol1->SetUIDebugCamera();

	Panel2 = CreateComponent<GameEngineUIRenderer>();
	Panel2->GetTransform().SetLocalScale({ 100 * 0.7f,74 * 0.7f });
	Panel2->SetTexture("UI_basic_panel.png");
	Panel2->SetPivot(PIVOTMODE::CENTER);
	Panel2->GetTransform().SetLocalPosition({ -45,413 });

	Panel3 = CreateComponent<GameEngineUIRenderer>();
	Panel3->GetTransform().SetLocalScale({ 100 * 0.7f,74 * 0.7f });
	Panel3->SetTexture("UI_basic_panel.png");
	Panel3->SetPivot(PIVOTMODE::CENTER);
	Panel3->GetTransform().SetLocalPosition({ 43,413 });

	Panel4 = CreateComponent<GameEngineUIRenderer>();
	Panel4->GetTransform().SetLocalScale({ 100 * 0.7f,74 * 0.7f });
	Panel4->SetTexture("UI_basic_panel.png");
	Panel4->SetPivot(PIVOTMODE::CENTER);
	Panel4->GetTransform().SetLocalPosition({ 135,413 });

	Home = CreateComponent<GameEngineUIRenderer>();
	Home->GetTransform().SetLocalScale({ 36,34 });
	Home->SetTexture("UI_HomeIcon.png");
	Home->SetPivot(PIVOTMODE::CENTER);
	Home->GetTransform().SetLocalPosition({ -135,415 });

	Event = CreateComponent<GameEngineUIRenderer>();
	Event->GetTransform().SetLocalScale({ 32,36 });
	Event->SetTexture("UI_EventIcon.png");
	Event->SetPivot(PIVOTMODE::CENTER);
	Event->GetTransform().SetLocalPosition({ -45,415 });

	Custom = CreateComponent<GameEngineUIRenderer>();
	Custom->GetTransform().SetLocalScale({ 36,33 });
	Custom->SetTexture("UI_CustomIcon.png");
	Custom->SetPivot(PIVOTMODE::CENTER);
	Custom->GetTransform().SetLocalPosition({ 43,415 });

	Store = CreateComponent<GameEngineUIRenderer>();
	Store->GetTransform().SetLocalScale({ 39,33 });
	Store->SetTexture("UI_StoreIcon.png");
	Store->SetPivot(PIVOTMODE::CENTER);
	Store->GetTransform().SetLocalPosition({ 135,415 });
}

void TopMenu::Update(float _DeltaTime)
{
	{
		PanelCol1->IsCollision(CollisionType::CT_OBB2D, UICOLLISION::Mouse, CollisionType::CT_OBB2D,
			std::bind(&TopMenu::ButtonOn, this, std::placeholders::_1, std::placeholders::_2));
	}
	
	{
		//�� ���ǹ� ���ƴ� Pikable �ڵ� ���� ����..[=]�̰� ���� �� ��; ���ٽ�..?�Լ�������..? ��ư �ؼ� true false�� ����
		ButtonCheck = PanelCol1->IsCollision(CollisionType::CT_OBB, CollisionGroup::Ray, CollisionType::CT_OBB,
			[=](GameEngineCollision* _This, GameEngineCollision* _Other)
			{
				return CollisionReturn::Break;
			});
		int a = 0;
		if (ButtonCheck == false)
		{
			//�浹�� �ƴ϶�� ���� ������� ���ư���
			float4 f4CurrentScale = Panel1->GetTransform().GetWorldScale();
			float4 f4DestinationScale = { 70,51.8 };
			Panel1->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
			a = 100;
		}
		int b = a;
	}
}

CollisionReturn TopMenu::ButtonOn(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	//�浹�ϸ� �ణ ��ư�� �þ
	float4 f4CurrentScale = Panel1->GetTransform().GetWorldScale();
	float4 f4DestinationScale = { 90,51.8 };
	Panel1->GetTransform().SetWorldScale({ float4::Lerp(f4CurrentScale, f4DestinationScale, GameEngineTime::GetDeltaTime() * 15.f) });
	return CollisionReturn::Break;
}
