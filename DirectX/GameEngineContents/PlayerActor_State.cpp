#include "PreCompile.h"
#include "PlayerActor.h"

void PlayerActor::CreateFSMStates()
{
	PlayerStateManager_.CreateStateMember("Idle"
		, std::bind(&PlayerActor::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PlayerActor::IdleStart, this, std::placeholders::_1)
		, std::bind(&PlayerActor::IdleEnd, this, std::placeholders::_1));

	PlayerStateManager_.CreateStateMember("Run"
		, std::bind(&PlayerActor::RunUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PlayerActor::RunStart, this, std::placeholders::_1)
		, std::bind(&PlayerActor::RunEnd, this, std::placeholders::_1));

	PlayerStateManager_.CreateStateMember("Jump"
		, std::bind(&PlayerActor::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PlayerActor::JumpStart, this, std::placeholders::_1)
		, std::bind(&PlayerActor::JumpEnd, this, std::placeholders::_1));

	PlayerStateManager_.CreateStateMember("Dive"
		, std::bind(&PlayerActor::DiveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PlayerActor::DiveStart, this, std::placeholders::_1)
		, std::bind(&PlayerActor::DiveEnd, this, std::placeholders::_1));

	PlayerStateManager_.CreateStateMember("DiveGetUp"
		, std::bind(&PlayerActor::DiveGetUpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PlayerActor::DiveGetUpStart, this, std::placeholders::_1)
		, std::bind(&PlayerActor::DiveGetUpEnd, this, std::placeholders::_1));

	PlayerStateManager_.CreateStateMember("CannotControl"
		, std::bind(&PlayerActor::CannotControlUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PlayerActor::CannotControlStart, this, std::placeholders::_1)
		, std::bind(&PlayerActor::CannotControlEnd, this, std::placeholders::_1));

	PlayerStateManager_.ChangeState("Idle");
}


void PlayerActor::IdleStart(const StateInfo& _Info)
{
}

void PlayerActor::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	PlayerActType ActType = InputDetect();
	bool IsOnGround = CheckOnGround();

	if (IsUnControlable_ == true)
	{
		InputControllerMove(_DeltaTime);
		PlayerStateManager_.ChangeState("CannotControl");
		return;
	}


	if (ActType == PlayerActType::Dive)
	{
		InputControllerDive(_DeltaTime);
		PlayerStateManager_.ChangeState("Dive");
		return;
	}

	if (ActType == PlayerActType::Jump && CheckOnGround() == true)
	{
		InputControllerJump(_DeltaTime);
		PlayerStateManager_.ChangeState("Jump");
		return;
	}


	if (ActType == PlayerActType::Run)
	{
		InputControllerMove(_DeltaTime);
		PlayerStateManager_.ChangeState("Run");
		return;
	}
}

void PlayerActor::IdleEnd(const StateInfo& _Info)
{
}

void PlayerActor::RunStart(const StateInfo& _Info)
{
}

void PlayerActor::RunUpdate(float _DeltaTime, const StateInfo& _Info)
{
	PlayerActType ActType = InputDetect();

	bool IsOnGround = CheckOnGround();

	InputControllerMove(_DeltaTime);

	if (IsUnControlable_ == true)
	{
		InputControllerMove(_DeltaTime);
		PlayerStateManager_.ChangeState("CannotControl");
		return;
	}

	if (ActType == PlayerActType::Dive)
	{
		InputControllerDive(_DeltaTime);
		PlayerStateManager_.ChangeState("Dive");
		return;
	}

 	if (ActType == PlayerActType::Jump && CheckOnGround() == true)
	{
		InputControllerJump(_DeltaTime);
		PlayerStateManager_.ChangeState("Jump");
		return;
	}

	if (ActType == PlayerActType::Idle)
	{
		PlayerStateManager_.ChangeState("Idle");
		return;
	}
}

void PlayerActor::RunEnd(const StateInfo& _Info)
{
}

void PlayerActor::JumpStart(const StateInfo& _Info)
{
	//IsTouchGround = false;
	//IsDetachGround = true;
	waitphysx_ = false;
}

void PlayerActor::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (IsUnControlable_ == true)
	{
		InputControllerMove(_DeltaTime);
		PlayerStateManager_.ChangeState("CannotControl");
		return;
	}

	PlayerActType ActType = InputDetect();

	InputControllerMove(_DeltaTime);

	if (ActType == PlayerActType::Dive)
	{
		InputControllerDive(_DeltaTime);
		PlayerStateManager_.ChangeState("Dive");
		return;
	}

	if (CheckOnGround() == true && waitphysx_ == true)
	{
		PlayerStateManager_.ChangeState("Idle");
		return;
	}

}

void PlayerActor::JumpEnd(const StateInfo& _Info)
{
}

void PlayerActor::DiveStart(const StateInfo& _Info)
{
	//IsTouchGround = false;
	//IsDetachGround = true;
	StandUpDelay_ = 0.0f;
	waitphysx_ = false;
	IsDiving_ = false;
}

void PlayerActor::DiveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	
	PlayerActType ActType = InputDetect();

	if (IsUnControlable_ == true)
	{
		InputControllerMove(_DeltaTime);
		PlayerStateManager_.ChangeState("CannotControl");
		return;
	}


	if ((CheckOnGround() == true  && waitphysx_ == true) ||
		IsDiving_ == true)
	{
		IsDiving_ = true;
		StandUpDelay_ += _DeltaTime;
		if (StandUpDelay_ > 0.1f)
		{
			PlayerStateManager_.ChangeState("DiveGetUp");
		}
	}


}

void PlayerActor::DiveEnd(const StateInfo& _Info)
{
}

void PlayerActor::DiveGetUpStart(const StateInfo& _Info)
{
}

void PlayerActor::DiveGetUpUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (IsUnControlable_ == true)
	{
		InputControllerMove(_DeltaTime);
		PlayerStateManager_.ChangeState("CannotControl");
		return;
	}

	if (StandUp(_DeltaTime) == true)
	{
		PlayerStateManager_.ChangeState("Idle");
		IsTouchGround = true;
		IsDetachGround = false;
	}


}

void PlayerActor::DiveGetUpEnd(const StateInfo& _Info)
{
}

void PlayerActor::CannotControlStart(const StateInfo& _Info)
{
	DynamicActorComponent_->SetUnlockAxis();
}

void PlayerActor::CannotControlUpdate(float _DeltaTime, const StateInfo& _Info)
{

	UnControlableTime_ += _DeltaTime;

	if (UnControlableTime_ > 2.0f && CheckOnGround() == true)
	{
		if (StandUp(_DeltaTime) == true)
		{
			IsUnControlable_ = false;
			DynamicActorComponent_->SetlockAxis();
			PlayerStateManager_.ChangeState("DiveGetUp");
		}
	}


}

void PlayerActor::CannotControlEnd(const StateInfo& _Info)
{
}



