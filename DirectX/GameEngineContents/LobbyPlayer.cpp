#include "PreCompile.h"
#include "LobbyPlayer.h"

LobbyPlayer::LobbyPlayer() 
{
}

LobbyPlayer::~LobbyPlayer() 
{
}

void LobbyPlayer::Start()
{
	FBXRenderer_ = CreateComponent<GameEngineFBXAnimationRenderer>();
	FBXRenderer_->SetFBXMesh("Character.fbx", "TextureAnimation");
	FBXRenderer_->CreateFBXAnimation("Idle", "Character.fbx");
	FBXRenderer_->ChangeAnimation("Idle");
	FBXRenderer_->GetTransform().SetWorldScale({ SIZE_MAGNIFICATION_RATIO });
}

void LobbyPlayer::Update(float _DeltaTime)
{
}

void LobbyPlayer::LevelStartEvent()
{
}
