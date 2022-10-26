#include "PreCompile.h"
#include "MapEditorLevel.h"
#include <GameEngineCore/CoreMinimal.h>

#include "ColorBox.h"
#include "ActorPicker.h"

MapEditorLevel::MapEditorLevel() 
{
}

MapEditorLevel::~MapEditorLevel() 
{
}

void MapEditorLevel::Start()
{
	// 피킹 예시
	{
		GameEngineActor* Box = CreateActor<ColorBox>();
		Box->GetTransform().SetWorldPosition({ 0, 0, 300 });

		ActorPicker* Picker = CreateActor<ActorPicker>();
	}
}

void MapEditorLevel::Update(float _DeltaTime)
{
}

void MapEditorLevel::End()
{
}
