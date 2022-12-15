#include "PreCompile.h"
#include "Winner.h"


Winner::Winner() 
{
}

Winner::~Winner() 
{
}

void Winner::Start()
{
}

void Winner::Update(float _DeltaTime)
{
}

void Winner::LevelStartEvent()
{
	BGRenderer_ = CreateComponent<GameEngineUIRenderer>();
	BGRenderer_->SetTexture("WinnerBar.png");
	BGRenderer_->GetTransform().SetWorldScale({ 354.0f,64.0f });
	BGRenderer_->GetTransform().SetWorldRotation({0,0,5.0f});
	BGRenderer_->GetTransform().SetWorldPosition({-600.0f,350.0f});

	FontRenderer_ = CreateComponent<GameEngineUIRenderer>();
	FontRenderer_->SetTexture("Winner.png");
	FontRenderer_->GetTransform().SetWorldScale({187.0f* 0.7f, 94.0f * 0.7f});
	FontRenderer_->GetTransform().SetWorldRotation({ 0,0,5.0f });
	FontRenderer_->GetTransform().SetWorldPosition({ -600.0f,320.0f });

	CrownRenderer_ = CreateComponent<GameEngineUIRenderer>();
	CrownRenderer_->SetTexture("ui_crown_winner_banner.png");
	CrownRenderer_->GetTransform().SetWorldScale({ 75.0f,56.5f });
	CrownRenderer_->GetTransform().SetWorldRotation({ 0,0,5.0f });
	CrownRenderer_->GetTransform().SetWorldPosition({ -600.0f,420.0f });

	Font_= CreateComponent<GameEngineFontRenderer>();
	Font_->ChangeCamera(CAMERAORDER::UICAMERA);
	Font_->SetSize(40.0f);
	Font_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	Font_->GetTransform().SetWorldRotation({ 0,0,5.0f }); //¾È¸ÔÈû
	Font_->SetScreenPostion({ 190.0f,28.0f });
	Font_->SetText("ÇÃ·¹ÀÌ¾îTest", "Noto Sans CJK SC");
}

void Winner::LevelEndEvent()
{
}
