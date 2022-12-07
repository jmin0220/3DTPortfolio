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
	BG_ = CreateComponent<GameEngineTextureRenderer>();
	BG_->SetTexture("Respawn_SkyBox.png");
	BG_->GetTransform().SetWorldScale({ 4096.0f,2048.0f });
	BG_->GetTransform().SetWorldPosition({ 0.0f,0.0f,1500.0f });

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
