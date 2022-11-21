#include "PreCompile.h"
#include "PostEffect_Bloom.h"

PostEffect_Bloom::PostEffect_Bloom()
{
}

PostEffect_Bloom::~PostEffect_Bloom()
{
}

void PostEffect_Bloom::EffectInit()
{
	CopyTarget = std::make_shared<GameEngineRenderTarget>();
	CopyTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	EffectSet.SetMesh("FullRect");
	EffectSet.SetPipeLine("Bloom");
}

void PostEffect_Bloom::Effect(std::shared_ptr<GameEngineRenderTarget> _Target)
{
	CopyTarget->Copy(_Target);

	EffectSet.ShaderResources.SetTexture("Tex", CopyTarget->GetRenderTargetTexture(0));
	_Target->Clear();
	_Target->Setting();
	_Target->Effect(EffectSet);
}

