#include "PreCompile.h"
#include "JumpClub_BackGroundObject.h"

JumpClub_BackGroundObject::JumpClub_BackGroundObject() 
{
}

JumpClub_BackGroundObject::~JumpClub_BackGroundObject() 
{
}

void JumpClub_BackGroundObject::Start()
{
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer->SetFBXMesh("JumpClubMap.FBX", "Texture");
}

void JumpClub_BackGroundObject::Update(float _DeltaTime)
{
}

