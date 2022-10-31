#include "PreCompile.h"
#include "TestActor_WaterPlane.h"


TestActor_WaterPlane::TestActor_WaterPlane() 
{
}

TestActor_WaterPlane::~TestActor_WaterPlane() 
{
}

// "Water" 메테리얼 적용 예시
void TestActor_WaterPlane::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->SetMesh("Rect");
	Renderer->GetRenderUnit().SetPipeLine("Water");
	Renderer->GetRenderUnit().EngineShaderResourcesSetting(Renderer);
	Renderer->GetTransform().SetWorldScale({ 300, 300, 1 });
}

void TestActor_WaterPlane::Update(float _DeltaTime)
{
}

