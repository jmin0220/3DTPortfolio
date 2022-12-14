#include "PreCompile.h"
#include "BigShots_Puff.h"
#include <GameEngineCore/GameEnginePixelShader.h>

BigShots_Puff::BigShots_Puff() 
	: IsTransTexture_(false)
	, SumTime_(0.0f)
	, SumValue_(10.0f)
{
}

BigShots_Puff::~BigShots_Puff() 
{
}

void BigShots_Puff::Start()
{
	PuffRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	PuffRenderer_->SetTexture("VFX_SomePuff_02.png");
	//PuffRenderer_->SetMaterial("CustomDefferedColor");
	PuffRenderer_->GetTransform().SetWorldScale({ SumValue_,SumValue_,0 });
	//PuffRenderer_->GetRenderUnit()->GetMaterial()->GetPixelShader()->SetIsAlphaEffect(true);

	PuffRenderer_->GetCamera()->ChangeRenderingOrder(PuffRenderer_, 0, RENDERINGPATHORDER::ALPHAEFFECT);
	PuffRenderer_->GetRenderUnit()->GetMaterial()->SetOutputMergerDepthStencil("AlwaysDepth");
}

void BigShots_Puff::Update(float _DeltaTime)
{
	if(false == IsTransTexture_ && 1.0f > SumTime_)
	{
		SumTime_ += _DeltaTime;
		SumValue_ += 0.1f;
		PuffRenderer_->GetPixelData().MulColor.a -= _DeltaTime * 0.8f;
		PuffRenderer_->GetTransform().SetWorldScale(GetTransform().GetWorldScale() + float4{ SumValue_ ,SumValue_ });
		PuffRenderer_->GetTransform().SetWorldRightMove(15.0f, _DeltaTime);
	}
	else if (false == IsTransTexture_ && 1.0f < SumTime_)
	{
		IsTransTexture_ = true;
		SumTime_ = 0.0f;
		PuffRenderer_->SetTexture("VFX_SomePuff_01.png");
	}

	if (true == IsTransTexture_ && 1.0f > SumTime_)
	{
		SumTime_ += _DeltaTime;
		SumValue_ += 0.1f;
		PuffRenderer_->GetPixelData().MulColor.a -= _DeltaTime;
		PuffRenderer_->GetTransform().SetWorldScale(GetTransform().GetWorldScale() + float4{ SumValue_ ,SumValue_ });
		PuffRenderer_->GetTransform().SetWorldRightMove(15.0f, _DeltaTime);
	}
	else if(true == IsTransTexture_ && 1.0f < SumTime_)
	{
		IsTransTexture_ = false;
		Death();
	}
}

