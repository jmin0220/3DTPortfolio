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

	// 府家胶 肺靛
	ContentsCore::GetInst()->LoadLevelResource(LEVELS::MAP_EDITOR);

	// 竣磐 积己
	std::shared_ptr<GameEngineActor> Picker = CreateActor<ActorPicker>();
	
}

void MapEditorLevel::LevelEndEvent()
{
	GUI_->Off();

	// 府家胶 秦力
	ContentsCore::GetInst()->ReleaseCurLevelResource();
}

