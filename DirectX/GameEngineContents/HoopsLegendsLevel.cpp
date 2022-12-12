#include "PreCompile.h"
#include "SkyboxActor.h"
#include "HoopsLegendsLevel.h"
#include "PlayerActor.h"
#include "HoopsStageObjects.h"

#include "HoopsScoreRing.h"
#include "TestGUI.h"
#include "GameEngineBase/GameEngineRandom.h"

HoopsLegendsLevel::HoopsLegendsLevel() 
{
}

HoopsLegendsLevel::~HoopsLegendsLevel() 
{
}

void HoopsLegendsLevel::Start()
{
	StageParentLevel::Start();
	MyStage_ = StageNum::STAGE5;

	GUI_ = GameEngineGUI::CreateGUIWindow<TestGUI>("MapEditorGUI", this);
	GUI_->Off();

	

	// InitPhysic는 레벨이 시작될때 실행되므로 LevelStartEvent가 실행되기 전에 포지션을 결정해야함.
	//Player_->GetTransform().SetWorldPosition({ 10.0f, -70.0f, -390.0f });
}

void HoopsLegendsLevel::Update(float _DeltaTime)
{
	StageParentLevel::Update(_DeltaTime);

	SetHoopPosition();
}

void HoopsLegendsLevel::End()
{
	StageParentLevel::End();
}

void HoopsLegendsLevel::LevelStartEvent()
{

	StageParentLevel::LevelStartEvent();

	Player_->GetTransform().SetWorldPosition({ 0,100.0f,0 });
	//스카이박스
	std::shared_ptr<SkyboxActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->SetSkyTexture("Respawn_SkyBox_S02.png");
	//그외 배경용 static매쉬
	std::shared_ptr<HoopsStageObjects> BackGround_ = CreateActor<HoopsStageObjects>();
	GUI_->SetObj(BackGround_);
	GUI_->On();

	for (int i = 0; i < 10; i++)
	{
		Hoops_ = CreateActor<HoopsScoreRing>();
		//Hoops_->Off();
		HoopsActor.push_back(Hoops_);

		PrevPos[i] = -1;
	}
}

void HoopsLegendsLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}

void HoopsLegendsLevel::SetHoopPosition()
{


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
		HoopsActor[i]->On();
	}
}
