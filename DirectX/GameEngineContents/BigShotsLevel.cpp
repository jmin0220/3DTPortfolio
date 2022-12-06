#include "PreCompile.h"
#include "BigShotsLevel.h"

// 오브젝트 액터
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
	// 물 쉐이더 이상 추후 확인 필요
	VFXWaterObj_ = CreateActor<VFXWaterActor>();
	// 물 위아래 위치 조정 필요
	VFXWaterObj_->GetTransform().SetWorldPosition(float4{ 0.0f,-80.0f,0.0f });

	// TODO::테스트용 임시 포지션
	Player_->GetTransform().SetWorldPosition(float4(0.0f, 8.0f, 0.0f));
	// *플레이어 생성 후 카메라암 세팅 해줘야함*
	CameraArm_->SetFollowCamera(GetMainCameraActor(), Player_);

	std::shared_ptr<BigShotsStage> Stage = CreateActor<BigShotsStage>();
	Stage->GetTransform().SetWorldPosition({ 0.0f, 0.0f, 0.0f });
	
	//스카이박스
	std::shared_ptr<SkyboxActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->SetSkyTexture("S4_SkyBox.png");
}

void BigShotsLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
