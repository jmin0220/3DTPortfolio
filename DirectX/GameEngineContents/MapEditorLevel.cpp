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

	// 리소스 로드
	ContentsCore::GetInst()->LoadLevelResource(LEVELS::MAP_EDITOR);

	// 엑터 생성
	std::shared_ptr<GameEngineActor> Picker = CreateActor<ActorPicker>();

	//std::shared_ptr<TestMapActor> TestMap = CreateActor<TestMapActor>();
	
	//std::shared_ptr<PickableActor> act = CreateActor<PickableActor>();
	//act->SetStaticMesh("Rainbow.FBX");

	// 트리거용 콜리전만 따로 생성
	//std::shared_ptr<PickableActor> CollisionOnly = CreateActor<PickableActor>();
	//CollisionOnly->SetCollisionOnly(float4(700, 700, 700));

	
}

void MapEditorLevel::LevelEndEvent()
{
	GUI_->Off();

	// 리소스 해제
	ContentsCore::GetInst()->ReleaseCurLevelResource();
}

