#include "PreCompile.h"
#include "BigShotsLevel.h"

// 오브젝트 액터
#include "SkyboxActor.h"
#include "BigShots_BackGroundObject.h"
#include "VFXWaterActor.h"
#include "BigShotsStage.h"
#include "BigShots_Cannon.h"
#include "BigShots_Spinner.h"

#include "PlayerActor.h"
#include <GameEngineBase/GameEngineRandom.h>

BigShotsLevel::BigShotsLevel() 
	: ServerActivated_(false)
{
}

BigShotsLevel::~BigShotsLevel() 
{
}

void BigShotsLevel::Start()
{
	MyStage_ = StageNum::STAGE3;
	GameScoreType_ = GameScoreType::SURVIVAL;
	StageParentLevel::Start();


	LightObject_->GetLightData().DifLightPower = 0.7f;
	LightObject_->GetLightData().AmbLightPower = 2.5;
	LightObject_->GetTransform().SetWorldRotation({ 90.0f,0.0f,0 });

}

void BigShotsLevel::Update(float _DeltaTime)
{
	StageParentLevel::Update(_DeltaTime);


}

void BigShotsLevel::End()
{
	StageParentLevel::End();
}

void BigShotsLevel::LevelStartEvent()
{
	StageParentLevel::LevelStartEvent();


	BackGroundObj_ = CreateActor<BigShots_BackGroundObject>();
	// 물 쉐이더 이상 추후 확인 필요
	VFXWaterObj_ = CreateActor<VFXWaterActor>();
	// 물 위아래 위치 조정 필요
	VFXWaterObj_->GetTransform().SetWorldPosition(float4{ 0.0f,-60.0f,0.0f });

	// TODO::Player의 위치가 대략 -55이하면 게임오버

	//// TODO::테스트용 임시 포지션
	//Player_->GetTransform().SetWorldPosition(float4(0.0f, 8.0f, 0.0f));
	//// *플레이어 생성 후 카메라암 세팅 해줘야함*
	//CameraArm_->SetFollowCamera(GetMainCameraActor(), Player_);

	std::shared_ptr<BigShotsStage> Stage = CreateActor<BigShotsStage>();
	Stage->GetTransform().SetWorldPosition({ 0.0f, -50.0f, 0.0f });
	
	// 호스트만 캐논 생성
	if (true == GameServer::IsHost_)
	{
		std::shared_ptr<BigShots_Cannon> Cannon1 = CreateActor<BigShots_Cannon>();
		Cannon1->GetTransform().SetWorldPosition({ -50.0f, -20.0f, -250.0f });
		Cannon1->GetTransform().SetWorldRotation({ -10.0f, 0.0f, 0.0f });
		Cannon1->ClientInit(ServerObjectType::Cannon, GameServerObject::GetObjectID());
		Cannon1->SetInitialInterTime(GameEngineRandom::MainRandom.RandomFloat(2, 5));
		Cannons_.push_back(Cannon1);

		std::shared_ptr<BigShots_Cannon> Cannon2 = CreateActor<BigShots_Cannon>();
		Cannon2->GetTransform().SetWorldPosition({ 0.0f, -20.0f, -250.0f });
		Cannon2->GetTransform().SetWorldRotation({ -10.0f, 0.0f, 0.0f });
		Cannon2->ClientInit(ServerObjectType::Cannon, GameServerObject::GetObjectID());
		Cannon2->SetInitialInterTime(GameEngineRandom::MainRandom.RandomFloat(2, 5));
		Cannons_.push_back(Cannon2);

		std::shared_ptr<BigShots_Cannon> Cannon3 = CreateActor<BigShots_Cannon>();
		Cannon3->GetTransform().SetWorldPosition({ 50.0f, -20.0f, -250.0f });
		Cannon3->GetTransform().SetWorldRotation({ -10.0f, 0.0f, 0.0f });
		Cannon3->ClientInit(ServerObjectType::Cannon, GameServerObject::GetObjectID());
		Cannon3->SetInitialInterTime(GameEngineRandom::MainRandom.RandomFloat(2, 5));
		Cannons_.push_back(Cannon3);
	}

	if (false == GameServer::GetInst()->IsServerStart())
	{
		std::shared_ptr<BigShots_Cannon> Cannon1 = CreateActor<BigShots_Cannon>();
		Cannon1->GetTransform().SetWorldPosition({ -50.0f, -20.0f, -250.0f });
		Cannon1->GetTransform().SetWorldRotation({ -10.0f, 0.0f, 0.0f });

		//std::shared_ptr<BigShots_Cannon> Cannon2 = CreateActor<BigShots_Cannon>();
		//Cannon2->GetTransform().SetWorldPosition({ 0.0f, -20.0f, -250.0f });
		//Cannon2->GetTransform().SetWorldRotation({ -10.0f, 0.0f, 0.0f });

		//std::shared_ptr<BigShots_Cannon> Cannon3 = CreateActor<BigShots_Cannon>();
		//Cannon3->GetTransform().SetWorldPosition({ 50.0f, -20.0f, -250.0f });
		//Cannon3->GetTransform().SetWorldRotation({ -10.0f, 0.0f, 0.0f });
	}

	//스카이박스
	std::shared_ptr<SkyboxActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->SetSkyTexture("S4_SkyBox.png");


	// 플레이어 스폰 위치 조정
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

			Player_->SetCheckPoint(StartPositions_[PositionIdx] + float4(0, PositionIdxPlus * 10.0f, 0));
			Player_->ResetPlayerPos();
		}
	}
	else
	{
		Player_->SetCheckPoint(StartPositions_[0]);
		Player_->ResetPlayerPos();
	}

}

void BigShotsLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();

	for (std::shared_ptr<BigShots_Cannon> Cannon : Cannons_)
	{
		Cannon->Death();
	}
}

bool BigShotsLevel::GameEndingFlag()
{
	if (Player_->GetTransform().GetWorldPosition().y <= -65.0f)
	{
		return true;
	}

	return false;
}
