#include "PreCompile.h"
#include "SelectShowButton.h"

SelectShowButton::SelectShowButton() 
{
}

SelectShowButton::~SelectShowButton() 
{
}

void SelectShowButton::Start()
{
	Button = CreateComponent<GameEngineUIRenderer>();
	Button->SetTexture("SelectShow.png");
	Button->GetTransform().SetWorldScale({ 350, 90 });
	Button->GetTransform().SetWorldPosition({600,-270});

	Key = CreateComponent<GameEngineUIRenderer>();
	Key->SetTexture("Ctrl.png");
	Key->GetTransform().SetWorldScale({ 44, 44});
	Key->GetTransform().SetWorldPosition({ 600,-305 });

	Font = CreateComponent<GameEngineFontRenderer>();
	Font->SetText("¼î ¼±ÅÃ", "Noto Sans CJK SC");
	Font->SetSize(25.0f);
	Font->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	Font->SetScreenPostion({ 1400,695 });
}

void SelectShowButton::Update(float _DeltaTime)
{
}

