#include "PreCompile.h"
#include "JumpClubLevel.h"

// 오브젝트 액터
#include "SkyboxActor.h"
#include "JumpClub_BackGroundObject.h"
#include "VFXWaterActor.h"
#include "JumpClubStage.h"
#include "JumpClub_SpinBarDouble.h"
#include "JumpClub_SpinBarSingle.h"

#include "PlayerActor.h"

#include "PostEffect_Bloom.h"

#include "InGameSetUI.h"

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

	Player_ = CreateActor<PlayerActor>();

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

	UIs_ = CreateActor<InGameSetUI>();

	Player_->GetTransform().SetWorldPosition({ 0.0f,200.0f,0.0f });

	std::shared_ptr<JumpClubStage> Stage = CreateActor<JumpClubStage>();
	Stage->GetTransform().SetWorldPosition({ 0.0f, 0.0f, 0.0f });

	// Bar Y축 조정 필요
	std::shared_ptr<JumpClub_SpinBarDouble> BarDouble = CreateActor<JumpClub_SpinBarDouble>();
	BarDouble->GetTransform().SetWorldPosition({ 0.0f, 75.0f, 0.0f });

	std::shared_ptr<JumpClub_SpinBarSingle> BarSingle = CreateActor<JumpClub_SpinBarSingle>();
	BarSingle->GetTransform().SetWorldPosition({ 0.0f, 75.0f, 0.0f });

	std::shared_ptr<GameEngineActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void JumpClubLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
