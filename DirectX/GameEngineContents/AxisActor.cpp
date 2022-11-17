#include "PreCompile.h"
#include "AxisActor.h"


AxisActor::AxisActor() 
{
}

AxisActor::~AxisActor() 
{
}

void AxisActor::Start()
{

	XAxis_ = GetLevel()->CreateActor<PickableActor>();
	XAxis_->SetAxisMove({ 1.0f, 0.0f, 0.0f, 1.0f }, { 500.0f, 50.0f, 50.0f }, float4::RIGHT);
	XAxis_->SetParent(shared_from_this());
	XAxis_->GetTransform().SetLocalPosition({ 225.0f, 0.0f , 0.0f });

	YAxis_ = GetLevel()->CreateActor<PickableActor>();
	YAxis_->SetAxisMove({ 0.0f, 1.0f, 0.0f, 1.0f }, { 50.0f, 500.0f, 50.0f }, float4::UP);
	YAxis_->SetParent(shared_from_this());
	YAxis_->GetTransform().SetLocalPosition({ 0.0f, 225.0f, 0.0f });

	ZAxis_ = GetLevel()->CreateActor<PickableActor>();
	ZAxis_->SetAxisMove({ 0.0f, 0.0f, 0.5f, 1.0f }, { 50.0f, 50.0f, 500.0f }, float4::FORWARD);
	ZAxis_->SetParent(shared_from_this());
	ZAxis_->GetTransform().SetLocalPosition({ 0.0f, 0.0f, 225.0f });
}

void AxisActor::Update(float _DeltaTime)
{
	
}

