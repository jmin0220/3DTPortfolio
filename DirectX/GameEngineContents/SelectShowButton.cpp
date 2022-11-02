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
	Button_ = CreateComponent<GameEngineUIRenderer>();
	Button_->SetTexture("SelectShow.png");
	Button_->GetTransform().SetWorldScale({ 350.0f, 90.0f });
	Button_->GetTransform().SetWorldPosition({600.0f,-270.0f });

	Key_ = CreateComponent<GameEngineUIRenderer>();
	Key_->SetTexture("Ctrl.png");
	Key_->GetTransform().SetWorldScale({ 44.0f, 44.0f });
	Key_->GetTransform().SetWorldPosition({ 600.0f,-305.0f });

	Font_ = CreateComponent<GameEngineFontRenderer>();
	Font_->ChangeCamera(CAMERAORDER::UICAMERA);
	Font_->SetText("¼î ¼±ÅÃ", "Noto Sans CJK SC");
	Font_->SetSize(25.0f);
	Font_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	Font_->SetScreenPostion({ 1400.0f,695.0f });
}

void SelectShowButton::Update(float _DeltaTime)
{
}

