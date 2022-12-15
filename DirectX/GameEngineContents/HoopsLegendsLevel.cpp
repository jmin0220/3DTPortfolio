#include "PreCompile.h"
#include "SkyboxActor.h"
#include "HoopsLegendsLevel.h"
#include "PlayerActor.h"
#include "HoopsStageObjects.h"

#include "HoopsScoreRing.h"
#include "TestGUI.h"
#include "GameEngineBase/GameEngineRandom.h"

HoopsLegendsLevel::HoopsLegendsLevel() :
	SettingHoops_(false)
{
}

HoopsLegendsLevel::~HoopsLegendsLevel() 
{
}

void HoopsLegendsLevel::Start()
{
	MyStage_ = StageNum::STAGE5;
	StageParentLevel::Start();

	GUI_ = GameEngineGUI::CreateGUIWindow<TestGUI>("MapEditorGUI", this);
	GUI_->Off();

	

	// InitPhysic�� ������ ���۵ɶ� ����ǹǷ� LevelStartEvent�� ����Ǳ� ���� �������� �����ؾ���.
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
	//��ī�̹ڽ�
	std::shared_ptr<SkyboxActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->SetSkyTexture("Respawn_SkyBox_S02.png");
	//�׿� ���� static�Ž�
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

	//���� �ʱ���ġ ����
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
