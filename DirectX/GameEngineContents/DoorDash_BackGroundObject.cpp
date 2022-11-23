#include "PreCompile.h"
#include "DoorDash_BackGroundObject.h"

DoorDash_BackGroundObject::DoorDash_BackGroundObject() 
{
}

DoorDash_BackGroundObject::~DoorDash_BackGroundObject() 
{
}

void DoorDash_BackGroundObject::Start()
{
	// 2. 메쉬세팅 Static renderer
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("DoodrDashEnv.FBX", "Texture");
}

void DoorDash_BackGroundObject::Update(float _DeltaTime)
{
}
