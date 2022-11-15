#include "PreCompile.h"
#include "ActorAxis.h"

#include "ActorPicker.h"
#include "AxisActor.h"
#include "AxisActorRot.h"

ActorAxis::ActorAxis()
{
}

ActorAxis::~ActorAxis()
{
}

void ActorAxis::Start()
{
	AxisMove_ = GetLevel()->CreateActor<AxisActor>();
	AxisMove_->SetParent(shared_from_this());

	AxisRot_ = GetLevel()->CreateActor<AxisActorRot>();
	AxisRot_->SetParent(shared_from_this());

	StateManager_.CreateStateMember("IdleMode"
		, std::bind(&ActorAxis::IdleModeUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&ActorAxis::IdleModeStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("MoveMode"
		, std::bind(&ActorAxis::MoveModeUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&ActorAxis::MoveModeStart, this, std::placeholders::_1));

	StateManager_.CreateStateMember("RotMode"
		, std::bind(&ActorAxis::RotModeUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&ActorAxis::RotModeStart, this, std::placeholders::_1));

	StateManager_.ChangeState("IdleMode");

	Mode_ = AXISMODE::MOVE;
}

void ActorAxis::Update(float _DeltaTime)
{
	if (nullptr != ActorPicker::SelectedActor.get())
	{
		GetTransform().SetWorldPosition(ActorPicker::SelectedActor.get()->GetTransform().GetWorldPosition());
	}

	StateManager_.Update(_DeltaTime);

}

void ActorAxis::IdleModeStart(const StateInfo& _Info)
{
	AxisMove_->Off();
	AxisRot_->Off();
}

void ActorAxis::IdleModeUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (nullptr != ActorPicker::SelectedActor)
	{
		switch (Mode_)
		{
		case AXISMODE::MOVE:
		{
			StateManager_.ChangeState("MoveMode");
			return;
		}
		case AXISMODE::ROT:
		{
			StateManager_.ChangeState("RotMode");
			return;
		}
		default:
			break;
		}
	}
}

void ActorAxis::MoveModeStart(const StateInfo& _Info)
{
	AxisMove_->On();
	AxisRot_->Off();

}

void ActorAxis::MoveModeUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (nullptr == ActorPicker::SelectedActor)
	{
		StateManager_.ChangeState("IdleMode");
		return;
	}

	if (Mode_ != AXISMODE::MOVE)
	{
		StateManager_.ChangeState("RotMode");
		return;
	}

	

}

void ActorAxis::RotModeStart(const StateInfo& _Info)
{
	AxisMove_->Off();
	AxisRot_->On();
}

void ActorAxis::RotModeUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (nullptr == ActorPicker::SelectedActor)
	{
		StateManager_.ChangeState("IdleMode");
		return;
	}

	if (Mode_ != AXISMODE::ROT)
	{
		StateManager_.ChangeState("RotMode");
		return;
	}

}