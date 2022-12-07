#include "PreCompile.h"
#include "SkyboxActor.h"
#include "HoopsLegendsLevel.h"
#include "PlayerActor.h"
#include "HoopsStageObjects.h"

#include "TestGUI.h"

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

	// InitPhysic�� ������ ���۵ɶ� ����ǹǷ� LevelStartEvent�� ����Ǳ� ���� �������� �����ؾ���.
	//Player_->GetTransform().SetWorldPosition({ 10.0f, -70.0f, -390.0f });
}

void HoopsLegendsLevel::Update(float _DeltaTime)
{
	StageParentLevel::Update(_DeltaTime);
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
	//BackGround_ = CreateActor<DoorDash_BackGroundObject>();
	//BackGround_->GetTransform().SetWorldPosition({ 0,0,0 });
	GUI_->On();
}

void HoopsLegendsLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
