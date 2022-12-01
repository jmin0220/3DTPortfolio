#include "PreCompile.h"
#include "HexAGoneLevel.h"
#include "InGameSetUI.h"

//오브젝트액터
#include "HexTile.h"
#include "Hex_BackGroundObject.h"
#include "PlayerActor.h"

#include "SkyboxActor.h"

HexAGoneLevel::HexAGoneLevel() 
{
}

HexAGoneLevel::~HexAGoneLevel() 
{
}

void HexAGoneLevel::Start()
{
	StageParentLevel::Start();
	MyStage_ = StageNum::STAGE4;

	
}

void HexAGoneLevel::Update(float _DeltaTime)
{
	StageParentLevel::Update(_DeltaTime);

	//if (GetAccTime() >= 5.0f)
	//{
	//	Tiles_->Off();
	//}
}

void HexAGoneLevel::End()
{
	StageParentLevel::End();
}

void HexAGoneLevel::LevelStartEvent()
{

	StageParentLevel::LevelStartEvent();
	//ContentsCore::GetInst()->LoadLevelResource(LEVELS::STAGE04_HEX_A_GONE);
	BackGroundObj_ = CreateActor<Hex_BackGroundObject>();
	//Tiles_ = CreateActor<HexTile>();
	//Tiles_->GetTransform().SetWorldPosition({ 0,300.0f,0 });

	// InitPhysic는 레벨이 시작될때 실행되므로 LevelStartEvent가 실행되기 전에 포지션을 결정해야함.
	Player_->GetTransform().SetWorldPosition({ 0.0f, 400.0f, 0.0f });

	float XPos = 0;
	float ZPos = 0;
	Num_ = 0;
	Col_ = 45;
	Row_ = 5;

	for (int i = 0; i < Col_; i++)
	{
		XPos = Num_ * TileScale_.x * -0.75f;
		ZPos = i * TileScale_.z * -0.5f;

		for (int j = 0; j < Row_; j++)
		{
			std::shared_ptr<HexTile> Tile = CreateActor<HexTile>();
			TileScale_ = Tile->GetRenderer()->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
			Tile->GetTransform().SetWorldPosition({ XPos - 30,300.0f,ZPos + 70 });
			XPos += Tile->GetRenderer()->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox.x * 1.5;
			TilesVec_.push_back(Tile);
		}

		if (i >= Col_ / 2)
		{
			Row_--;

			Num_--;
		}
		else
		{
			if (Row_ >= 10)
			{
				Row_--;
				Num_--;
				continue;
			}

			Row_++;
			Num_++;

		}

		if (Row_ < 5)
		{
			break;
		}
	}


	//for (int i = 0; i < Col_; i++)
	//{
	//	//XPos = i * TileScale_.x * 0.75f;
	//	ZPos = Num_ * TileScale_.z * -0.5f;
	//	
	//	for (int j = 0; j < Row_; j++)
	//	{
	//		std::shared_ptr<HexTile> Tile = CreateActor<HexTile>();
	//		TileScale_ = Tile->GetRenderer()->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	//		Tile->GetTransform().SetWorldPosition({ 10.0f + XPos,300.0f,ZPos });
	//		ZPos += Tile->GetRenderer()->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox.z;
	//		TilesVec_.push_back(Tile);
	//	}
	//	if (i >= Col_ / 2)
	//	{
	//		Row_--;

	//		Num_--;
	//	}
	//	else
	//	{
	//		Row_++;

	//		Num_++;
	//	}

	//	//ZPos += TileScale_.z * -0.5f;
	//	XPos += TileScale_.x * 0.75f;
	//}

	// 스카이박스 생성
	std::shared_ptr<SkyboxActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->SetSkyTexture("S5_SkyBox_Respawn.png");
}

void HexAGoneLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
