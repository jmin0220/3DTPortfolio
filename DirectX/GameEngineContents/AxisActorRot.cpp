#include "PreCompile.h"
#include "AxisActorRot.h"


#include "GlobalValues.h"
#include "XAxisRot.h"
#include "YAxisRot.h"
#include "ZAxisRot.h"


AxisActorRot::AxisActorRot()
{
}

AxisActorRot::~AxisActorRot()
{
}

void AxisActorRot::Start()
{

	Option.IsRot = true;



	{
		XRenderer = CreateComponent<GameEngineTextureRenderer>();
		XRenderer->GetTransform().SetWorldScale({ 15.0f,125.0f,125.0f });
		XRenderer->GetRenderUnit().SetPipeLine("CustomColor");
		XRenderer->GetRenderUnit().EngineShaderResourcesSetting(XRenderer);

		XResultColor = float4(1.0f, 0.0f, 0.0f, 0.5f);
		Option.RenderPos = XRenderer->GetTransform().GetWorldPosition();
		XRenderer->GetShaderResources().SetConstantBufferLink("AxisData", Option);

	}

	{
		YRenderer = CreateComponent<GameEngineTextureRenderer>();
		YRenderer->GetTransform().SetWorldScale({ 125.0f,15.0f,125.0f });
		YRenderer->GetRenderUnit().SetPipeLine("CustomColor");
		YRenderer->GetRenderUnit().EngineShaderResourcesSetting(YRenderer);

		YResultColor = float4(0.0f, 1.0f, 0.0f, 0.5f);
		Option.RenderPos = YRenderer->GetTransform().GetWorldPosition();
		YRenderer->GetShaderResources().SetConstantBufferLink("AxisData", Option);


	}

	{
		ZRenderer = CreateComponent<GameEngineTextureRenderer>();
		ZRenderer->GetTransform().SetWorldScale({ 125.0f,125.0f,150.0f });
		ZRenderer->GetRenderUnit().SetPipeLine("CustomColor");
		ZRenderer->GetRenderUnit().EngineShaderResourcesSetting(ZRenderer);

		ZResultColor = float4(0.0f, 0.0f, 1.0f, 0.5f);
		Option.RenderPos = ZRenderer->GetTransform().GetWorldPosition();
		ZRenderer->GetShaderResources().SetConstantBufferLink("AxisData", Option);


	}
	//GetTransform().SetWorldRotation({ -10.0f, 20.0f, 0.0f });


	XAxisRot_ = GetLevel()->CreateActor<XAxisRot>();
	YAxisRot_ = GetLevel()->CreateActor<YAxisRot>();
	ZAxisRot_ = GetLevel()->CreateActor<ZAxisRot>();

	XAxisRot_->SetParent(this);
	YAxisRot_->SetParent(this);
	ZAxisRot_->SetParent(this);
}

void AxisActorRot::Update(float _DeltaTime)
{
	//CheckPickingRay();

	//메쉬의 포지션 
	//GetTransform().SetWorldPosition({ XAxis_->GetTransform().GetWorldPosition().x,
	//								  YAxis_->GetTransform().GetWorldPosition().y,
	//								  ZAxis_->GetTransform().GetWorldPosition().z });


	//XAxis_->GetTransform().SetWorldPosition({ XAxis_->GetTransform().GetWorldPosition().x,
	//										  YAxis_->GetTransform().GetWorldPosition().y,
	//										  ZAxis_->GetTransform().GetWorldPosition().z });

	//YAxis_->GetTransform().SetWorldPosition({ XAxis_->GetTransform().GetWorldPosition().x,
	//										  YAxis_->GetTransform().GetWorldPosition().y,
	//										  ZAxis_->GetTransform().GetWorldPosition().z });

	//ZAxis_->GetTransform().SetWorldPosition({ XAxis_->GetTransform().GetWorldPosition().x,
	//										  YAxis_->GetTransform().GetWorldPosition().y,
	//										  ZAxis_->GetTransform().GetWorldPosition().z });
}

void AxisActorRot::SetPosition()
{
	XAxisRot_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	YAxisRot_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	ZAxisRot_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
}
