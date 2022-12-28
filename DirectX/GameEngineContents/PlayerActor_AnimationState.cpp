#include "PreCompile.h"
#include "PlayerActor.h"

void PlayerActor::CreateAnimationFSMStates()
{
	PlayerAniStateManager_.CreateStateMember("Idle"
		, std::bind(&PlayerActor::IdleAniUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PlayerActor::IdleAniStart, this, std::placeholders::_1)
		, std::bind(&PlayerActor::IdleAniEnd, this, std::placeholders::_1));

	PlayerAniStateManager_.CreateStateMember("Walk"
		, std::bind(&PlayerActor::WalkAniUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PlayerActor::WalkAniStart, this, std::placeholders::_1)
		, std::bind(&PlayerActor::WalkAniEnd, this, std::placeholders::_1));

	PlayerAniStateManager_.CreateStateMember("Run"
		, std::bind(&PlayerActor::RunAniUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PlayerActor::RunAniStart, this, std::placeholders::_1)
		, std::bind(&PlayerActor::RunAniEnd, this, std::placeholders::_1));

	PlayerAniStateManager_.CreateStateMember("Jump_Start"
		, std::bind(&PlayerActor::JumpStartAniUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PlayerActor::JumpStartAniStart, this, std::placeholders::_1)
		, std::bind(&PlayerActor::JumpStartAniEnd, this, std::placeholders::_1));

	PlayerAniStateManager_.CreateStateMember("Jump_MidAir"
		, std::bind(&PlayerActor::JumpMidAirAniUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PlayerActor::JumpMidAirAniStart, this, std::placeholders::_1)
		, std::bind(&PlayerActor::JumpMidAirAniEnd, this, std::placeholders::_1));

	PlayerAniStateManager_.CreateStateMember("Jump_Landing"
		, std::bind(&PlayerActor::JumpLandingAniUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PlayerActor::JumpLandingAniStart, this, std::placeholders::_1)
		, std::bind(&PlayerActor::JumpLandingAniEnd, this, std::placeholders::_1));

	PlayerAniStateManager_.CreateStateMember("Dive_Loop"
		, std::bind(&PlayerActor::DiveLoopAniUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PlayerActor::DiveLoopAniStart, this, std::placeholders::_1)
		, std::bind(&PlayerActor::DiveLoopAniEnd, this, std::placeholders::_1));

	PlayerAniStateManager_.CreateStateMember("Dive_GetUp"
		, std::bind(&PlayerActor::DiveGetUpAniUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PlayerActor::DiveGetUpAniStart, this, std::placeholders::_1)
		, std::bind(&PlayerActor::DiveGetUpAniEnd, this, std::placeholders::_1));

	PlayerAniStateManager_.CreateStateMember("Ragdoll"
		, std::bind(&PlayerActor::CannotControlAniUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PlayerActor::CannotControlAniStart, this, std::placeholders::_1)
		, std::bind(&PlayerActor::CannotControlAniEnd, this, std::placeholders::_1));

	PlayerAniStateManager_.ChangeState("Idle");
}


void PlayerActor::IdleAniStart(const StateInfo& _Info)
{
	FbxRenderer_->ChangeAnimation("Idle");
	CurAniName = "Idle";
}

void PlayerActor::IdleAniUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (PlayerStateManager_.GetCurStateStateName() == "CannotControl")
	{
		PlayerAniStateManager_.ChangeState("Ragdoll");
		return;
	}

	if (PlayerStateManager_.GetCurStateStateName() == "Run"
		|| PlayerStateManager_.GetCurStateStateName() == "Idle")
	{
		if (PlayerXZSpeed_ > 1.0f)
		{
			PlayerAniStateManager_.ChangeState("Walk");
			return;
		}
	}

	if (PlayerStateManager_.GetCurStateStateName() == "Jump")
	{
		PlayerAniStateManager_.ChangeState("Jump_MidAir");
		return;
	}

	if (PlayerStateManager_.GetCurStateStateName() == "Dive")
	{
		PlayerAniStateManager_.ChangeState("Dive_Loop");
		return;
	}
}

void PlayerActor::IdleAniEnd(const StateInfo& _Info)
{
}

void PlayerActor::WalkAniStart(const StateInfo& _Info)
{
	FbxRenderer_->ChangeAnimation("Walk");
	CurAniName = "Walk";
}

void PlayerActor::WalkAniUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (PlayerStateManager_.GetCurStateStateName() == "CannotControl")
	{
		PlayerAniStateManager_.ChangeState("Ragdoll");
		return;
	}

	if (PlayerStateManager_.GetCurStateStateName() == "Run"
		|| PlayerStateManager_.GetCurStateStateName() == "Idle")
	{
		if (PlayerXZSpeed_ > 10.0f)
		{
			PlayerAniStateManager_.ChangeState("Run");
			return;
		}

		if (PlayerXZSpeed_ < 1.0f)
		{
			PlayerAniStateManager_.ChangeState("Idle");
			return;
		}
	}

	if (PlayerStateManager_.GetCurStateStateName() == "Jump")
	{
		PlayerAniStateManager_.ChangeState("Jump_MidAir");
		return;
	}

	if (PlayerStateManager_.GetCurStateStateName() == "Dive")
	{
		PlayerAniStateManager_.ChangeState("Dive_Loop");
		return;
	}

}

void PlayerActor::WalkAniEnd(const StateInfo& _Info)
{
}

void PlayerActor::RunAniStart(const StateInfo& _Info)
{
	FbxRenderer_->ChangeAnimation("Run");
	CurAniName = "Run";
}

void PlayerActor::RunAniUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (PlayerStateManager_.GetCurStateStateName() == "CannotControl")
	{
		PlayerAniStateManager_.ChangeState("Ragdoll");
		return;
	}

	if (PlayerStateManager_.GetCurStateStateName() == "Run" 
		|| PlayerStateManager_.GetCurStateStateName() == "Idle")
	{
		if (PlayerXZSpeed_ < 10.0f)
		{
			PlayerAniStateManager_.ChangeState("Walk");
			return;
		}
	}

	if (PlayerStateManager_.GetCurStateStateName() == "Jump")
	{
		PlayerAniStateManager_.ChangeState("Jump_MidAir");
		return;
	}

	if (PlayerStateManager_.GetCurStateStateName() == "Dive")
	{
		PlayerAniStateManager_.ChangeState("Dive_Loop");
		return;
	}

}

void PlayerActor::RunAniEnd(const StateInfo& _Info)
{
}

void PlayerActor::JumpStartAniStart(const StateInfo& _Info)
{
	//Jump_Start 애니메이션이 끝나면 알아서 Idle 상태로 이동 (B애니메이션 생성때 AnimationBindEnd 함수 활용함
	FbxRenderer_->ChangeAnimation("Jump_Start");
	CurAniName = "Jump_Start";
}

void PlayerActor::JumpStartAniUpdate(float _DeltaTime, const StateInfo& _Info)
{

}

void PlayerActor::JumpStartAniEnd(const StateInfo& _Info)
{
}


void PlayerActor::JumpMidAirAniStart(const StateInfo& _Info)
{
	FbxRenderer_->ChangeAnimation("Jump_MidAir");
	CurAniName = "Jump_MidAir";
}

void PlayerActor::JumpMidAirAniUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (PlayerStateManager_.GetCurStateStateName() == "CannotControl")
	{
		PlayerAniStateManager_.ChangeState("Ragdoll");
		return;
	}

	if (PlayerStateManager_.GetCurStateStateName() == "Idle")
	{
		PlayerAniStateManager_.ChangeState("Idle");
	}

	if (PlayerStateManager_.GetCurStateStateName() == "Dive")
	{
		PlayerAniStateManager_.ChangeState("Dive_Loop");
		return;
	}
}

void PlayerActor::JumpMidAirAniEnd(const StateInfo& _Info)
{
}

void PlayerActor::JumpLandingAniStart(const StateInfo& _Info)
{
	//Jump_Landing 애니메이션이 끝나면 알아서 Idle 상태로 이동 (B애니메이션 생성때 AnimationBindEnd 함수 활용함
	//FbxRenderer_->ChangeAnimation("Jump_Landing");
}

void PlayerActor::JumpLandingAniUpdate(float _DeltaTime, const StateInfo& _Info)
{

}

void PlayerActor::JumpLandingAniEnd(const StateInfo& _Info)
{
}

void PlayerActor::DiveLoopAniStart(const StateInfo& _Info)
{
	//Jump_Landing 애니메이션이 끝나면 알아서 Idle 상태로 이동 (B애니메이션 생성때 AnimationBindEnd 함수 활용함
	FbxRenderer_->ChangeAnimation("Dive_Loop");
	CurAniName = "Dive_Loop";
}

void PlayerActor::DiveLoopAniUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (PlayerStateManager_.GetCurStateStateName() == "CannotControl")
	{
		PlayerAniStateManager_.ChangeState("Ragdoll");
		return;
	}

	if (StandUpDelay_ > 0.01f)
	{
		PlayerAniStateManager_.ChangeState("Dive_GetUp");
	}
}

void PlayerActor::DiveLoopAniEnd(const StateInfo& _Info)
{
}

void PlayerActor::DiveGetUpAniStart(const StateInfo& _Info)
{
	//Jump_Landing 애니메이션이 끝나면 알아서 Idle 상태로 이동 (B애니메이션 생성때 AnimationBindEnd 함수 활용함
	FbxRenderer_->ChangeAnimation("Dive_GetUp");
	CurAniName = "Dive_GetUp";
}

void PlayerActor::DiveGetUpAniUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (PlayerStateManager_.GetCurStateStateName() == "CannotControl")
	{
		PlayerAniStateManager_.ChangeState("Ragdoll");
		return;
	}

	if (PlayerStateManager_.GetCurStateStateName() == "Idle")
	{
		PlayerAniStateManager_.ChangeState("Idle");
		return;
	}
}

void PlayerActor::DiveGetUpAniEnd(const StateInfo& _Info)
{
}

void PlayerActor::CannotControlAniStart(const StateInfo& _Info)
{
	//Jump_Landing 애니메이션이 끝나면 알아서 Idle 상태로 이동 (B애니메이션 생성때 AnimationBindEnd 함수 활용함
	FbxRenderer_->ChangeAnimation("Ragdoll");
	CurAniName = "Ragdoll";
}

void PlayerActor::CannotControlAniUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (PlayerStateManager_.GetCurStateStateName() == "Idle")
	{
		PlayerAniStateManager_.ChangeState("Idle");
		return;
	}

	if (PlayerStateManager_.GetCurStateStateName() == "DiveGetUp")
	{
		PlayerAniStateManager_.ChangeState("Dive_GetUp");
	}
}

void PlayerActor::CannotControlAniEnd(const StateInfo& _Info)
{
}



