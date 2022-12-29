#include "PreCompile.h"
#include "HexAGoneLevel.h"
#include "InGameSetUI.h"

//오브젝트액터
#include "HexTile.h"
#include "Hex_BackGroundObject.h"
#include "PlayerActor.h"

#include "SkyboxActor.h"

#include <GameEngineBase/GameEngineRandom.h>

HexAGoneLevel::HexAGoneLevel() 
{
}

HexAGoneLevel::~HexAGoneLevel() 
{
}

void HexAGoneLevel::Start()
{
	MyStage_ = StageNum::STAGE4;
	GameScoreType_ = GameScoreType::SURVIVAL;
	StageParentLevel::Start();

	
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



	LightObject_->GetLightData().LightColor = float4{ 0.6f,0.8f,1.0f,1.0f };
	LightObject_->GetLightData().DifLightPower = 0.7f;
	LightObject_->GetLightData().SpcLightPower = 0.8f;
	LightObject_->GetLightData().AmbLightPower = 5.7f;
	LightObject_->GetTransform().SetWorldRotation({ 289.3,178.3f,0.0f });

	//ContentsCore::GetInst()->LoadLevelResource(LEVELS::STAGE04_HEX_A_GONE);
	BackGroundObj_ = CreateActor<Hex_BackGroundObject>();
	//Tiles_ = CreateActor<HexTile>();
	//Tiles_->GetTransform().SetWorldPosition({ 0,300.0f,0 });

	// InitPhysic는 레벨이 시작될때 실행되므로 LevelStartEvent가 실행되기 전에 포지션을 결정해야함.

	float XPos = 0;
	float ZPos = 0;
	float YPos = 50.0f;
	Num_ = 0;
	Col_ = 45;
	Row_ = 5;
	for (int k = 0; k < 5; k++)
	{
		for (int i = 0; i < Col_; i++)
		{
			XPos = Num_ * TileScale_.x * -0.75f;
			ZPos = i * TileScale_.z * -0.5f;

			for (int j = 0; j < Row_; j++)
			{
				std::shared_ptr<HexTile> Tile = CreateActor<HexTile>();
				if (k == 0)
				{
					Tile->SetTex("Yellow");
				}
				else if (k == 1)
				{
					Tile->SetTex("Blue");
				}
				else if (k == 2)
				{
					Tile->SetTex("Purple");
				}
				else if (k == 3)
				{
					Tile->SetTex("WhiteBlue");
				}
				else if (k == 4)
				{
					Tile->SetTex("Yellow");
				}
				TileScale_ = Tile->GetRenderer()->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
				Tile->GetTransform().SetWorldPosition({ XPos - 30,YPos,ZPos + 70 });
				XPos += Tile->GetRenderer()->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox.x * 1.5;
				if (k == 5)
				{
					TilesVec_.push_back(Tile);
				}
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

		YPos += 70.0f;

	}
	
	{
		float XPos = 0;
		float ZPos = 0;

		float SumPos = 0;

		Num_ = 0;
		Col_ = 5;
		Row_ = 1;
		for (int i = 0; i < Col_; i++)
		{
			XPos = 0 - Num_ * SumPos;
			ZPos = 0 + i * 25;


			for (int j = 1; j <= Row_; j++)
			{
				std::shared_ptr<HexTile> Tile = CreateActor<HexTile>();
				Tile->SetTex("WhiteBlue");
				Tile->GetTransform().SetWorldPosition({ XPos , 350.0f , ZPos - 50.0f });
				PositionList_.push_back(Tile->GetTransform().GetWorldPosition());

				XPos += Tile->GetRenderer()->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox.x * 3.0f;
				SumPos = Tile->GetRenderer()->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox.x * 1.5f;
			}


			if (i >= Col_ / 2)
			{
				Row_--;
				Num_--;
			}
			else
			{
				Row_++;
				Num_++;
			}


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

	//CinemaCam_->SetActivated();

//	//플레이어 위치 수정
//
	if (false == GameServer::GetInst()->IsServerStart())
	{
		Player_->SetCheckPoint(PositionList_[0] + float4(0, 0, 0));
		Player_->ResetPlayerPos();
	}
	else
	{
		unsigned int PlayerID = GameServer::GetInst()->PlayerID_;
		Player_->SetCheckPoint(PositionList_[PlayerID] + float4(0, 0, 0));
		Player_->ResetPlayerPos();
	}


}

void HexAGoneLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();

	for (std::shared_ptr<GameEngineActor> Tile : TilesVec_)
	{
		Tile->Death();
	}
}

bool HexAGoneLevel::GameEndingFlag()
{
	if (Player_->GetTransform().GetWorldPosition().y <= -20.0f)
	{
		return true;
	}

	return false;
}
