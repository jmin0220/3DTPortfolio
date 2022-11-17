#include "PreCompile.h"
#include "StageParentLevel.h"
#include "TestRainBow.h"
#include "TestMapActor.h"
#include <GameEngineBase/magic_enum.hpp>
#include <GameEngineCore/ThirdParty/inc/json.h>
#include <GameEngineCore/CoreMinimal.h>
#include <iostream>
#include <fstream>

StageParentLevel::StageParentLevel() 
	: MyStage_(StageNum::STAGE1)
{
}

StageParentLevel::~StageParentLevel() 
{
}

void StageParentLevel::Start()
{
	VirtualPhysXLevel::Start();
}
void StageParentLevel::Update(float _DeltaTime)
{
	VirtualPhysXLevel::Update(_DeltaTime);
}
void StageParentLevel::End()
{
	VirtualPhysXLevel::End();
}

void StageParentLevel::LevelStartEvent()
{
	VirtualPhysXLevel::LevelStartEvent();
	LevelStartLoad();
}
void StageParentLevel::LevelEndEvent()
{
	VirtualPhysXLevel::LevelEndEvent();
	ContentsCore::GetInst()->ReleaseCurLevelResource();
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
		ContentsCore::GetInst()->LoadLevelResource(LEVELS::STAGE1_TEST);
		CurStageName = "\\stage1.json";
		break;
	}
	case StageNum::STAGE2:
		//ContentsCore::GetInst()->LoadLevelResource(LEVELS::STAGE2_TEST);
		//CurStageName = "\\stage2.json";
		break;
	case StageNum::STAGE3:
		//ContentsCore::GetInst()->LoadLevelResource(LEVELS::STAGE3_TEST);
		//CurStageName = "\\stage3.json";
		break;
	case StageNum::STAGE4:
		ContentsCore::GetInst()->LoadLevelResource(LEVELS::STAGE04_HEX_A_GONE);
		//CurStageName = "\\stage4.json";
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