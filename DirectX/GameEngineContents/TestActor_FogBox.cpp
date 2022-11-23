#include "PreCompile.h"
#include "TestActor_FogBox.h"

TestActor_FogBox::TestActor_FogBox()
{
}

TestActor_FogBox::~TestActor_FogBox()
{
}

void TestActor_FogBox::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetMesh("Box");
	Renderer_->SetPipeLine("BoxFog");

	Color_ = float4::WHITE;
	Renderer_->GetRenderUnit().ShaderResources.SetConstantBufferLink("ResultColor", Color_);
	Renderer_->GetTransform().SetWorldScale({ 100, 100, 100 });

}

void TestActor_FogBox::Update(float _DeltaTime)
{
}

void TestActor_FogBox::End()
{
}
