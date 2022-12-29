#include "PreCompile.h"
#include "JumpClubLevel.h"

// 오브젝트 액터
#include "SkyboxActor.h"
#include "JumpClub_BackGroundObject.h"
#include "VFXWaterActor.h"
#include "JumpClubStage.h"
#include "JumpClub_SpinBarDouble.h"
#include "JumpClub_SpinBarSingle.h"

#include "PlayerActor.h"

#include "PostEffect_Bloom.h"

#include "InGameSetUI.h"

JumpClubLevel::JumpClubLevel() 
{
}

JumpClubLevel::~JumpClubLevel() 
{
}

void JumpClubLevel::Start()
{
	MyStage_ = StageNum::STAGE2;
	GameScoreType_ = GameScoreType::SURVIVAL;
	StageParentLevel::Start();


	std::shared_ptr<PostEffect_Bloom> Ptr = GetMainCamera()->GetCameraRenderTarget()->AddEffect<PostEffect_Bloom>();
	Ptr->Off();
}

void JumpClubLevel::Update(float _DeltaTime)
{
	StageParentLevel::Update(_DeltaTime);

}

void JumpClubLevel::End()
{
	StageParentLevel::End();
}

void JumpClubLevel::LevelStartEvent()
{
	StageParentLevel::LevelStartEvent();
	
	LightObject_->GetLightData().AmbientLight = float4{ 0.7f,0.7f,0.7f,1.0f };
	LightObject_->GetLightData().DifLightPower = 0.5f;
	LightObject_->GetLightData().SpcLightPower = 1.0f;
	LightObject_->GetLightData().AmbLightPower = 1.0f;
	LightObject_->GetTransform().SetWorldRotation({ 260.0f,230.0f,0.0f });

	BackGroundObj_ = CreateActor<JumpClub_BackGroundObject>();
	VFXWaterObj_ = CreateActor<VFXWaterActor>();

	UIs_ = CreateActor<InGameSetUI>();

	Player_->GetTransform().SetWorldPosition({ 0.0f,200.0f,0.0f });

	std::shared_ptr<JumpClubStage> Stage = CreateActor<JumpClubStage>();
	Stage->GetTransform().SetWorldPosition({ 0.0f, 65.0f, 0.0f });

	// Bar Y축 조정 필요
	// 호스트 : 생성하고 서버초기화
	// 유저 : 패킷받아서생성, 움직임은 서버 패킷받아서 움직임
	
	// 서버 안키고 디버깅 할 때
	{
		if (false == GameServer::GetInst()->IsServerStart())
		{
			std::shared_ptr<JumpClub_SpinBarDouble> BarDouble = CreateActor<JumpClub_SpinBarDouble>();
			BarDouble->GetTransform().SetWorldPosition({ 0.0f, 77.0f, 0.0f });
			BarDouble->PhysXInit();


			std::shared_ptr<JumpClub_SpinBarSingle> BarSingle = CreateActor<JumpClub_SpinBarSingle>();
			BarSingle->GetTransform().SetWorldPosition({ 0.0f, 62.0f, 0.0f });
			BarSingle->PhysXInit();
		}
	}


	if (true == GameServer::IsHost_)
	{
		std::shared_ptr<JumpClub_SpinBarDouble> BarDouble = CreateActor<JumpClub_SpinBarDouble>();
		BarDouble->ServerInit(ServerObjectType::SpinBarDouble);
		BarDouble->GetTransform().SetWorldPosition({ 0.0f, 77.0f, 0.0f });
		BarDouble->PhysXInit();


		std::shared_ptr<JumpClub_SpinBarSingle> BarSingle = CreateActor<JumpClub_SpinBarSingle>();
		BarSingle->ServerInit(ServerObjectType::SpinBarSingle);
		BarSingle->GetTransform().SetWorldPosition({ 0.0f, 62.0f, 0.0f });
		BarSingle->PhysXInit();
	}


	std::shared_ptr<SkyboxActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->SetSkyTexture("S5_SkyBox_Respawn.png");

	// 플레이어 스폰위치 조정
	// 위치 6개임

	if (true == GameServer::GetInst()->IsServerStart())
	{
		unsigned int PositionIdx = GameServer::GetInst()->PlayerID_;

		if (PositionIdx < 6)
		{
			Player_->SetCheckPoint(StartPositions_[PositionIdx] + float4(0, 0, 0));
			Player_->ResetPlayerPos();
		}
		else
		{
			// ex 플레이어 13명 -> 13 / 6 = 2 ... 1
			// 1은 포지션 리스트의 인덱스, 2는 그 포지션의 3번째(0, 1, 2) 사람
			PositionIdx = PositionIdx % 6;
			int PositionIdxPlus = PositionIdx / 6;

			// 1번째 : 0도 돌림, 2번째 중복 : 20도 돌림, 3번째 중복 : 40도 돌림
			float4 Position = StartPositions_[PositionIdx];
			Position = float4::VectorRotationToDegreeYAxis(Position, PositionIdxPlus * 20.0f);
			Player_->SetCheckPoint(Position);
			Player_->ResetPlayerPos();
		}
	}
	else
	{
		Player_->SetCheckPoint(StartPositions_[0] + float4(0, 0, 0));
		Player_->ResetPlayerPos();
	}

	TimerLimit_ = 120.0f;

}

void JumpClubLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}



bool JumpClubLevel::GameEndingFlag()
{
	if (Player_->GetTransform().GetWorldPosition().y <= -20.0f)
	{
		return true;
	}
	// 다른 모든 플레이어 죽었으면
	else if (GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StageRaceChangeReady))
	{
		Player_->SetGoal(true);
		return true;
	}

	return false;
}
