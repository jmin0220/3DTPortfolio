#include "PreCompile.h"
#include "PhysXTestPlayer.h"

PhysXTestPlayer::PhysXTestPlayer() 
{
}

PhysXTestPlayer::~PhysXTestPlayer() 
{
}

void PhysXTestPlayer::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxControllerManager* _CtrManager)
{
	CCTActorComponent_->CreatePhysXActors(_Scene, _physics, _CtrManager);
}

void PhysXTestPlayer::Start()
{
	// 캐릭터 메쉬 로드 테스트용
	FbxRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	CCTActorComponent_ = CreateComponent<PhysXCCTActorComponent>();
}

void PhysXTestPlayer::Update(float _DeltaTime)
{
}

void PhysXTestPlayer::LevelStartEvent()
{
	// 메쉬 로드
	FbxRenderer_->SetFBXMesh("Character.FBX", "Texture");
	//FbxRenderer_->GetTransform().SetWorldScale({ SIZE_MAGNIFICATION_RATIO });


}

