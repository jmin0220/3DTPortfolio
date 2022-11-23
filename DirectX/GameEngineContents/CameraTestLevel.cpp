#include "PreCompile.h"
#include "CameraTestLevel.h"
#include <GameEngineCore/CoreMinimal.h>

#include "TestActor_WaterPlane.h"
#include "TestActor_Character.h"
#include "TestActor_FogBox.h"
#include "SkyboxActor.h"

#include "PostEffect_Bloom.h"

CameraTestLevel::CameraTestLevel() 
{
}

CameraTestLevel::~CameraTestLevel() 
{
}

void CameraTestLevel::Start()
{
	//if (false == GetMainCameraActor()->IsFreeCameraMode())
	//{
	//	GetMainCameraActor()->FreeCameraModeOnOff();
	//	GetMainCameraActor()->GetTransform().SetWorldMove({ 0, 200, -3000 });
	//}

	//std::shared_ptr<PostEffect_Bloom> Ptr = GetMainCamera()->GetCameraRenderTarget()->AddEffect<PostEffect_Bloom>();
	//Ptr->On();

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
	



	// 府家胶 肺靛
	ContentsCore::GetInst()->LoadLevelResource(LEVELS::CAMERA_TEST);

	// 竣磐 积己
	std::shared_ptr<GameEngineActor> Floor = CreateActor<TestActor_WaterPlane>();
	Floor->GetTransform().SetWorldPosition({ 0, -2000, 0 });

	std::shared_ptr<GameEngineActor> Player = CreateActor<TestActor_Character>();
	Player->GetTransform().SetWorldPosition({ 0, 0, 0 });

	std::shared_ptr<GameEngineActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->GetTransform().SetWorldScale({ 100, 100, 100 });

	std::shared_ptr<GameEngineActor> FogBox = CreateActor<TestActor_FogBox>();
	FogBox->GetTransform().SetWorldPosition({ 0, -2000, 200 });

	Actors_.push_back(Player);
	
}

void CameraTestLevel::LevelEndEvent()
{
	for (std::shared_ptr<GameEngineActor> Ptr : Actors_)
	{
		Ptr->Death();
	}

	// 府家胶 秦力
	ContentsCore::GetInst()->ReleaseCurLevelResource();

}

