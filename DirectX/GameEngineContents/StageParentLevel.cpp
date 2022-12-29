#include "PreCompile.h"
#include "StageParentLevel.h"
#include "TestRainBow.h"

//load objects
#include "DoorBlock.h"
#include "TestMapActor.h"
#include "Col_StartPos.h"
#include "Col_Trigger.h"
#include "MovingBar.h"
#include "Chevron.h"
#include "HexProPeller.h"
#include "JumboTron.h"
#include "Col_Goal.h"
#include "Col_CheckPoint.h"
#include "HoopsWoodPlank.h"
#include "HoopsScythe.h"
#include "HoopsBox.h"
#include "HoopsRamp.h"
#include "HoopsScoreRing.h"
#include "JumpClub_SpinBarDouble.h"
#include "JumpClub_SpinBarSingle.h"
#include "BigShots_Cannon.h"
#include "BigShots_Spinner.h"

#include <GameEngineBase/magic_enum.hpp>
#include <GameEngineCore/ThirdParty/inc/json.h>
#include <GameEngineCore/CoreMinimal.h>
#include <iostream>
#include <fstream>
#include "InGameSetUI.h"
#include "PlayerActor.h"
#include "IntroduceGame.h"
#include "LoadingLevel.h"
#include <atomic>

#include <GameEngineCore/GameEngineBlur.h>

#include "TestGUI.h"
#include "TimerActor.h"
#include "HoopsScoreRing.h"


std::mutex SpawnLock;

float4 StageParentLevel::PlayerPos = float4::ZERO;
std::vector<float4> StageParentLevel::HoopsPos = std::vector<float4>();
std::vector<std::shared_ptr<GameEngineActor>> StageParentLevel::HoopsActor = std::vector<std::shared_ptr<GameEngineActor>>();

StageParentLevel::StageParentLevel() 
	: MyStage_(StageNum::STAGE1)
	, GameScoreType_(GameScoreType::NONE)
	, WatchCamIdx(0)
	, TimerLimit_(0.0f)
{
	CinemaCam_ = std::make_shared<Cinemachine>();
}

StageParentLevel::~StageParentLevel() 
{
}

void StageParentLevel::Start()
{
	VirtualPhysXLevel::Start();
	CinemaCam_->SetStage(MyStage_);
	CinemaCam_->Init(GetMainCameraActor());

	GUI_ = GameEngineGUI::CreateGUIWindow<TestGUI>("StageGUI", this);
	GUI_->Off();

	{
		LightObject_ = CreateActor<GameEngineLight>();
		LightObject_->GetTransform().SetWorldPosition({ 0, 0, 0 });
		GUI_->SetLight(LightObject_);
		GetMainCamera()->PushLight(LightObject_);
	}

	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	//GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();


	IntroduceGame_ = CreateActor<IntroduceGame>();
	IntroduceGame_->Off();

	UIs_ = CreateActor<InGameSetUI>();
	UIs_->Off();

	TimerUI_ = CreateActor<TimerActor>();
	TimerUI_->Off();

	// 스테이지 FSM
	StageStateManager_.CreateStateMember("Idle"
		, std::bind(&StageParentLevel::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&StageParentLevel::IdleStart, this, std::placeholders::_1));

	StageStateManager_.CreateStateMember("StagePreview"
		, std::bind(&StageParentLevel::StagePreviewUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&StageParentLevel::StagePreviewStart, this, std::placeholders::_1));

	StageStateManager_.CreateStateMember("Ready"
		, std::bind(&StageParentLevel::ReadyUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&StageParentLevel::ReadyStart, this, std::placeholders::_1));

	StageStateManager_.CreateStateMember("Race"
		, std::bind(&StageParentLevel::RaceUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&StageParentLevel::RaceStart, this, std::placeholders::_1));

	StageStateManager_.CreateStateMember("End"
		, std::bind(&StageParentLevel::EndUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&StageParentLevel::EndStart, this, std::placeholders::_1));

}

void StageParentLevel::Update(float _DeltaTime)
{
	// PhysX업데이트
	VirtualPhysXLevel::Update(_DeltaTime);

	SpawnServerObjects();

	CinemaCam_->Update();

	// 게임 종료 조건을 체크

	if (true == GameEndingFlag())
	{
		Player_->SetGoal(true);
	}
	
	StageStateManager_.Update(_DeltaTime);

	// 점수추가
	if (true == GameEngineInput::GetInst()->IsDown("P"))
	{
		GameServer::GetInst()->PlayerScore_ += 100;
	}

}
void StageParentLevel::End()
{
	VirtualPhysXLevel::End();
}

void StageParentLevel::LevelStartEvent()
{
	if (true == GameServer::GetInst()->IsServerStart())
	{
		GUI_->Off();
	}
	else
	{
		GUI_->On();
	}
	VirtualPhysXLevel::LevelStartEvent();
	LevelStartLoad();

	// 자신의 메인 플레이어 생성
	PlayerActor::IsMainPlayerSpawned_ = false;
	Player_ = CreateActor<PlayerActor>();


	if (true == GameServer::GetInst()->IsServerStart())
	{
		GameServerObject::PlayersCount = GameServer::GetInst()->GetAllPlayersCount();

		/*if (true == GameServer::IsHost_)
		{
			Player_->ClientInit(ServerObjectType::Player, GameServer::GetInst()->PlayerID_);
		}
		else
		{
			Player_->ClientInit
		}*/

		Player_->ClientInit(ServerObjectType::Player, GameServer::GetInst()->PlayerID_);
	}

	Player_->PlayerInit();

	//후프레벨 위치 임시
	if (MyStage_ == StageNum::STAGE4)
	{
		//Player_->GetTransform().SetWorldPosition({ 0,500.0f,0 });
	}
	else if (MyStage_ == StageNum::STAGE5)
	{
		Player_->GetTransform().SetWorldPosition({ 0,150.0f,0 });
	}


	UIs_->On();

	MainCam_ = GetMainCameraActor();
	CameraArm_ = CreateActor<CameraArm>();

	StageStateManager_.ChangeState("Idle");
}

void StageParentLevel::LevelEndEvent()
{
	VirtualPhysXLevel::LevelEndEvent();
	//ContentsCore::GetInst()->ReleaseCurLevelResource();

	GameServerObject::ServerRelease();

	Player_->Death();

	CameraArm_->Death();
	

	for (StageObject StageObj : StageObjects_)
	{
		StageObj.Actor_.lock()->Death();
	}

	for (std::shared_ptr<GameEngineActor> NetPlayer : NetPlayers_)
	{
		NetPlayer->Death();
	}

	for (std::shared_ptr<GameEngineActor> NetObstacle : NetObstacles_)
	{
		NetObstacle->Death();
	}

}

void StageParentLevel::LevelStartLoad()
{
	GameEngineDirectory LoadDir;
	LoadDir.MoveParentToExitsChildDirectory(DIR_RESOURCES);
	LoadDir.Move(DIR_RESOURCES);
	LoadDir.Move(DIR_JSONTEST);

	std::string LoadPath(LoadDir.GetFullPath());
	std::string CurStageName;
	switch (MyStage_)
	{
	case StageNum::STAGE1:
	{
		CurStageName = JSON_NAME_DOORDASH;
		break;
	}
	case StageNum::STAGE2:
		CurStageName = JSON_NAME_JUMPCLUB;
		break;
	case StageNum::STAGE3:
		CurStageName = JSON_NAME_BIGSHOTS;
		break;
	case StageNum::STAGE4:
		CurStageName = JSON_NAME_HEXAGONE;
		break;
	case StageNum::STAGE5:
		CurStageName = JSON_NAME_HOOPSLEGENDS;
		break;
	default:
		break;
	}
	
	std::ifstream json_dir(LoadPath + CurStageName);

	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	Json::Value value;

	JSONCPP_STRING errs;
	bool ok = parseFromStream(builder, json_dir, &value, &errs);
	if (ok == false)
	{
		return;
	}

	int j = 0;
	while (Json::nullValue != value["Object" + std::to_string(j)])
	{
		Json::Value Mesh = value["Object" + std::to_string(j)]["Mesh"];

		float4 Pos = { Mesh["Transform"]["Pos"][0].asFloat() , Mesh["Transform"]["Pos"][1].asFloat() , Mesh["Transform"]["Pos"][2].asFloat(), Mesh["Transform"]["Pos"][3].asFloat() };
		float4 Size = { Mesh["Transform"]["Size"][0].asFloat() , Mesh["Transform"]["Size"][1].asFloat() , Mesh["Transform"]["Size"][2].asFloat(), Mesh["Transform"]["Size"][3].asFloat() };
		float4 Rot = { Mesh["Transform"]["Rot"][0].asFloat() , Mesh["Transform"]["Rot"][1].asFloat() , Mesh["Transform"]["Rot"][2].asFloat(), Mesh["Transform"]["Rot"][3].asFloat() };

		StageObject NewObj;
		NewObj.Name_ = Mesh["Name"].asCString();

		//NewObj.Dir_ = FBXFiles_[FileIdx].GetFullPath();
		//NewObj.Actor_ = ConnectedLevel->CreateActor<ColorBox>();

		std::map<std::string, Stage_MeshEnum> MeshEnumMap_;
		Stage_MeshEnum tmpEnum = Stage_MeshEnum::START;

		for (int i = 0; i < static_cast<int>(Stage_MeshEnum::END); i++)
		{
			std::string tmp = magic_enum::enum_name(tmpEnum).data();
			MeshEnumMap_[tmp] = (Stage_MeshEnum)i;
			tmpEnum = (Stage_MeshEnum)((int)tmpEnum + 1);
		}

		switch ((*MeshEnumMap_.find(NewObj.Name_)).second)
		{
		case Stage_MeshEnum::START:
		{
			int a = 0;
			break;
		}
		case Stage_MeshEnum::S04Chevron_low1_TopRotater_low_MainTriRotater2_low:
		{
			NewObj.Actor_ = CreateActor<BigShots_Spinner>();
			break;
		}
		case Stage_MeshEnum::HexAGoneMap:
		{
			NewObj.Actor_ = CreateActor<TestMapActor>();
			break;
		}
		case Stage_MeshEnum::HexTile:
		{
			NewObj.Actor_ = CreateActor<TestRainBow>();
			break;
		}
		case Stage_MeshEnum::HexProPeller:
		{
			NewObj.Actor_ = CreateActor<HexProPeller>();
			std::dynamic_pointer_cast<HexProPeller>(NewObj.Actor_.lock())->SetMesh("HexProPeller.FBX");
			break;
		}
		case Stage_MeshEnum::JumboTronProPeller:
		{
			NewObj.Actor_ = CreateActor<HexProPeller>();
			std::shared_ptr<HexProPeller> Act = std::dynamic_pointer_cast<HexProPeller>(NewObj.Actor_.lock());
			Act->SetMesh("JumboTronProPeller.FBX");
			Act->SetJumboNum(Act->GetNum());
			Act->AddNum();
			break;
		}
		case Stage_MeshEnum::JumboTron1:
		{
			NewObj.Actor_ = CreateActor<JumboTron>();
			std::dynamic_pointer_cast<JumboTron>(NewObj.Actor_.lock())->SetMesh("JumboTron1.FBX");
			break;
		}
		case Stage_MeshEnum::JumboTron2:
		{
			NewObj.Actor_ = CreateActor<JumboTron>();
			std::dynamic_pointer_cast<JumboTron>(NewObj.Actor_.lock())->SetMesh("JumboTron2.FBX");
			break;
		}
		case Stage_MeshEnum::JumboTron3:
		{
			NewObj.Actor_ = CreateActor<JumboTron>();
			std::dynamic_pointer_cast<JumboTron>(NewObj.Actor_.lock())->SetMesh("JumboTron3.FBX");
			break;
		}
		case Stage_MeshEnum::JumboTron4:
		{
			NewObj.Actor_ = CreateActor<JumboTron>();
			std::dynamic_pointer_cast<JumboTron>(NewObj.Actor_.lock())->SetMesh("JumboTron4.FBX");
			break;
		}
		case Stage_MeshEnum::JumboTron5:
		{
			NewObj.Actor_ = CreateActor<JumboTron>();
			std::dynamic_pointer_cast<JumboTron>(NewObj.Actor_.lock())->SetMesh("JumboTron5.FBX");
			break;
		}
		case Stage_MeshEnum::JumboTron6:
		{
			NewObj.Actor_ = CreateActor<JumboTron>();
			std::dynamic_pointer_cast<JumboTron>(NewObj.Actor_.lock())->SetMesh("JumboTron6.FBX");
			break;
		}
		case Stage_MeshEnum::JumboTron7:
		{
			NewObj.Actor_ = CreateActor<JumboTron>();
			std::dynamic_pointer_cast<JumboTron>(NewObj.Actor_.lock())->SetMesh("JumboTron7.FBX");
			break;
		}
		case Stage_MeshEnum::Rainbow:
		{
			NewObj.Actor_ = CreateActor<TestRainBow>();
			break;
		}
		case Stage_MeshEnum::TestMap:
		{
			NewObj.Actor_ = CreateActor<TestMapActor>();
			break;
		}
		case Stage_MeshEnum::DoorBlock:
		{
			NewObj.Actor_ = CreateActor<DoorBlock>();
			break;
		}
		case Stage_MeshEnum::MovingBar:
		{
			NewObj.Actor_ = CreateActor<MovingBar>();
			break;
		}
		case Stage_MeshEnum::Chevron:
		{
			NewObj.Actor_ = CreateActor<Chevron>();
			break;
		}
		case Stage_MeshEnum::WoodPlank:
		{
			NewObj.Actor_ = CreateActor<HoopsWoodPlank>();

			NewObj.Actor_.lock()->GetTransform().SetWorldPosition(Pos);
			NewObj.Actor_.lock()->GetTransform().SetWorldScale(Size);
			NewObj.Actor_.lock()->GetTransform().SetLocalRotation(Rot);

			std::dynamic_pointer_cast<HoopsWoodPlank>(NewObj.Actor_.lock())->SetRotation(Rot);
			break;
		}
		case Stage_MeshEnum::HoopsScythe:
		{
			NewObj.Actor_ = CreateActor<HoopsScythe>();
			break;
		}
		case Stage_MeshEnum::HoopsBox:
		{
			NewObj.Actor_ = CreateActor<HoopsBox>();
			std::dynamic_pointer_cast<HoopsBox>(NewObj.Actor_.lock())->SetFBX("HoopsBoxWall.FBX", "HoopsBoxFloor.FBX");
			break;
		}
		case Stage_MeshEnum::HoopsBox2:
		{
			NewObj.Actor_ = CreateActor<HoopsBox>();
			std::dynamic_pointer_cast<HoopsBox>(NewObj.Actor_.lock())->SetFBX("HoopsBoxWall2.FBX", "HoopsBoxFloor2.FBX");
			break;
		}
		case Stage_MeshEnum::HoopsBox3:
		{
			NewObj.Actor_ = CreateActor<HoopsBox>();
			std::dynamic_pointer_cast<HoopsBox>(NewObj.Actor_.lock())->SetFBX("HoopsBoxWall3.FBX", "HoopsBoxFloor3.FBX");
			break;
		}
		case Stage_MeshEnum::HoopsBox4:
		{
			NewObj.Actor_ = CreateActor<HoopsBox>();
			std::dynamic_pointer_cast<HoopsBox>(NewObj.Actor_.lock())->SetFBX("HoopsBoxWall4.FBX", "HoopsBoxFloor4.FBX");
			break;
		}
		case Stage_MeshEnum::HoopsRamp:
		{
			NewObj.Actor_ = CreateActor<HoopsRamp>();
			std::dynamic_pointer_cast<HoopsRamp>(NewObj.Actor_.lock())->SetFBX("HoopsRampWall.FBX" ,"HoopsRampFloor.FBX" );
			break;
		}
		case Stage_MeshEnum::HoopsRamp2:
		{
			NewObj.Actor_ = CreateActor<HoopsRamp>();
			std::dynamic_pointer_cast<HoopsRamp>(NewObj.Actor_.lock())->SetFBX("HoopsRampWall2.FBX", "HoopsRampFloor2.FBX");
			break;
		}
		case Stage_MeshEnum::HoopsScoreRing:
		{
			NewObj.Actor_ = CreateActor<HoopsScoreRing>();
			std::dynamic_pointer_cast<HoopsScoreRing>(NewObj.Actor_.lock())->SetFBX("HoopsScoreRing.FBX");
			break;
		}
		case Stage_MeshEnum::HoopsScoreRing2:
		{
			NewObj.Actor_ = CreateActor<HoopsScoreRing>();
			std::dynamic_pointer_cast<HoopsScoreRing>(NewObj.Actor_.lock())->SetFBX("HoopsScoreRing2.FBX");
			break;
		}
		case Stage_MeshEnum::Col_StartPos:
		{
			if (MyStage_ == StageNum::STAGE5)
			{
				NewObj.Actor_ = CreateActor<Col_StartPos>();
				NewObj.Actor_.lock()->GetTransform().SetWorldPosition(Pos);
				NewObj.Actor_.lock()->GetTransform().SetWorldScale(Size);
				NewObj.Actor_.lock()->GetTransform().SetLocalRotation(Rot);

				HoopsStartPos_.push_back(NewObj.Actor_.lock()->GetTransform().GetWorldPosition());
			}
			else
			{

				NewObj.Actor_ = CreateActor<Col_StartPos>();
				NewObj.Actor_.lock()->GetTransform().SetWorldPosition(Pos);
				NewObj.Actor_.lock()->GetTransform().SetWorldScale(Size);
				NewObj.Actor_.lock()->GetTransform().SetLocalRotation(Rot);

				StartPositions_.push_back(NewObj.Actor_.lock()->GetTransform().GetWorldPosition());

				//플레이어 포지션을 가지고있어야하는 static 전역변수
				PlayerPos = NewObj.Actor_.lock()->GetTransform().GetWorldPosition();
			}
			break;
		}
		case Stage_MeshEnum::Col_CheckPoint:
		{
			NewObj.Actor_ = CreateActor<Col_CheckPoint>();
			break;
		}
		case Stage_MeshEnum::Col_Trigger:
		{
			NewObj.Actor_ = CreateActor<Col_Trigger>();
			//후프의 포지션 나중에 다른 트리거를 추가하면 예외처리를 해줘야함 .
			NewObj.Actor_.lock()->GetTransform().SetWorldPosition(Pos);
			HoopsPos.push_back(NewObj.Actor_.lock()->GetTransform().GetWorldPosition());
			break;
		}
		case Stage_MeshEnum::Col_Goal:
		{
			NewObj.Actor_ = CreateActor<Col_Goal>();
			break;
		}
		case Stage_MeshEnum::END:
		{
			int a = 0;
			break;
		}
		default:
		{
			int a = 0;
			break;
		}
		}

		NewObj.Actor_.lock()->GetTransform().SetWorldPosition(Pos);
		NewObj.Actor_.lock()->GetTransform().SetWorldScale(Size);
		NewObj.Actor_.lock()->GetTransform().SetLocalRotation(Rot);







		StageObjects_.push_back(NewObj);

		j++;
	}
}


void StageParentLevel::SpawnServerObjects()
{
	std::list<std::shared_ptr<ObjectUpdatePacket>>& PacketList = GameServer::GetInst()->NewObjectUpdatePacketList_;

	while (false == PacketList.empty())
	{
		// GameServerObejcts와 비교
		std::shared_ptr<ObjectUpdatePacket> CurPacket;
		
		{
			std::lock_guard<std::mutex> Guard(SpawnLock);
			CurPacket = PacketList.front();
			PacketList.pop_front();
		}

		
		GameServerObject* ServerObject = GameServerObject::GetServerObject(CurPacket->ObjectID);

		if (nullptr == ServerObject)
		{
			// 없다면 소환
			switch (CurPacket->Type)
			{
			case ServerObjectType::Player:
			{
				std::shared_ptr<PlayerActor> NewPlayer = CreateActor<PlayerActor>();
				NewPlayer->ClientInit(CurPacket->Type, CurPacket->ObjectID);
				NewPlayer->GetTransform().SetWorldPosition(CurPacket->Pos);
				NewPlayer->GetTransform().SetWorldScale(CurPacket->Scale);
				NewPlayer->GetTransform().SetWorldRotation(CurPacket->Rot);


				NewPlayer->PlayerInit();
				NewPlayer->PushPacket(CurPacket);
				NewPlayer->SetPlayerInvisible(false);

				NetPlayers_.push_back(NewPlayer);

				break;
			}
			case ServerObjectType::SpinBarDouble:
			{
				if (MyStage_ != StageNum::STAGE2)
				{
					continue;
				}
				std::shared_ptr<JumpClub_SpinBarDouble> SpinBarDouble = CreateActor<JumpClub_SpinBarDouble>();
				SpinBarDouble->ClientInit(CurPacket->Type, CurPacket->ObjectID);
				SpinBarDouble->GetTransform().SetWorldPosition(CurPacket->Pos);
				SpinBarDouble->GetTransform().SetWorldScale(CurPacket->Scale);
				SpinBarDouble->GetPhysXSpinBarComponent()->SetCurRot(CurPacket->Rot.y);

				SpinBarDouble->PhysXInit();
				SpinBarDouble->PushPacket(CurPacket);
				NetObstacles_.push_back(SpinBarDouble);

				break;
			}
			case ServerObjectType::SpinBarSingle:
			{
				if (MyStage_ != StageNum::STAGE2)
				{
					continue;
				}
				std::shared_ptr<JumpClub_SpinBarSingle> SpinBarSingle = CreateActor<JumpClub_SpinBarSingle>();
				SpinBarSingle->ClientInit(CurPacket->Type, CurPacket->ObjectID);
				SpinBarSingle->GetTransform().SetWorldPosition(CurPacket->Pos);
				SpinBarSingle->GetTransform().SetWorldScale(CurPacket->Scale);
				SpinBarSingle->GetPhysXSpinBarComponent()->SetCurRot(CurPacket->Rot.y);
				
				SpinBarSingle->PhysXInit();
				SpinBarSingle->PushPacket(CurPacket);
				NetObstacles_.push_back(SpinBarSingle);
				break;
			}
			case ServerObjectType::Cannon:
			{
				if (MyStage_ != StageNum::STAGE3)
				{
					continue;
				}
				std::shared_ptr<BigShots_Cannon> Cannon = CreateActor<BigShots_Cannon>();
				Cannon->ClientInit(CurPacket->Type, CurPacket->ObjectID);
				Cannon->GetTransform().SetWorldPosition(CurPacket->Pos);
				Cannon->GetTransform().SetWorldScale(CurPacket->Scale);
				Cannon->GetTransform().SetWorldRotation(CurPacket->Rot);

				Cannon->PushPacket(CurPacket);
				NetObstacles_.push_back(Cannon);
				break;
			}
			case ServerObjectType::HoopRing:
			{
				if (MyStage_ != StageNum::STAGE5)
				{
					continue;
				}
				std::shared_ptr<HoopsScoreRing> Ring = CreateActor<HoopsScoreRing>();
				Ring->ClientInit(CurPacket->Type, CurPacket->ObjectID);
				Ring->GetTransform().SetWorldPosition(CurPacket->Pos);
				Ring->GetTransform().SetWorldScale(CurPacket->Scale);
				Ring->GetTransform().SetWorldRotation(CurPacket->Rot);

				Ring->PushPacket(CurPacket);
				NetObstacles_.push_back(Ring);
				break;
			}
			default:
				break;
			}
		}
		else
		{
			continue;
		}

	}


}

// *점수를 얻고 P_StageRaceChangeReady로 바꾸어야 함
void StageParentLevel::GetGameScoreByCurrentType()
{
	unsigned int AllPlayersCount = GameServer::GetInst()->GetAllPlayersCount();

	// 1. 순위확인  PlayerFlag::P_StageRaceChangeReady -> (결승에 들어온 플레이어/먼저 탈락한 플레이어) '신호'
	unsigned int FinishedPlayersCount = GameServer::GetInst()->CheckOtherPlayersFlagCount(PlayerFlag::P_StageRaceChangeReady);

	// 2. 순위에 따른 점수
	unsigned int EarnedScore = 0;

	// ex) 10명 플레이
	// DoorDash : 상위 4명이 점수 얻음 (400, 300, 200, 100, ..., 0, 0)
	// Hexagone : 하위 4명이 점수 얻음 (0, 0, ... , 100, 200, 300, 400)

	switch (GameScoreType_)
	{
	case StageParentLevel::GameScoreType::NONE:
		MsgBoxAssert("GameScoreType이 세팅되지 않은 레벨입니다");
		break;
	case StageParentLevel::GameScoreType::RACE:
	{
		// FinishedPlayersCount, 0 이면 1등
		EarnedScore = (AllPlayersCount * 100) - (FinishedPlayersCount * 100);

		if (EarnedScore <= 0)
		{
			EarnedScore = 0;
		}

		break;
	}
	case StageParentLevel::GameScoreType::SURVIVAL:
	{
		// FinishedPlayersCount, 0면 꼴등
		unsigned int Ranking = AllPlayersCount - FinishedPlayersCount;
		// 뒤에서 4등부터 4위, 3위, 2위, 1위

		if (Ranking <= 4)
		{
			// 4등 100점, 3등 200점, ...
			EarnedScore = ((AllPlayersCount + 1) * 100) - (100 * Ranking);
		}
		else
		{
			EarnedScore = 0;
		}

		break;
	}
	default:
		return;
		break;
	}

	GameServer::GetInst()->PlayerScore_ += EarnedScore;
}

void StageParentLevel::SetWatchCamNextPlayer()
{
	// 관전 인덱스 관리
	WatchCamIdx++;

	// 관전 플레이어 관리
	WatchPlayers_.clear();
	for (std::shared_ptr<GameEngineActor> LivePlayer : NetPlayers_)
	{
		if (false == std::dynamic_pointer_cast<PlayerActor>(LivePlayer)->GetNetDeath())
		{
			WatchPlayers_.push_back(LivePlayer);
		}
	}

	if (WatchCamIdx >= static_cast<int>(WatchPlayers_.size()))
	{
		WatchCamIdx = 0;
	}

	CameraArm_->SetFollowCamera(MainCam_, NetPlayers_[WatchCamIdx]);
	
}
