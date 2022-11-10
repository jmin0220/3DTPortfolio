#include "PreCompile.h"
#include "NoneMoney.h"

NoneMoney::NoneMoney() 
{
}

NoneMoney::~NoneMoney() 
{
}

void NoneMoney::Start()
{
	MoneyCost_ = 0;

	MoneyCount_ = CreateComponent<GameEngineUIRenderer>();
	MoneyCount_->SetTexture("Money.png");
	MoneyCount_->GetTransform().SetLocalScale({ 230 * 0.7f,64 * 0.7f });
	MoneyCount_->SetPivot(PIVOTMODE::LEFTTOP);
	MoneyCount_->GetTransform().SetWorldPosition({ 500.0f,430.0f });

	MoneyIcon_ = CreateComponent<GameEngineUIRenderer>();
	MoneyIcon_->SetTexture("MoneyIcon.png");
	MoneyIcon_->GetTransform().SetLocalScale({ 132 * 0.4f,136 * 0.4f });
	MoneyIcon_->GetTransform().SetWorldPosition({ 500.0f, 405.0f });

	MoneyNumber_ = CreateComponent<GameEngineFontRenderer>();
	MoneyNumber_->ChangeCamera(CAMERAORDER::UICAMERA);
	MoneyNumber_->SetSize(20.0f);
	MoneyNumber_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	MoneyNumber_->SetParent(MoneyCount_.get());
	MoneyNumber_->SetScreenPostion({ 1390.0f,28.0f });
	MoneyNumber_->SetText(std::to_string(MoneyCost_), "Noto Sans CJK SC");
}

void NoneMoney::Update(float _DeltaTime)
{
}

