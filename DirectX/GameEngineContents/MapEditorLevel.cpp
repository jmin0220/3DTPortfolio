#include "PreCompile.h"
#include "MapEditorLevel.h"
#include <GameEngineCore/CoreMinimal.h>

#include "AxisActor.h"
#include "XAxis.h"
#include "YAxis.h"
#include "ZAxis.h"
#include "TestRainBow.h"
#include "TestMapActor.h"


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



	//{
	//	TestRainBow* RainBow = CreateActor<TestRainBow>();
	//	RainBow->GetTransform().SetWorldPosition({ -200.0f,0,0 });

	//}


	//{
	//	TestMapActor* TestMap = CreateActor<TestMapActor>();
	//	TestMap->GetTransform().SetWorldPosition({ 0,0,0 });
	//}

	{
		AxisActor* Axis = CreateActor<AxisActor>();
		Axis->GetTransform().SetWorldPosition({ 300.0f,0,300.0f });
		Axis->SetPosition();
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

