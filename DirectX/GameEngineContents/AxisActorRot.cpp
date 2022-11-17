#include "PreCompile.h"
#include "AxisActorRot.h"


#include "GlobalValues.h"



AxisActorRot::AxisActorRot()
{
}

AxisActorRot::~AxisActorRot()
{
}

void AxisActorRot::Start()
{

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
