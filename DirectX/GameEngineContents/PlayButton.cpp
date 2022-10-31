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
	Button = CreateComponent<GameEngineUIRenderer>();
	Button->SetTexture("Play.png");
	Button->GetTransform().SetWorldScale({ 350, 110});
	Button->GetTransform().SetWorldPosition({ 600,-380 });

	Key = CreateComponent<GameEngineUIRenderer>();
	Key->SetTexture("Spacebar.png");
	Key->GetTransform().SetWorldScale({ 114 * 0.5f, 55 * 0.5f });
	Key->GetTransform().SetWorldPosition({ 600,-420 });

	Font = CreateComponent<GameEngineFontRenderer>();
	Font->ChangeCamera(CAMERAORDER::UICAMERA);
	Font->SetText("ÇÃ·¹ÀÌ", "Noto Sans CJK SC");
	Font->SetSize(25.0f);
	Font->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	Font->SetScreenPostion({ 1400,805 });
}

void PlayButton::Update(float _DeltaTime)
{
}

