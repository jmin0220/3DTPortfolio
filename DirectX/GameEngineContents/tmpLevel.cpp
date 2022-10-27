#include "PreCompile.h"
#include "tmpLevel.h"
#include "TitleActor.h"
#include "Cursor.h"

tmpLevel::tmpLevel() 
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
	
}

void tmpLevel::Update(float _DeltaTime)
{
}

void tmpLevel::End()
{
}
