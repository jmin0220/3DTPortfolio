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
	MoneyCost = 0;

	MoneyCount = CreateComponent<GameEngineUIRenderer>();
	MoneyCount->SetTexture("Money.png");
	MoneyCount->GetTransform().SetLocalScale({ 230 * 0.7f,64 * 0.7f });
	MoneyCount->SetPivot(PIVOTMODE::LEFTTOP);
	MoneyCount->GetTransform().SetWorldPosition({ 500,430 });

	MoneyIcon = CreateComponent<GameEngineUIRenderer>();
	MoneyIcon->SetTexture("MoneyIcon.png");
	MoneyIcon->GetTransform().SetLocalScale({ 132 * 0.4f,136 * 0.4f });
	MoneyIcon->GetTransform().SetWorldPosition({ 500,405 });

	MoneyNumber = CreateComponent<GameEngineFontRenderer>();
	MoneyNumber->SetText(std::to_string(MoneyCost), "Noto Sans CJK SC");
	MoneyNumber->SetSize(20);
	MoneyNumber->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	MoneyNumber->SetParent(MoneyCount);
	MoneyNumber->SetScreenPostion({ 1390,28 });
}

void NoneMoney::Update(float _DeltaTime)
{
}

