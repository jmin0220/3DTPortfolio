#include "PreCompile.h"
#include "DoorDashLevel.h"

#include "DoorDashStage.h"
#include "DoorDash_BackGroundObject.h"
#include "PlayerActor.h"
#include "SkyboxActor.h"

DoorDashLevel::DoorDashLevel() 
{
}

DoorDashLevel::~DoorDashLevel() 
{
}

void DoorDashLevel::Start()
{
	StageParentLevel::Start();
	MyStage_ = StageNum::STAGE1;
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

	std::shared_ptr<PlayerActor> Player = CreateActor<PlayerActor>();
	Player->CreatePhysXActors(GetScene(), GetPhysics());
	Player->GetTransform().SetWorldPosition({ 30.0f,50.0f,0 });
	//collision용 매쉬 바닥, 벽 등
	Stage_ = CreateActor<DoorDashStage>();
	Stage_->GetTransform().SetWorldPosition({0, -200, 0});

	//스카이박스
	std::shared_ptr<SkyboxActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->SetSkyTexture("Respawn_SkyBox_S02.png");
	//그외 배경용 static매쉬
	//BackGround_ = CreateActor<DoorDash_BackGroundObject>();
	//BackGround_->GetTransform().SetWorldPosition({ 0,0,0 });
}

void DoorDashLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
