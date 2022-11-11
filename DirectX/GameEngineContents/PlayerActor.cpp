#include "PreCompile.h"
#include "PlayerActor.h"

PlayerActor::PlayerActor() 
{
}

PlayerActor::~PlayerActor() 
{
}


void PlayerActor::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxControllerManager* _CtrManager)
{
	CCTActorComponent_->CreatePhysXActors(_Scene, _physics, _CtrManager);
}

void PlayerActor::Start()
{
	// 캐릭터 메쉬 로드 테스트용
	FbxRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	CCTActorComponent_ = CreateComponent<PhysXCCTActorComponent>();
}

void PlayerActor::Update(float _DeltaTime)
{
}

void PlayerActor::LevelStartEvent()
{
	// 메쉬 로드
	FbxRenderer_->SetFBXMesh("Character.FBX", "Texture");
	FbxRenderer_->GetTransform().SetWorldScale({ SIZE_MAGNIFICATION_RATIO });
}

