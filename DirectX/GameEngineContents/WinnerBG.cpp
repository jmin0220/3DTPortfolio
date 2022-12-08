#include "PreCompile.h"
#include "WinnerBG.h"

WinnerBG::WinnerBG() 
{
}

WinnerBG::~WinnerBG() 
{
}

void WinnerBG::Start()
{
	Mesh_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Mesh_->SetFBXMesh("WinnerLevelOBJ.fbx", "Texture");
	Mesh_->GetTransform().SetWorldScale({ 2.0f,2.0f,2.0f });
	Mesh_->GetTransform().SetWorldPosition({ 0,-70,70 });
}

void WinnerBG::Update(float _DeltaTime)
{
}

void WinnerBG::LevelStartEvent()
{
}

void WinnerBG::LevelEndEvent()
{
}
