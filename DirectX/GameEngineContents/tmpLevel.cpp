#include "PreCompile.h"
#include "tmpLevel.h"
#include "TitleActor.h"
#include "Cursor.h"
#include <GameEngineCore/GameEngineActor.h>
#include "FontActor.h"

tmpLevel::tmpLevel() 
	:Font(nullptr)
{
}

tmpLevel::~tmpLevel() 
{
}

void tmpLevel::Start()
{
	TitleLogo = CreateActor<TitleActor>();
	TitleLogo->GetTransform().SetLocalPosition({ 800,-450 });
	TitleLogo->GetTransform().SetLocalPosition({ -400 + 418, 225 - 143 });

	Mouse = CreateActor<Cursor>();

	Font = CreateActor<FontActor>();
	Font->GetFont()->SetText("½ÃÀÛ!", "Noto Sans CJK SC");
	Font->GetFont()->SetScreenPostion({ 825,700 });
}

void tmpLevel::Update(float _DeltaTime)
{
}

void tmpLevel::End()
{
}
