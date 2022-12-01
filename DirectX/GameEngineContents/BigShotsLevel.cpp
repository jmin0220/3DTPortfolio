#include "PreCompile.h"
#include "BigShotsLevel.h"

// ������Ʈ ����
#include "SkyboxActor.h"
#include "BigShots_BackGroundObject.h"
#include "VFXWaterActor.h"
#include "BigShotsStage.h"

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
	VFXWaterObj_->GetTransform().SetWorldPosition(float4{ 0.0f,-80.0f,0.0f });

	Player_->GetTransform().SetWorldPosition(PlayerPos);

	std::shared_ptr<BigShotsStage> Stage = CreateActor<BigShotsStage>();
	Stage->GetTransform().SetWorldPosition({ 0.0f, -50.0f, 0.0f });
	
	//��ī�̹ڽ�
	std::shared_ptr<SkyboxActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->SetSkyTexture("S4_SkyBox.png");
}

void BigShotsLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
