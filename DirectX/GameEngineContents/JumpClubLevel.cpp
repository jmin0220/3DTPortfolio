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
	MyStage_ = StageNum::STAGE2;
	StageParentLevel::Start();


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
	Stage->GetTransform().SetWorldPosition({ 0.0f, 65.0f, 0.0f });

	// Bar Y축 조정 필요
	// 호스트 : 생성하고 서버초기화
	// 유저 : 패킷받아서생성, 움직임은 서버 패킷받아서 움직임
	
	// 서버 안키고 디버깅 할 때
	{
		if (false == GameServer::GetInst()->IsServerStart())
		{
			std::shared_ptr<JumpClub_SpinBarDouble> BarDouble = CreateActor<JumpClub_SpinBarDouble>();
			BarDouble->GetTransform().SetWorldPosition({ 0.0f, 77.0f, 0.0f });
			BarDouble->PhysXInit();


			std::shared_ptr<JumpClub_SpinBarSingle> BarSingle = CreateActor<JumpClub_SpinBarSingle>();
			BarSingle->GetTransform().SetWorldPosition({ 0.0f, 62.0f, 0.0f });
			BarSingle->PhysXInit();
		}
	}


	if (true == GameServer::IsHost_)
	{
		std::shared_ptr<JumpClub_SpinBarDouble> BarDouble = CreateActor<JumpClub_SpinBarDouble>();
		BarDouble->ServerInit(ServerObjectType::SpinBarDouble);
		BarDouble->GetTransform().SetWorldPosition({ 0.0f, 77.0f, 0.0f });
		BarDouble->PhysXInit();


		std::shared_ptr<JumpClub_SpinBarSingle> BarSingle = CreateActor<JumpClub_SpinBarSingle>();
		BarSingle->ServerInit(ServerObjectType::SpinBarSingle);
		BarSingle->GetTransform().SetWorldPosition({ 0.0f, 62.0f, 0.0f });
		BarSingle->PhysXInit();
	}


	std::shared_ptr<GameEngineActor> Skybox = CreateActor<SkyboxActor>();
	Skybox->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void JumpClubLevel::LevelEndEvent()
{
	StageParentLevel::LevelEndEvent();
}
