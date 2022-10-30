#include "PreCompile.h"
#include "NoneButton.h"

NoneButton::NoneButton() 
{
}

NoneButton::~NoneButton() 
{
}

void NoneButton::Start()
{
	OpenParty = CreateComponent<GameEngineUIRenderer>();
	OpenParty->SetTexture("OpenParty.png");
	OpenParty->GetTransform().SetWorldScale({230,60});
	OpenParty->SetPivot(PIVOTMODE::LEFTBOT);
	OpenParty->GetTransform().SetLocalPosition({ -800,-450 });

	Tab = CreateComponent<GameEngineUIRenderer>();
	Tab->SetTexture("tab.png");
	Tab->GetTransform().SetLocalScale({ 95 * 0.5f, 55 * 0.5f });
	Tab->GetTransform().SetLocalPosition({ -770, -425 });
	Tab->SetPivot(PIVOTMODE::LEFT);

	F_OpenParty = CreateComponent<GameEngineFontRenderer>();
	F_OpenParty->SetParent(OpenParty);
	F_OpenParty->ChangeCamera(CAMERAORDER::UICAMERA);
	F_OpenParty->SetColor({ 1.0f,1.0f,1.0f, 0.9f });
	F_OpenParty->SetSize(20.0f);
	F_OpenParty->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	F_OpenParty->SetScreenPostion({ 120.0f ,860.0f});
	F_OpenParty->SetText("파티 열기", "Noto Sans CJK SC");
}

void NoneButton::Update(float _DeltaTime)
{
}

