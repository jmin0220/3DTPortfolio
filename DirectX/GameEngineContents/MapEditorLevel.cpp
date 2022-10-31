#include "PreCompile.h"
#include "MapEditorLevel.h"
#include <GameEngineCore/CoreMinimal.h>

#include "MapEditorGUI.h"
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

	GUI = GameEngineGUI::CreateGUIWindow<MapEditorGUI>("MapEditorGUI", this);
	GUI->Off();
}

void MapEditorLevel::Update(float _DeltaTime)
{
}

void MapEditorLevel::End()
{
}

void MapEditorLevel::LevelStartEvent()
{
	GUI->On();
}

void MapEditorLevel::LevelEndEvent()
{
	GUI->Off();
}

