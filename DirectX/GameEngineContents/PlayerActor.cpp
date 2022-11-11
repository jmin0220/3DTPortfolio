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
	// ĳ���� �޽� �ε� �׽�Ʈ��
	FbxRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	CCTActorComponent_ = CreateComponent<PhysXCCTActorComponent>();
}

void PlayerActor::Update(float _DeltaTime)
{
}

void PlayerActor::LevelStartEvent()
{
	// �޽� �ε�
	FbxRenderer_->SetFBXMesh("Character.FBX", "Texture");
	FbxRenderer_->GetTransform().SetWorldScale({ SIZE_MAGNIFICATION_RATIO });
}

