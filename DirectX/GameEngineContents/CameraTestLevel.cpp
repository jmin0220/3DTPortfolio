#include "PreCompile.h"
#include "CameraTestLevel.h"
#include <GameEngineCore/CoreMinimal.h>

#include "TestActor_WaterPlane.h"
#include "TestActor_Character.h"

CameraTestLevel::CameraTestLevel() 
{
}

CameraTestLevel::~CameraTestLevel() 
{
}

void CameraTestLevel::Start()
{
	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
		GetMainCameraActor()->GetTransform().SetWorldMove({ 0, 200, -3000 });
	}




}

void CameraTestLevel::Update(float _DeltaTime)
{

}

void CameraTestLevel::End()
{
}

void CameraTestLevel::LevelStartEvent()
{	
	GEngine::CollisionDebugOff();
	
	// ���ҽ� �ε�
	ContentsCore::GetInst()->LoadLevelResource(LEVELS::CAMERA_TEST);

	// ���� ����
	GameEngineActor* Floor = CreateActor<TestActor_WaterPlane>();
	Actors_.push_back(Floor);

	GameEngineActor* Player = CreateActor<TestActor_Character>();
	Player->GetTransform().SetWorldPosition({ 0, 300, 0 });
	Actors_.push_back(Player);
}

void CameraTestLevel::LevelEndEvent()
{
	// ���� ����
	for (GameEngineActor* Actor : Actors_)
	{
		Actor->Death();
	}

	// ���ҽ� ����
	ContentsCore::GetInst()->ReleaseCurLevelResource();

}

