#include "PreCompile.h"
#include "FloorActor.h"

FloorActor::FloorActor() 
{
}

FloorActor::~FloorActor() 
{
}

void FloorActor::Start()
{
	FBXRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	FBXRenderer_->SetFBXMesh("Floor.fbx", "Texture");
}

void FloorActor::Update(float _DeltaTime)
{
}

void FloorActor::LevelStartEvent()
{
	FBXRenderer_->GetTransform().SetWorldScale({ 0.007,0.007,0.007 });
	FBXRenderer_->GetTransform().SetWorldPosition({ -1.5f,-18.0f });
}
