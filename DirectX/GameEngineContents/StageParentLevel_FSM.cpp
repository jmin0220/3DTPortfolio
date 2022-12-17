#include "PreCompile.h"
#include "StageParentLevel.h"
#include "PlayerActor.h"
#include "InGameSetUI.h"
#include "Cinemachine.h"
#include "IntroduceGame.h"

///////////////////////////
// 스테이지 시작전 준비 단계
///////////////////////////

bool IdleEnd = false;
bool AllUserOver = false;
void StageParentLevel::IdleStart(const StateInfo& _Info)
{
	IdleEnd = false;

	IntroduceGame_->On();
	CameraArm_->SetFollowCamera(MainCam_, Player_);
}

void StageParentLevel::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SpawnServerObjects();


	// 1. 유저들은 호스트 들어온거 확인했으면 ChangeOver신호 끔
	if (false == GameServer::IsHost_ && GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_LoadingChangeOver))
	{
		if (false == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_LoadingChangeOver))
		{
			GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
		}
	}

	// 2. 호스트도 들어오면 끔
	if (true == GameServer::IsHost_ && GameServer::GetInst()->CheckServerSignal(ServerFlag::S_LoadingChangeOver))
	{
		if (true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_LoadingChangeOver))
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_None);
			GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
		}
	}

	
	// 5. 준비완료 됐으면 상태변경시작
	if (true == IdleEnd && true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_StageIdleChangeReady))
	{
		if (true == GameServer::IsHost_)
		{
			// 호스트는 제일 나중에 상태변경
			if (true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StageIdleChangeOver))
			{
				StageStateManager_.ChangeState("StagePreview");
				return;
			}
		}
		else
		{
			if (true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageIdleChangeReady))
			{
				StageStateManager_.ChangeState("StagePreview");
				return;
			}
		}
	}


	// 4. 호스트는 모두 준비 완료되었는지 확인
	if (true == IdleEnd && true == GameServer::IsHost_)
	{
		if (true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StageIdleChangeReady))
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_StageIdleChangeReady);
		}
	}


	// 3. UI띄우고 몇초 기다림 -> 준비완료
	if (false == IdleEnd && _Info.StateTime > 7.0f)
	{
		IdleEnd = true;
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_StageIdleChangeReady);
		return;
	}


}

///////////////////////////
// 카메라 시네머신
///////////////////////////
void StageParentLevel::StagePreviewStart(const StateInfo& _Info)
{
	GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_StageIdleChangeOver);
	if (true == GameServer::IsHost_)
	{
		GameServer::GetInst()->SetServerSignal(ServerFlag::S_StageIdleChangeOver);
	}

	IntroduceGame_->Off();
	MainCam_->OnFreeCameraMode();

	// 시네머신 작동
	CinemaCam_->SetActivated();
}

void StageParentLevel::StagePreviewUpdate(float _DeltaTime, const StateInfo& _Info)
{
	
	// 1. 시네머신 끝나면 준비완료
}

///////////////////////////
// 3, 2, 1, GO!
///////////////////////////
void StageParentLevel::ReadyStart(const StateInfo& _Info)
{
	// 유저나 호스트나 신호 끔
	//GameServer::GetInst()->SubServerSignal(ServerFlag::StateChange);

	// 모든 유저 다음에 호스트가 마지막으로 들어왔다
	if (true == GameServer::IsHost_)
	{
		AllPlayersReady_ = false;
	}



	// 카메라암 -> 플레이어에게 세팅
	MainCam_->OffFreeCameraMode();
	CameraArm_->SetFollowCamera(MainCam_, Player_);

	//UIs_-> 카운트다운 스타트
	UIs_->CountdownStart();
}

void StageParentLevel::ReadyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 유저는 호스트가 마지막으로 들어왔는지 확인한 후에 신호 끔
	// 이래야지 호스트도 이전상태에서 넘어올 수 있음
	// 호스트가 들어왔으면 신호 끔
	if (false == AllPlayersReady_)
	{
		//GameServer::GetInst()->SetPlayerSignal(PlayerFlag::Wait);
	}








	if (true == GameEngineInput::GetInst()->IsDown(KEY_ENTER))
	{
		StageStateManager_.ChangeState("Race");
		return;
	}
}

///////////////////////////
// 지금부터 달릴 수 있음
///////////////////////////
void StageParentLevel::RaceStart(const StateInfo& _Info)
{
	UIs_->OnOffSuccessCount();
}

void StageParentLevel::RaceUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_ENTER))
	{
		UIs_->OnOffSuccessCount();
		StageStateManager_.ChangeState("End");
		return;
	}
}

///////////////////////////
// 종료 
///////////////////////////
void StageParentLevel::EndStart(const StateInfo& _Info)
{
	UIs_->OnOffEnd();
}

void StageParentLevel::EndUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_ENTER))
	{
		return;
	}
}

