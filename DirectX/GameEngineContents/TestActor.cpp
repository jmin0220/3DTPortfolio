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
	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetTexture("large-pill-black.png");
	Renderer_->GetTransform().SetWorldScale({ 459, 141 });

	Renderer_->GetRenderUnit().SetPipeLine("TextureLoop");
	Renderer_->GetRenderUnit().EngineShaderResourcesSetting(Renderer_);
	Renderer_->GetRenderUnit().ShaderResources.SetTexture("Tex", "crown-pattern-2.png");
	
	if (true == Renderer_->GetRenderUnit().ShaderResources.IsConstantBuffer("Tex"))
	{
		int a = 0;//들어오는지 테스트용
	}

} 

void TestActor::Update(float _DeltaTime)
{
}

