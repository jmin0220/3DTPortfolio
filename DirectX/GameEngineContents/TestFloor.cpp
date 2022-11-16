#include "PreCompile.h"
#include "TestFloor.h"

TestFloor::TestFloor() 
{
}

TestFloor::~TestFloor() 
{
}

void TestFloor::Start()
{
	Renderer = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer->SetFBXMesh("ScaleTestFloor.FBX", "Texture");
}

void TestFloor::Update(float _DeltaTime)
{
}

