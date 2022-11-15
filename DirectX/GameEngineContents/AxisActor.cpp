#include "PreCompile.h"
#include "AxisActor.h"

#include "XAxis.h"
#include "YAxis.h"
#include "ZAxis.h"


AxisActor::AxisActor() 
{
}

AxisActor::~AxisActor() 
{
}

void AxisActor::Start()
{
	//{
	//	XRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	//	XRenderer_->GetTransform().SetWorldScale({ 125.0f,25.0f,25.0f });
	//	XRenderer_->GetTransform().SetWorldPosition({ 50.0f,0,0 });
	//	XRenderer_->SetPipeLine("Color");
	//	//XRenderer->SetMesh("Box");

	//	XRendererColor = float4(1.0f, 0.0f, 0.0f, 0.5f);
	//	XRenderer_->GetShaderResources().SetConstantBufferLink("ResultColor", XRendererColor);
	//}

	//
	//{
	//	YRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	//	YRenderer_->GetTransform().SetWorldScale({ 25.0f,125.0f,25.0f });
	//	YRenderer_->GetTransform().SetWorldPosition({ 0.0f,50.0f,0 });
	//	YRenderer_->SetPipeLine("Color");
	//	//YRenderer->SetMesh("Box");

	//	YRendererColor = float4(0.0f, 1.0f, 0.0f, 0.5f);
	//	YRenderer_->GetShaderResources().SetConstantBufferLink("ResultColor", YRendererColor);
	//}

	//{
	//	ZRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	//	ZRenderer_->GetTransform().SetWorldScale({ 25.0f,25.0f,125.0f });
	//	ZRenderer_->GetTransform().SetWorldPosition({ 0.0f,0,-50.0f });
	//	ZRenderer_->SetPipeLine("Color");
	//	//ZRenderer->SetMesh("Box");

	//	ZRendererColor = float4(0.0f, 0.0f, 1.0f, 0.5f);
	//	ZRenderer_->GetShaderResources().SetConstantBufferLink("ResultColor", ZRendererColor);
	//}


	XAxis_ = GetLevel()->CreateActor<PickableActor>();
	XAxis_->SetAxisMove({ 1.0f, 0.0f, 0.0f, 1.0f }, { 125.0f, 25.0f, 25.0f }, float4::RIGHT);
	XAxis_->SetParent(shared_from_this());
	XAxis_->GetTransform().SetLocalPosition({ 50.0f, 0.0f , 0.0f });

	YAxis_ = GetLevel()->CreateActor<PickableActor>();
	YAxis_->SetAxisMove({ 0.0f, 1.0f, 0.0f, 1.0f }, { 25.0f,125.0f,25.0f }, float4::UP);
	YAxis_->SetParent(shared_from_this());
	YAxis_->GetTransform().SetLocalPosition({ 0.0f, 50.0f, 0.0f });

	ZAxis_ = GetLevel()->CreateActor<PickableActor>();
	ZAxis_->SetAxisMove({ 0.0f, 0.0f, 0.5f, 1.0f }, { 25.0f,25.0f,125.0f }, float4::FORWARD);
	ZAxis_->SetParent(shared_from_this());
	ZAxis_->GetTransform().SetLocalPosition({ 0.0f, 0.0f, 50.0f });
}

void AxisActor::Update(float _DeltaTime)
{
	
}

void AxisActor::SetPosition()
{
	XAxis_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	YAxis_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	ZAxis_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
}
