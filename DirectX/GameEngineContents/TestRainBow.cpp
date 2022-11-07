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
		//Renderer->GetTransform().SetWorldScale({ 50.0f,50.0f, 50.0f});
		// Renderer->SetFBXMesh("Monster3.FBX", "Texture");
		// std::vector<std::vector<GameEngineRenderUnit>>& Meshs = Renderer->GetAllRenderUnit();
	}

	{
		// 마우스 피킹
		CreatePickingCollision({ 155.0f, 155.0f, 305.0f }, { 0.0f,0,-50.0f });
	}
}

void TestRainBow::Update(float _DeltaTime)
{
	CheckPickingRay();
}

