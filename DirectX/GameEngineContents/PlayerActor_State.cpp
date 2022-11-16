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
		, std::bind(&PlayerActor::IdleStart, this, std::placeholders::_1));

	PlayerStateManager_.CreateStateMember("Jump"
		, std::bind(&PlayerActor::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PlayerActor::JumpStart, this, std::placeholders::_1)
		, std::bind(&PlayerActor::IdleStart, this, std::placeholders::_1));

	PlayerStateManager_.ChangeState("Idle");
}


void PlayerActor::IdleStart(const StateInfo& _Info)
{
}

void PlayerActor::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void PlayerActor::IdleEnd(const StateInfo& _Info)
{
}

void PlayerActor::RunStart(const StateInfo& _Info)
{
}

void PlayerActor::RunUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void PlayerActor::RunEnd(const StateInfo& _Info)
{
}

void PlayerActor::JumpStart(const StateInfo& _Info)
{
}

void PlayerActor::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void PlayerActor::JumpEnd(const StateInfo& _Info)
{
}

