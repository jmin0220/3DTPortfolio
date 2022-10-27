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
	Font = CreateComponent<GameEngineFontRenderer>();
	Font->SetSize(35.0f);
	Font->SetColor({ 1.0f, 1.0f, 1.0f });
	Font->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	Font->SetText("제목을 입력하세요", "Noto Sans CJK SC");
}

void FontActor::Update(float _DeltaTime)
{
}

