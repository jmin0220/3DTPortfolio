#include "PreCompile.h"
#include "BigShotsLevel.h"

// ������Ʈ ����
#include "SkyboxActor.h"
#include "BigShots_BackGroundObject.h"
#include "VFXWaterActor.h"
#include "BigShotsStage.h"
#include "BigShots_Cannon.h"
#include "BigShots_Spinner.h"

#include "PlayerActor.h"

BigShotsLevel::BigShotsLevel() 
{
}

BigShotsLevel::~BigShotsLevel() 
{
}

void BigShotsLevel::Start()
{
	StageParentLevel::Start();
	MyStage_ = StageNum::STAGE3;

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
	// �� ���̴� �̻� ���� Ȯ�� �ʿ�
	VFXWaterObj_ = CreateActor<VFXWaterActor>();
	// �� ���Ʒ� ��ġ ���� �ʿ�
	VFXWaterObj_->GetTransform().SetWorldPosition(float4{ 0.0f,-60.0f,0.0f });

	//// TODO::�׽�Ʈ�� �ӽ� ������
	//Player_->GetTransform().SetWorldPosition(float4(0.0f, 8.0f, 0.0f));
	//// *�÷��̾� ���� �� ī�޶�� ���� �������*
	//CameraArm_->SetFollowCamera(GetMainCameraActor(), Player_);

	std::shared_ptr<BigShotsStage> Stage = CreateActor<BigShotsStage>();
	Stage->GetTransform().SetWorldPosition({ 0.0f, -50.0f, 0.0f });
	
	std::shared_ptr<BigShots_Cannon> Cannon1 = CreateActor<BigShots_Cannon>();
	Cannon1->GetTransform().SetWorldPosition({ -50.0f, -20.0f, -180.0f });
	Cannon1->GetTransform().SetWorldRotation({ -10.0f, 0.0f, 0.0f });

	std::shared_ptr<BigShots_Cannon> Cannon2 = CreateActor<BigShots_Cannon>();
	Cannon2->GetTransform().SetWorldPosition({ 0.0f, -20.0f, -180.0f });
	Cannon2->GetTransform().SetWorldRotation({ -10.0f, 0.0f, 0.0f });

	std::shared_ptr<BigShots_Cannon> Cannon3 = CreateActor<BigShots_Cannon>();
	Cannon3->GetTransform().SetWorldPosition({ 50.0f, -20.0f, -180.0f });
	Cannon3->GetTransform().SetWorldRotation({ -10.0f, 0.0f, 0.0f });

	// Test��
	std::shared_ptr<BigShots_Spinner> Spinner1 = CreateActor<BigShots_Spinner>();
	Spinner1->GetTransform().SetWorldPosition({ 50.0f, -20.0f, 0.0f });

	//��ī�̹ڽ�
	std::shared_ptr<SkyboxActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->SetSkyTexture("S4_SkyBox.png");
}

void BigShotsLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
