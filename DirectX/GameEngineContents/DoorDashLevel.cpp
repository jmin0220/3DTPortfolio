#include "PreCompile.h"
#include "DoorDashLevel.h"

#include "DoorDashStage.h"
#include "PlayerActor.h"
#include "SkyboxActor.h"

#include <GameEngineCore/GameEngineBlur.h>
#include "GameEngineStatusWindow.h"
#include "Col_Goal.h"

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
	GameScoreType_ = GameScoreType::RACE;

	LightObject_->GetLightData().DifLightPower = 0.7f;
	LightObject_->GetLightData().AmbLightPower = 8.3f;
	LightObject_->GetTransform().SetWorldRotation({ 93.4f,147.7f,0 });

	// InitPhysic�� ������ ���۵ɶ� ����ǹǷ� LevelStartEvent�� ����Ǳ� ���� �������� �����ؾ���.
	//Player_->GetTransform().SetWorldPosition({ 10.0f, -70.0f, -390.0f });
}

void DoorDashLevel::Update(float _DeltaTime)
{
	StageParentLevel::Update(_DeltaTime);

	if (Player_->GetTransform().GetWorldPosition().y <= -200.0f)
	{
		Player_->ResetPlayerPos();
	}

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


	int PlayerID = GameServer::GetInst()->PlayerID_;
	Player_->SetCheckPoint(PlayerPos + float4{ PlayerID * 20.0f, 0, 0 });
	Player_->ResetPlayerPos();

}

void DoorDashLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}

bool DoorDashLevel::GameEndingFlag()
{
	if (Col_Goal::GetIsPlayerGoal_()==true)
	{
		Col_Goal::SetIsPlayerGoal(); //false
		return true;
	}


	return false;
}
