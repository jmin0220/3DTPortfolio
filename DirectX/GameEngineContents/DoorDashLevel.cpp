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

	//��
	//{
	//	LightObject = CreateActor<GameEngineLight>();
	//	LightObject->GetTransform().SetWorldRotation({ 0.0f,100.0f, 0.0f });
	//	GetMainCamera()->PushLight(LightObject);
	//	LightObject->GetLightData().DifLightPower = 0.5f;
	//}

	StageParentLevel::Start();
	MyStage_ = StageNum::STAGE1;


	// InitPhysic�� ������ ���۵ɶ� ����ǹǷ� LevelStartEvent�� ����Ǳ� ���� �������� �����ؾ���.
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

	//collision�� �Ž� �ٴ�, �� ��
	Stage_ = CreateActor<DoorDashStage>();
	Stage_->GetTransform().SetWorldPosition({0, -200, 0});

	//��ī�̹ڽ�
	std::shared_ptr<SkyboxActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->SetSkyTexture("Respawn_SkyBox.png");
	//�׿� ���� static�Ž�
	//BackGround_ = CreateActor<DoorDash_BackGroundObject>();
	//BackGround_->GetTransform().SetWorldPosition({ 0,0,0 });

}

void DoorDashLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
