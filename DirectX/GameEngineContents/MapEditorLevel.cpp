#include "PreCompile.h"
#include "MapEditorLevel.h"
#include <GameEngineCore/CoreMinimal.h>

#include "TestRainBow.h"
#include "TestMapActor.h"

#include "MapEditorGUI.h"
#include "ColorBox.h"
#include "ActorPicker.h"
#include "ActorAxis.h"

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
	GUI_->ReleaseResources();
}

void MapEditorLevel::LevelStartEvent()
{
	GUI_->On();

	// ���ҽ� �ε�
	ContentsCore::GetInst()->LoadLevelResource(LEVELS::MAP_EDITOR);

	// ���� ����
	std::shared_ptr<GameEngineActor> Picker = CreateActor<ActorPicker>();

	//std::shared_ptr<TestMapActor> TestMap = CreateActor<TestMapActor>();
	
	//std::shared_ptr<PickableActor> act = CreateActor<PickableActor>();
	//act->SetStaticMesh("Rainbow.FBX");

	std::shared_ptr<PickableActor> CollisionOnly = CreateActor<PickableActor>();
	CollisionOnly->SetCollisionOnly(float4(700, 700, 700));

	
}

void MapEditorLevel::LevelEndEvent()
{
	GUI_->Off();

	// ���ҽ� ����
	ContentsCore::GetInst()->ReleaseCurLevelResource();
}

