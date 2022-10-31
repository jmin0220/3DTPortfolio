#include "PreCompile.h"
#include "TopMenu.h"

TopMenu::TopMenu() 
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
}

