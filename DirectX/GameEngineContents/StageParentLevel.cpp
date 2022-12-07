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



#include <GameEngineBase/magic_enum.hpp>
#include <GameEngineCore/ThirdParty/inc/json.h>
#include <GameEngineCore/CoreMinimal.h>
#include <iostream>
#include <fstream>
#include "InGameSetUI.h"
#include "PlayerActor.h"

float4 StageParentLevel::PlayerPos = float4::ZERO;


StageParentLevel::StageParentLevel() 
	: MyStage_(StageNum::STAGE1)
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

	// 스테이지 FSM
	StageStateManager_.CreateStateMember("Idle"
		, std::bind(&StageParentLevel::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&StageParentLevel::IdleStart, this, std::placeholders::_1));

	StageStateManager_.CreateStateMember("StagePreView"
		, std::bind(&StageParentLevel::StagePreViewUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&StageParentLevel::StagePreViewStart, this, std::placeholders::_1));

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
	VirtualPhysXLevel::Update(_DeltaTime);

	CinemaCam_->Update();

	StageStateManager_.Update(_DeltaTime);

}
void StageParentLevel::End()
{
	VirtualPhysXLevel::End();
}

void StageParentLevel::LevelStartEvent()
{
	VirtualPhysXLevel::LevelStartEvent();
	LevelStartLoad();

	// 서버
	// 호스트/클라이언트 자신의 플레이어
	Player_ = CreateActor<PlayerActor>();

	if (true == GameServer::GetInst()->IsServerStart())
	{
		if (true == GameServer::IsHost_)
		{
			Player_->ServerInit(ServerObjectType::Player);
		}
		else
		{
			Player_->ClientInit(ServerObjectType::Player, GameServer::GetInst()->PlayerID_);
		}
	}



	MainCam_ = GetMainCameraActor();
	CameraArm_ = CreateActor<CameraArm>();

	UIs_ = CreateActor<InGameSetUI>();

	StageStateManager_.ChangeState("Idle");



}
void StageParentLevel::LevelEndEvent()
{
	VirtualPhysXLevel::LevelEndEvent();
	ContentsCore::GetInst()->ReleaseCurLevelResource();

	Player_->Death();

	CameraArm_->Death();
	
	UIs_->Death();
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
		//CurStageName = "\\stage2.json";
		break;
	case StageNum::STAGE3:
		//CurStageName = "\\stage3.json";
		break;
	case StageNum::STAGE4:
		CurStageName = JSON_NAME_HEXAGONE;
		break;
	case StageNum::STAGE5:
		//CurStageName = JSON_NAME_HOOPSLEGENDS;
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
		case Stage_MeshEnum::Col_StartPos:
		{
			NewObj.Actor_ = CreateActor<Col_StartPos>();
			NewObj.Actor_.lock()->GetTransform().SetWorldPosition(Pos);
			NewObj.Actor_.lock()->GetTransform().SetWorldScale(Size);
			NewObj.Actor_.lock()->GetTransform().SetLocalRotation(Rot);

			//플레이어 포지션을 가지고있어야하는 static 전역변수
			PlayerPos = NewObj.Actor_.lock()->GetTransform().GetWorldPosition();

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

