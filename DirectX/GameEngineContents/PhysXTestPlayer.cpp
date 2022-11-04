#include "PreCompile.h"
#include "PhysXTestPlayer.h"

PhysXTestPlayer::PhysXTestPlayer() 
{
}

PhysXTestPlayer::~PhysXTestPlayer() 
{
}

void PhysXTestPlayer::Start()
{
	// 캐릭터 메쉬 로드 테스트용
	FbxRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();

}

void PhysXTestPlayer::Update(float _DeltaTime)
{
}

void PhysXTestPlayer::LevelStartEvent()
{
	// 메쉬 로드
	FbxRenderer_->SetFBXMesh("Character.FBX", "Texture");
	FbxRenderer_->GetTransform().SetWorldScale({ 100, 100, 100 });
}

