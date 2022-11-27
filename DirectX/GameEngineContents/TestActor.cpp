#include "PreCompile.h"
#include "TestActor.h"

TestActor::TestActor() 
{
}

TestActor::~TestActor() 
{
}

void TestActor::Start()
{
	SlicePos_ = float4(1, 1, 0, 0);

	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetTexture("large-pill-black.png");
	Renderer_->GetTransform().SetWorldScale({ 459, 141 });

	Renderer_->GetRenderUnit()->SetPipeLine("TextureLoop");
	Renderer_->GetRenderUnit()->EngineShaderResourcesSetting(Renderer_);
	Renderer_->GetRenderUnit()->ShaderResources.SetTexture("Tex", "crown-pattern-2.png");

	Renderer_->GetRenderUnit()->ShaderResources.SetTexture("Mask", "large-pill-black.png");
	
	if (true == Renderer_->GetRenderUnit()->ShaderResources.IsConstantBuffer("SliceData"))
	{
		Renderer_->GetRenderUnit()->ShaderResources.SetConstantBufferLink("SliceData", SlicePos_);
	}
} 

void TestActor::Update(float _DeltaTime)
{
	SlicePos_.x += 0.1f;
}

void TestActor::LevelStartEvent()
{
	SlicePos_.x = 0.0f;
}
