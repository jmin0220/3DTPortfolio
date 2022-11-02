#include "PreCompile.h"
#include "PlayButton.h"

PlayButton::PlayButton() 
{
}

PlayButton::~PlayButton() 
{
}

void PlayButton::Start()
{
	Button_ = CreateComponent<GameEngineUIRenderer>();
	Button_->SetTexture("Play.png");
	Button_->GetTransform().SetWorldScale({ 350.0f, 110.0f });
	Button_->GetTransform().SetWorldPosition({ 600.0f,-380.0f });

	Key_ = CreateComponent<GameEngineUIRenderer>();
	Key_->SetTexture("Spacebar.png");
	Key_->GetTransform().SetWorldScale({ 114 * 0.5f, 55 * 0.5f });
	Key_->GetTransform().SetWorldPosition({ 600.0f,-420.0f });

	Font_ = CreateComponent<GameEngineFontRenderer>();
	Font_->ChangeCamera(CAMERAORDER::UICAMERA);
	Font_->SetText("ÇÃ·¹ÀÌ", "Noto Sans CJK SC");
	Font_->SetSize(25.0f);
	Font_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	Font_->SetScreenPostion({ 1400.0f,805.0f });
}

void PlayButton::Update(float _DeltaTime)
{
}

