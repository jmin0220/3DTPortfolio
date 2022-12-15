#include "PreCompile.h"
#include "BigShots_Puff.h"

BigShots_Puff::BigShots_Puff() 
	: IsTransTexture_(false)
	, SumTime_(0.0f)
	, SumValue_(20.0f)
{
}

BigShots_Puff::~BigShots_Puff() 
{
}

void BigShots_Puff::Start()
{
	PuffRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	PuffRenderer_->SetTexture("VFX_SomePuff_02.png");
	PuffRenderer_->GetTransform().SetWorldScale({ SumValue_,SumValue_,0 });
	PuffRenderer_->SetRenderingOrder(10);
}

void BigShots_Puff::Update(float _DeltaTime)
{
	if(false == IsTransTexture_ && 1.0f > SumTime_)
	{
		SumTime_ += _DeltaTime;
		SumValue_ += 0.1f;
		PuffRenderer_->GetPixelData().MulColor.a -= _DeltaTime * 0.8f;
		PuffRenderer_->GetTransform().SetWorldScale(GetTransform().GetWorldScale() + float4{ SumValue_ ,SumValue_ });
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
	}
	else if(true == IsTransTexture_ && 1.0f < SumTime_)
	{
		IsTransTexture_ = false;
		Death();
	}

	if (0.0f >= PuffRenderer_->GetPixelData().MulColor.a)
	{
		PuffRenderer_->GetPixelData().MulColor.a = 0.0f;
	}
}

