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
		GameEngineFBXStaticRenderer* Renderer = CreateComponent<GameEngineFBXStaticRenderer>();
		Renderer->SetFBXMesh("TestMap.FBX", "Texture");
		Renderer->GetTransform().SetWorldScale({ 50.0f,50.0f, 50.0f });
		// Renderer->SetFBXMesh("Monster3.FBX", "Texture");
		// std::vector<std::vector<GameEngineRenderUnit>>& Meshs = Renderer->GetAllRenderUnit();
	}
}

void TestMapActor::Update(float _DeltaTime)
{
}

