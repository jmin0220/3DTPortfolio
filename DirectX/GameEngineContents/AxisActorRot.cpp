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

	//Option.IsRot = true;



	//{
	//	XRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	//	XRenderer_->GetTransform().SetWorldScale({ 15.0f,125.0f,125.0f });
	//	XRenderer_->GetRenderUnit().SetPipeLine("CustomColor");
	//	XRenderer_->GetRenderUnit().EngineShaderResourcesSetting(XRenderer_);

	//	XResultColor = float4(1.0f, 0.0f, 0.0f, 0.5f);
	//	//Option.RenderPos = XRenderer->GetTransform().GetWorldPosition();
	//	//XRenderer->GetShaderResources().SetConstantBufferLink("AxisData", Option);

	//}

	//{
	//	YRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	//	YRenderer_->GetTransform().SetWorldScale({ 125.0f,15.0f,125.0f });
	//	YRenderer_->GetRenderUnit().SetPipeLine("CustomColor");
	//	YRenderer_->GetRenderUnit().EngineShaderResourcesSetting(YRenderer_);

	//	YResultColor = float4(0.0f, 1.0f, 0.0f, 0.5f);
	//	//Option.RenderPos = YRenderer->GetTransform().GetWorldPosition();
	//	//YRenderer->GetShaderResources().SetConstantBufferLink("AxisData", Option);


	//}

	//{
	//	ZRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	//	ZRenderer_->GetTransform().SetWorldScale({ 125.0f,125.0f,150.0f });
	//	ZRenderer_->GetRenderUnit().SetPipeLine("CustomColor");
	//	ZRenderer_->GetRenderUnit().EngineShaderResourcesSetting(ZRenderer_);

	//	ZResultColor = float4(0.0f, 0.0f, 1.0f, 0.5f);
	//	//Option.RenderPos = ZRenderer->GetTransform().GetWorldPosition();
	//	//ZRenderer->GetShaderResources().SetConstantBufferLink("AxisData", Option);


	//}
	//GetTransform().SetWorldRotation({ -10.0f, 20.0f, 0.0f });


	XAxisRot_ = GetLevel()->CreateActor<PickableActor>();
	XAxisRot_->SetAxisRot(float4::GREEN, { 100, 100, 100 });

	YAxisRot_ = GetLevel()->CreateActor<PickableActor>();
	YAxisRot_->SetAxisRot(float4::GREEN, { 100, 100, 100 });

	ZAxisRot_ = GetLevel()->CreateActor<PickableActor>();
	ZAxisRot_->SetAxisRot(float4::GREEN, { 100, 100, 100 });

	XAxisRot_->SetParent(shared_from_this());
	YAxisRot_->SetParent(shared_from_this());
	ZAxisRot_->SetParent(shared_from_this());
}

void AxisActorRot::Update(float _DeltaTime)
{

}

void AxisActorRot::SetPosition()
{
	XAxisRot_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	YAxisRot_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	ZAxisRot_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
}
