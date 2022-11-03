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
		GameEngineFBXRenderer* Renderer = CreateComponent<GameEngineFBXRenderer>();
		Renderer->SetFBXMesh("TestMap.FBX", "Texture");
		Renderer->GetTransform().SetWorldScale({ 50.0f,50.0f, 50.0f });
		// Renderer->SetFBXMesh("Monster3.FBX", "Texture");
		// std::vector<std::vector<GameEngineRenderUnit>>& Meshs = Renderer->GetAllRenderUnit();
	}
}

void TestMapActor::Update(float _DeltaTime)
{
}

