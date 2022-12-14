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

	PlayerStateManager_.ChangeState("Idle");
}


void PlayerActor::IdleStart(const StateInfo& _Info)
{
}

void PlayerActor::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	PlayerActType ActType = InputDetect();
	bool IsOnGround = CheckOnGround();

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
	IsTouchGround = false;
	IsDetachGround = true;
}

void PlayerActor::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{

	PlayerActType ActType = InputDetect();

	InputControllerMove(_DeltaTime);

	if (ActType == PlayerActType::Dive)
	{
		InputControllerDive(_DeltaTime);
		PlayerStateManager_.ChangeState("Dive");
		return;
	}

	if (CheckOnGround() == true)
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
	IsTouchGround = false;
	IsDetachGround = true;
}

void PlayerActor::DiveUpdate(float _DeltaTime, const StateInfo& _Info)
{

	PlayerActType ActType = InputDetect();
	if (CheckOnGround() == true)
	{
		PlayerStateManager_.ChangeState("Idle");
		return;
	}
}

void PlayerActor::DiveEnd(const StateInfo& _Info)
{
}

