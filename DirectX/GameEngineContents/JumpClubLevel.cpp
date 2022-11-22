#include "PreCompile.h"
#include "JumpClubLevel.h"

// ������Ʈ ����
#include "SkyboxActor.h"
#include "JumpClub_BackGroundObject.h"
#include "VFXWaterActor.h"

#include "PostEffect_Bloom.h"

JumpClubLevel::JumpClubLevel() 
{
}

JumpClubLevel::~JumpClubLevel() 
{
}

void JumpClubLevel::Start()
{
	StageParentLevel::Start();
	MyStage_ = StageNum::STAGE2;

	std::shared_ptr<PostEffect_Bloom> Ptr = GetMainCamera()->GetCameraRenderTarget()->AddEffect<PostEffect_Bloom>();
	Ptr->Off();
}

void JumpClubLevel::Update(float _DeltaTime)
{
	StageParentLevel::Update(_DeltaTime);
}

void JumpClubLevel::End()
{
	StageParentLevel::End();
}

void JumpClubLevel::LevelStartEvent()
{
	StageParentLevel::LevelStartEvent();
	BackGroundObj_ = CreateActor<JumpClub_BackGroundObject>();
	VFXWaterObj_ = CreateActor<VFXWaterActor>();

	std::shared_ptr<GameEngineActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void JumpClubLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
