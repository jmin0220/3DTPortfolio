#include "PreCompile.h"
#include "SkyboxActor.h"
#include "HoopsLegendsLevel.h"

#include "HoopsStageObjects.h"

HoopsLegendsLevel::HoopsLegendsLevel() 
{
}

HoopsLegendsLevel::~HoopsLegendsLevel() 
{
}

void HoopsLegendsLevel::Start()
{
	StageParentLevel::Start();
	MyStage_ = StageNum::STAGE5;


	// InitPhysic�� ������ ���۵ɶ� ����ǹǷ� LevelStartEvent�� ����Ǳ� ���� �������� �����ؾ���.
	//Player_->GetTransform().SetWorldPosition({ 10.0f, -70.0f, -390.0f });
}

void HoopsLegendsLevel::Update(float _DeltaTime)
{
	StageParentLevel::Update(_DeltaTime);
}

void HoopsLegendsLevel::End()
{
	StageParentLevel::End();
}

void HoopsLegendsLevel::LevelStartEvent()
{
	StageParentLevel::LevelStartEvent();

	//��ī�̹ڽ�
	std::shared_ptr<SkyboxActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->SetSkyTexture("Respawn_SkyBox_S02.png");
	//�׿� ���� static�Ž�
	std::shared_ptr<HoopsStageObjects> BackGround_ = CreateActor<HoopsStageObjects>();
	//BackGround_ = CreateActor<DoorDash_BackGroundObject>();
	//BackGround_->GetTransform().SetWorldPosition({ 0,0,0 });
}

void HoopsLegendsLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
