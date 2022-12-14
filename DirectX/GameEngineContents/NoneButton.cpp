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
	OpenParty_ = CreateComponent<GameEngineUIRenderer>();
	OpenParty_->SetTexture("OpenParty.png");
	OpenParty_->GetTransform().SetWorldScale({230.0f, 60.0f });
	OpenParty_->SetPivot(PIVOTMODE::LEFTBOT);
	OpenParty_->GetTransform().SetLocalPosition({ -800.0f,-450.0f });

	Tab_ = CreateComponent<GameEngineUIRenderer>();
	Tab_->SetTexture("tab.png");
	Tab_->GetTransform().SetLocalScale({ 95 * 0.5f, 55 * 0.5f });
	Tab_->GetTransform().SetLocalPosition({ -770.0f, -425.0f });
	Tab_->SetPivot(PIVOTMODE::LEFT);

	F_OpenParty_ = CreateComponent<GameEngineFontRenderer>();
	F_OpenParty_->SetParent(OpenParty_);
	//F_OpenParty_->ChangeCamera(CAMERAORDER::UICAMERA);
	F_OpenParty_->SetColor({ 1.0f,1.0f,1.0f, 0.9f });
	F_OpenParty_->SetSize(20.0f);
	F_OpenParty_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	F_OpenParty_->SetScreenPostion({ 120.0f ,860.0f});
	F_OpenParty_->SetText("파티 열기", "Noto Sans CJK SC");
}

void NoneButton::Update(float _DeltaTime)
{
}

