#include "PreCompile.h"
#include "FontActor.h"

FontActor::FontActor() 
{
}

FontActor::~FontActor() 
{
}

void FontActor::Start()
{
	Font_ = CreateComponent<GameEngineFontRenderer>();
	Font_->SetSize(35.0f);
	Font_->SetColor({ 1.0f, 1.0f, 1.0f });
	Font_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	Font_->SetText("������ �Է��ϼ���", "Noto Sans CJK SC");
}

void FontActor::Update(float _DeltaTime)
{
}

