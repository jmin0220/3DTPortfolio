#include "PreCompile.h"
#include "BigShots_BackGroundObject.h"

BigShots_BackGroundObject::BigShots_BackGroundObject() 
{
}

BigShots_BackGroundObject::~BigShots_BackGroundObject() 
{
}

void BigShots_BackGroundObject::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("BigShotsMap.FBX", "CustomDefferedColor");
}

void BigShots_BackGroundObject::Update(float _DeltaTime)
{
}

