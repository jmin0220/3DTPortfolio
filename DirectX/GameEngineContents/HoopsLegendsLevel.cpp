#include "PreCompile.h"
#include "SkyboxActor.h"
#include "HoopsLegendsLevel.h"
#include "PlayerActor.h"
#include "HoopsStageObjects.h"

#include "HoopsScoreRing.h"
//#include "TestGUI.h"
#include "GameEngineBase/GameEngineRandom.h"
#include "TimerActor.h"
#include "RankingActor.h"

HoopsLegendsLevel::HoopsLegendsLevel() :
	SettingHoops_(false)
	, ServerActivated_(false)
{
}

HoopsLegendsLevel::~HoopsLegendsLevel() 
{
}

void HoopsLegendsLevel::Start()
{
	MyStage_ = StageNum::STAGE5;
	GameScoreType_ = GameScoreType::TIMEATTACK;
	StageParentLevel::Start();

	LightObject_->GetLightData().DifLightPower = 0.5f;
	LightObject_->GetLightData().SpcLightPower = 0.1f;
	LightObject_->GetLightData().AmbLightPower = 7.3f;
	LightObject_->GetTransform().SetWorldRotation({ 299.4f,80.7f,0 });

	//GUI_ = GameEngineGUI::CreateGUIWindow<TestGUI>("MapEditorGUI", this);
	//GUI_->Off();

	

	// InitPhysic는 레벨이 시작될때 실행되므로 LevelStartEvent가 실행되기 전에 포지션을 결정해야함.
	//Player_->GetTransform().SetWorldPosition({ 10.0f, -70.0f, -390.0f });
}

void HoopsLegendsLevel::Update(float _DeltaTime)
{
	StageParentLevel::Update(_DeltaTime);

	if (false == ServerActivated_
		&& true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StagePreviewChangeOver))
	{
		ServerActivated_ = true;
		RankingActor_->On();
	}

	// 이거 서버만 돌려야됨
	if (true == GameServer::GetInst()->IsServerStart())
	{
		if (true == GameServer::IsHost_)
		{
			// 호스트만 실시간 후프위치 조절
			SetHoopPosition();

			// 호스트만 남은시간 조절
			if (true == ServerActivated_)
			{
				TimerLimit_ -= _DeltaTime;
			}

			GameServer::GetInst()->PlayTime_ = static_cast<unsigned int>(TimerLimit_);
			TimerUI_->SetNetTime(TimerLimit_);
		}
		else
		{
			// 클라이언트는 호스트 유저플레이어의 시간 받아와야됨
			std::map<int, std::shared_ptr<class PlayerStatePacket>>& Players = GameServer::GetInst()->GetOtherPlayersInfo();
			
			TimerLimit_ = static_cast<float>(Players[0]->PlayTime);
			TimerUI_->SetNetTime(TimerLimit_);
		}

	}



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
	//GUI_->SetObj(BackGround_);
	//GUI_->On();



	if (true == GameServer::GetInst()->IsServerStart())
	{
		//////////////
		// 서버 ON
		//////////////

		// 1. 플레이어 소환
		unsigned int PositionCount = static_cast<unsigned int>(HoopsStartPos_.size());
		unsigned int PositionIdx = GameServer::GetInst()->PlayerID_;
		if (PositionIdx < PositionCount)
		{
			Player_->SetCheckPoint(HoopsStartPos_[PositionIdx] + float4(0, 0, 0));
			Player_->ResetPlayerPos();
		}
		else
		{
			// ex 플레이어 13명 -> 13 / 6 = 2 ... 1
			// 1은 포지션 리스트의 인덱스, 2는 그 포지션의 3번째(0, 1, 2) 사람
			PositionIdx = PositionIdx % PositionCount;
			int PositionIdxPlus = PositionIdx / PositionCount;

			// 1번째 : 0도 돌림, 2번째 중복 : 20도 돌림, 3번째 중복 : 40도 돌림
			float4 Position = HoopsStartPos_[PositionIdx];
			Position = float4::VectorRotationToDegreeYAxis(Position, PositionIdxPlus * 20.0f);
			Player_->SetCheckPoint(Position);
			Player_->ResetPlayerPos();
		}

		// 2. 호스트는 후프 소환
		if (true == GameServer::GetInst()->IsHost_)
		{
			SpawnHoops();
		}


	}
	else
	{
		//////////////
		// 서버 OFF
		//////////////

		Player_->SetCheckPoint(HoopsStartPos_[0] + float4(0, 0, 0));
		Player_->ResetPlayerPos();
	}

	// 호스트의 시간만 적용됨
	TimerLimit_ = 60.0f;

	RankingActor_ = CreateActor<RankingActor>();
	RankingActor_->Off();
}

void HoopsLegendsLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();

	TimerUI_->Off();

	RankingActor_->Death();
}

bool HoopsLegendsLevel::GameEndingFlag()
{
	// 튕기면 범위지정해서 죽은걸로
	if (Player_->GetTransform().GetWorldPosition().y <= -20.0f)
	{
		return true;
	}

	// 이 레벨은 호스트만 종료 체크 가능

	if (true == GameServer::GetInst()->IsServerStart())
	{
		if (true == GameServer::GetInst()->IsHost_ && true == TimerUI_->IsTimerEnd())
		{
			return true;
		}
		else
		{
			return GameServer::GetInst()->CheckHostFlag(PlayerFlag::P_StageRaceChangeReady);
		}
	}


	return false;
}

void HoopsLegendsLevel::SpawnHoops()
{
	//std::shared_ptr<JumpClub_SpinBarDouble> BarDouble = CreateActor<JumpClub_SpinBarDouble>();
	//BarDouble->ServerInit(ServerObjectType::SpinBarDouble);
	//BarDouble->GetTransform().SetWorldPosition({ 0.0f, 77.0f, 0.0f });
	//BarDouble->PhysXInit();

	for (int i = 0; i < 10; i++)
	{
		Hoops_ = CreateActor<HoopsScoreRing>();

		HoopsActor.push_back(Hoops_);

		PrevPos[i] = -1;
	}


	// 이거도 서버가 해야됨
	//후프 초기위치 설정
	for (int i = 0; i < 10; i++)
	{
		if (PrevPos[i] == -1)
		{
			PrevPos[i] = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(HoopsPos.size() - 1));
			for (int j = 0; j < i; j++)
			{
				if (PrevPos[i] == PrevPos[j])
				{
					PrevPos[i] = -1;
					i--;
					break;
				}
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		HoopsActor[i]->GetTransform().SetWorldPosition(HoopsPos[PrevPos[i]]);

		// 호스트의 서버 초기화
		HoopsActor[i]->CastThis<HoopsScoreRing>()->ServerInit(ServerObjectType::HoopRing);
		HoopsActor[i]->CastThis<HoopsScoreRing>()->PhysXInit();
	}

}

void HoopsLegendsLevel::SetHoopPosition()
{
	for (int i = 0; i < 10; i++)
	{
		if (std::dynamic_pointer_cast<HoopsScoreRing>(HoopsActor[i])->GetRenderer()->IsUpdate() == false)
		{
			PrevPos[i] = -1;
			SettingHoops_ = true;
		}
	}

	if (SettingHoops_ == true)
	{
		for (int i = 0; i < 10; i++)
		{
			if (PrevPos[i] == -1)
			{
				PrevPos[i] = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(HoopsPos.size() - 1));
				Num_ = i;
				for (int j = 0; j < 10; j++)
				{
					if (i == j)
					{
						continue;
					}

					if (PrevPos[i] == PrevPos[j])
					{
						PrevPos[i] = -1;
						i--;
						break;
					}
				}
			}
		}

		float4 Pos = HoopsPos[PrevPos[Num_]];
		Pos.y += 200.0f;
		HoopsActor[Num_]->GetTransform().SetWorldPosition(Pos);
		std::dynamic_pointer_cast<HoopsScoreRing>(HoopsActor[Num_])->SetFlag(); // true
		std::dynamic_pointer_cast<HoopsScoreRing>(HoopsActor[Num_])->SetRenderer(); //true
		std::dynamic_pointer_cast<HoopsScoreRing>(HoopsActor[Num_])->SetPrevPos(HoopsPos[PrevPos[Num_]]);
		 

		SettingHoops_ = false;
	}
}
