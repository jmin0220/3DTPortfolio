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


	// InitPhysic는 레벨이 시작될때 실행되므로 LevelStartEvent가 실행되기 전에 포지션을 결정해야함.
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

	//스카이박스
	std::shared_ptr<SkyboxActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->SetSkyTexture("Respawn_SkyBox_S02.png");
	//그외 배경용 static매쉬
	std::shared_ptr<HoopsStageObjects> BackGround_ = CreateActor<HoopsStageObjects>();
	//BackGround_ = CreateActor<DoorDash_BackGroundObject>();
	//BackGround_->GetTransform().SetWorldPosition({ 0,0,0 });
}

void HoopsLegendsLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
