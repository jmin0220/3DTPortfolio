#include "PreCompile.h"
#include "TestMapActor.h"

TestMapActor::TestMapActor() 
{
}

TestMapActor::~TestMapActor() 
{
}

void TestMapActor::Start()
{
	{
		std::shared_ptr<GameEngineFBXStaticRenderer> Renderer = CreateComponent<GameEngineFBXStaticRenderer>();
		Renderer->SetFBXMesh("HexAGoneMap.FBX", "Texture");
		//Renderer->GetTransform().SetWorldScale({ 50.0f,50.0f, 50.0f });
	}
}

void TestMapActor::Update(float _DeltaTime)
{
}

