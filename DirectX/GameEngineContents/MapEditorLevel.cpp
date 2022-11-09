#include "PreCompile.h"
#include "MapEditorLevel.h"
#include <GameEngineCore/CoreMinimal.h>

#include "AxisActor.h"
#include "AxisActorRot.h"
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
		//GameEngineActor* Box = CreateActor<ColorBox>();
		//Box->GetTransform().SetWorldPosition({ 0, 0, 300 });

		ActorPicker* Picker = CreateActor<ActorPicker>();
	}



	{
		TestRainBow* RainBow = CreateActor<TestRainBow>();
		RainBow->GetTransform().SetWorldPosition({ -200,0,0 });

		TestRainBow* RainBow2 = CreateActor<TestRainBow>();
		RainBow2->GetTransform().SetWorldPosition({ -200, 200,0 });
	}


	{
		TestMapActor* TestMap = CreateActor<TestMapActor>();
		TestMap->GetTransform().SetWorldPosition({ 0,0,0 });
	}


	{
		AxisActorRot* AxisRot = CreateActor<AxisActorRot>();
		AxisRot->SetPosition();
		AxisRot->GetTransform().SetWorldPosition({ 300.0f,0,0 });


	}


	//{
	//	AxisActor* Axis = CreateActor<AxisActor>();
	//	Axis->GetTransform().SetWorldPosition({ 200,0,0 });
	//	Axis->SetPosition();
	//}

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

