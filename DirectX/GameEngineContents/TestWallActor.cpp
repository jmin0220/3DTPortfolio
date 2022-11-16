#include "PreCompile.h"
#include "TestWallActor.h"

TestWallActor::TestWallActor() 
{
}

TestWallActor::~TestWallActor() 
{
}

void TestWallActor::Start()
{
	Renderer = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer->SetFBXMesh("ScaleTestWall.FBX", "Texture");
	Renderer->GetTransform().SetWorldScale({ 1.0f,1.0f,1.0f });
}

void TestWallActor::Update(float _DeltaTime)
{
}

