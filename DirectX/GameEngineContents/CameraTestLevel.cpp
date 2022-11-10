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
	
	// 리소스 로드
	ContentsCore::GetInst()->LoadLevelResource(LEVELS::CAMERA_TEST);

	// 엑터 생성
	GameEngineActor* Floor = CreateActor<TestActor_WaterPlane>();
	Actors_.push_back(Floor);

	GameEngineActor* Player = CreateActor<TestActor_Character>();
	Player->GetTransform().SetWorldPosition({ 0, 300, 0 });
	Actors_.push_back(Player);
}

void CameraTestLevel::LevelEndEvent()
{
	// 엑터 제거
	for (GameEngineActor* Actor : Actors_)
	{
		Actor->Death();
	}

	// 리소스 해제
	ContentsCore::GetInst()->ReleaseCurLevelResource();

}

