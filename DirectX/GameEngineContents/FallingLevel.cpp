#include "PreCompile.h"
#include "FallingLevel.h"
#include "LobbyPlayer.h"

FallingLevel::FallingLevel() 
{
}

FallingLevel::~FallingLevel() 
{
}

void FallingLevel::Start()
{
}

void FallingLevel::Update(float _DeltaTime)
{
}

void FallingLevel::End()
{
}

void FallingLevel::LevelStartEvent()
{
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	Player_ = CreateActor<LobbyPlayer>();
	Player_->GetTransform().SetWorldRotation({ 0,180,0 });
	Player_->GetTransform().SetWorldPosition({ 0,-15,0 });

	Player_->ChangeAnimationWin();
}

void FallingLevel::LevelEndEvent()
{
	Player_->Death();

	ContentsCore::GetInst()->ReleaseCurLevelResource();
}
