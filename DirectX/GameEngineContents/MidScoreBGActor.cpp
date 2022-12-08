#include "PreCompile.h"
#include "MidScoreBGActor.h"

MidScoreBGActor::MidScoreBGActor() 
{
}

MidScoreBGActor::~MidScoreBGActor() 
{
}

void MidScoreBGActor::Start()
{
	SlicePos_ = float4(1, 0, 0, 0);

	{
		BG_ = CreateComponent<GameEngineTextureRenderer>();
		BG_->GetTransform().SetWorldScale({ 1600.0f, 900.0f });
		BG_->GetTransform().SetWorldPosition({ 0.0f, 0.0f, 1500.0f });
		BG_->SetPivot(PIVOTMODE::CENTER);

		BG_->SetTexture("LogoBG.png");
	}

	{
		Pattern_ = CreateComponent<GameEngineTextureRenderer>();
		Pattern_->GetTransform().SetWorldScale({ 1600.0f, 900.0f });
		Pattern_->GetTransform().SetWorldPosition({ 0.0f, 0.0f, 1500.0f });
		Pattern_->SetPivot(PIVOTMODE::CENTER);

		Pattern_->SetTexture("LogoBG.png");

		Pattern_->GetRenderUnit()->SetMaterial("TextureLoop");
		Pattern_->GetRenderUnit()->EngineShaderResourcesSetting(Pattern_);
		Pattern_->GetRenderUnit()->ShaderResources.SetTexture("Tex", "LogoPattern.png");

		if (true == Pattern_->GetRenderUnit()->ShaderResources.IsConstantBuffer("SliceData"))
		{
			Pattern_->GetRenderUnit()->ShaderResources.SetConstantBufferLink("SliceData", SlicePos_);
		}

		Pattern_->GetRenderUnit()->ShaderResources.SetTexture("Mask", "LogoBG.png");
	}
}

void MidScoreBGActor::Update(float _DeltaTime)
{
}

void MidScoreBGActor::LevelStartEvent()
{
}
