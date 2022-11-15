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
	FBXRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	FBXRenderer_->SetFBXMesh("Character.FBX", "TextureCustom");

	FBXRenderer_->GetTransform().SetWorldScale({ 200, 200, 200 });
}

void LobbyPlayer::Update(float _DeltaTime)
{
}

void LobbyPlayer::LevelStartEvent()
{
}
