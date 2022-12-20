#include "PreCompile.h"
#include "DoorDashLevel.h"

#include "DoorDashStage.h"
#include "PlayerActor.h"
#include "SkyboxActor.h"

#include <GameEngineCore/GameEngineBlur.h>
#include "GameEngineStatusWindow.h"

DoorDashLevel::DoorDashLevel() 
{
}

DoorDashLevel::~DoorDashLevel() 
{
}

void DoorDashLevel::Start()
{

	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	GameEngineStatusWindow::AddDebugRenderTarget("GBuffer", GetMainCamera()->GetCameraDeferredLightRenderTarget());

	//빛
	//{
	//	LightObject = CreateActor<GameEngineLight>();
	//	LightObject->GetTransform().SetWorldRotation({ 0.0f,100.0f, 0.0f });
	//	GetMainCamera()->PushLight(LightObject);
	//	LightObject->GetLightData().DifLightPower = 0.5f;
	//}

	StageParentLevel::Start();
	MyStage_ = StageNum::STAGE1;


	// InitPhysic는 레벨이 시작될때 실행되므로 LevelStartEvent가 실행되기 전에 포지션을 결정해야함.
	//Player_->GetTransform().SetWorldPosition({ 10.0f, -70.0f, -390.0f });
}

void DoorDashLevel::Update(float _DeltaTime)
{
	StageParentLevel::Update(_DeltaTime);
}

void DoorDashLevel::End()
{
	StageParentLevel::End();
}

void DoorDashLevel::LevelStartEvent()
{
	StageParentLevel::LevelStartEvent();

	//Player_->GetDynamicActorComponent()->SetPlayerStartPos(PlayerPos);

	//collision용 매쉬 바닥, 벽 등
	Stage_ = CreateActor<DoorDashStage>();
	Stage_->GetTransform().SetWorldPosition({0, -200, 0});

	//스카이박스
	std::shared_ptr<SkyboxActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->SetSkyTexture("Respawn_SkyBox.png");
	//그외 배경용 static매쉬
	//BackGround_ = CreateActor<DoorDash_BackGroundObject>();
	//BackGround_->GetTransform().SetWorldPosition({ 0,0,0 });

}

void DoorDashLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
