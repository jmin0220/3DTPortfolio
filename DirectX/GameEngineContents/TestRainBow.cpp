#include "PreCompile.h"
#include "TestRainBow.h"
#include <GameEngineCore/GameEngineFBXRenderer.h>


TestRainBow::TestRainBow() 
{
}

TestRainBow::~TestRainBow() 
{
}

void TestRainBow::Start()
{
	{
		GameEngineFBXStaticRenderer* Renderer = CreateComponent<GameEngineFBXStaticRenderer>();
		Renderer->SetFBXMesh("Rainbow.FBX", "Texture");
		Renderer->GetTransform().SetWorldScale({ 50.0f,50.0f, 50.0f});
		// Renderer->SetFBXMesh("Monster3.FBX", "Texture");
		// std::vector<std::vector<GameEngineRenderUnit>>& Meshs = Renderer->GetAllRenderUnit();
	}
}

void TestRainBow::Update(float _DeltaTime)
{
}

