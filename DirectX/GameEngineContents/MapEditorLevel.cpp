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
	GUI_ = GameEngineGUI::CreateGUIWindow<MapEditorGUI>("MapEditorGUI", this);
	GUI_->Off();


}

void MapEditorLevel::Update(float _DeltaTime)
{
}

void MapEditorLevel::End()
{
}

void MapEditorLevel::LevelStartEvent()
{
	GUI_->On();

	// ���ҽ� �ε�
	ContentsCore::GetInst()->LoadLevelResource(LEVELS::MAP_EDITOR);

	// ���� ����
	std::shared_ptr<GameEngineActor> Picker = CreateActor<ActorPicker>();

	std::shared_ptr<AxisActorRot> AxisRot = CreateActor<AxisActorRot>();
	AxisRot->SetPosition();
	AxisRot->GetTransform().SetWorldPosition({ 300.0f,0,0 });

	// �׽�Ʈ�� ����(���� �����ؾ���)
	std::shared_ptr<GameEngineActor> RainBow = CreateActor<TestRainBow>();
	RainBow->GetTransform().SetWorldPosition({ -200,0,0 });
	Actors_.push_back(RainBow);

	std::shared_ptr<GameEngineActor> RainBow2 = CreateActor<TestRainBow>();
	RainBow2->GetTransform().SetWorldPosition({ -200, 200,0 });
	Actors_.push_back(RainBow2);

	std::shared_ptr<GameEngineActor> TestMap = CreateActor<TestMapActor>();
	TestMap->GetTransform().SetWorldPosition({ 0,0,0 });
	Actors_.push_back(TestMap);

}

void MapEditorLevel::LevelEndEvent()
{
	GUI_->Off();

	// ���� ����
	for (std::shared_ptr<GameEngineActor> Actor : Actors_)
	{
		Actor->Death();
	}

	// ���ҽ� ����
	ContentsCore::GetInst()->ReleaseCurLevelResource();
}

