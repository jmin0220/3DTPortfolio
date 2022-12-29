#include "PreCompile.h"
#include "StageParentLevel.h"
#include "PlayerActor.h"
#include "InGameSetUI.h"
#include "Cinemachine.h"
#include "IntroduceGame.h"
#include "TimerActor.h"

#include "OptionActor.h"

///////////////////////////
// 스테이지 시작전 준비 단계
///////////////////////////
bool IdleEnd = false;
bool AllUserOver = false;
void StageParentLevel::IdleStart(const StateInfo& _Info)
{
	// 서버
	// 로딩레벨에서 넘어온 유저들
	GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_LoadingChangeOver);
	if (true == GameServer::IsHost_)
	{
		GameServer::GetInst()->SetServerSignal(ServerFlag::S_LoadingChangeOver);
	}


	IdleEnd = false;

	if (true == GameServer::GetInst()->IsServerStart())
	{
		IntroduceGame_->On();
		{
			//김예나 : 게임소개 부분 브금 추가
			GlobalBGM::GetInst()->GetBGM().Stop();
			GlobalBGM::GetInst()->SetBGM(GameEngineSound::SoundPlayControl("Game_Intro.mp3"));
			GlobalBGM::GetInst()->GetBGM().Volume(OptionActor::VolumeRatio_);
		}
		IntroduceGame_->SetStageTexture(MyStage_);
		Player_->SetInputAvailable(false);
	}
	CameraArm_->SetFollowCamera(MainCam_, Player_);

	UIs_->OffSuccessCount();
	TimerUI_->Off();

	GameServer::RaceStart_ = false;
}

void StageParentLevel::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (false == GameServer::GetInst()->IsServerStart())
	{
		return;
	}

	// 1. 유저들은 호스트 들어온거 확인했으면 ChangeOver신호 끔
	if (false == GameServer::IsHost_ 
		&& GameServer::GetInst()->CheckServerSignal(ServerFlag::S_LoadingChangeOver)
		&& GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_LoadingChangeOver))
	{
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
	}

	// 2. 호스트도 들어오면 끔
	if (true == GameServer::IsHost_ && GameServer::GetInst()->CheckServerSignal(ServerFlag::S_LoadingChangeOver))
	{
		if (true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_None))
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
	if (false == IdleEnd && _Info.StateTime > 8.0f)
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

	UIs_->OnSuccessCount();
	
	if (MyStage_ == StageNum::STAGE2 || MyStage_ == StageNum::STAGE3
		|| MyStage_ == StageNum::STAGE5)
	{
		TimerUI_->On();
		TimerUI_->SetNetTime(TimerLimit_);
	}

	IntroduceGame_->Off();
	{
		//김예나 : 게임 소개 꺼지면 소개 브금도 같이 꺼짐
		GlobalBGM::GetInst()->GetBGM().Stop();
	}
	MainCam_->OffFreeCameraMode();

	// 시네머신 작동
	CinemaCam_->SetActivated();
	{
		//김예나 : 시네마 카메라 동작시 나오는 브금 On
		GlobalBGM::GetInst()->SetBGM(GameEngineSound::SoundPlayControl("Ready_Go.mp3"));
		GlobalBGM::GetInst()->GetBGM().Volume(OptionActor::VolumeRatio_);
	}
}

void StageParentLevel::StagePreviewUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 1. 유저가 먼저 신호 끔
	if (false == GameServer::IsHost_
		&& GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageIdleChangeOver))
	{
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
	}

	// 2. 호스트도 신호 끔
	if (true == GameServer::IsHost_)
	{
		if (GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_None))
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_None);
			GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
		}
	}

	// 5. 상태변경
	if (GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StagePreviewChangeReady))
	{
		if (true == GameServer::IsHost_)
		{
			// 호스트는 유저 다 변경시 들감
			if (true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StagePreviewChangeOver))
			{
				StageStateManager_.ChangeState("Ready");
				return;
			}
		}
		else
		{
			// 유저먼저 보냄
			StageStateManager_.ChangeState("Ready");
			return;
		}
	}

	// 4. 서버가 유저들 준비 됐는지 확인
	if (true == GameServer::IsHost_ && GameServer::GetInst()->CheckServerSignal(ServerFlag::S_None))
	{
		// 자기 자신 + 유저 준비 확인
		if (true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_StagePreviewChangeReady)
			&& true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StagePreviewChangeReady))
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_StagePreviewChangeReady);
		}
	}


	// 3. 시네머신 끝나면 준비완료
	if (true == CinemaCam_->IsEnd() 
		&& GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_None))
	{
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_StagePreviewChangeReady);
	}
}

///////////////////////////
// 3, 2, 1, GO!
///////////////////////////
void StageParentLevel::ReadyStart(const StateInfo& _Info)
{
	// 유저나 호스트나 신호 끔
	GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_StagePreviewChangeOver);
	if (true == GameServer::IsHost_)
	{
		GameServer::GetInst()->SetServerSignal(ServerFlag::S_StagePreviewChangeOver);
	}


	// 카메라암 -> 플레이어에게 세팅
	MainCam_->OffFreeCameraMode();
	CameraArm_->SetFollowCamera(MainCam_, Player_);

	//UIs_-> 카운트다운 스타트
	UIs_->CountdownStart();
}

void StageParentLevel::ReadyUpdate(float _DeltaTime, const StateInfo& _Info)
{

	// 카운트다운 종료되면 상태변경
	// 플레이어 움직일 수 있음
	if (true == UIs_->IsCountDownEnd())
	{
		StageStateManager_.ChangeState("Race");
		return;
	}
}

///////////////////////////
// 지금부터 달릴 수 있음
///////////////////////////
bool FinishScoreSetted;
bool RaceStartSignal;
void StageParentLevel::RaceStart(const StateInfo& _Info)
{
	FinishScoreSetted = false;
	RaceStartSignal = false;
}

void StageParentLevel::RaceUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 1. 유저가 먼저 신호 끔
	if (false == GameServer::IsHost_
		&& GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StagePreviewChangeOver) && false == FinishScoreSetted)
	{
		// 플레이어 입력 가능
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
	}

	// 2. 호스트도 신호 끔
	if (true == GameServer::IsHost_)
	{
		if (GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_None) && false == FinishScoreSetted)
		{
			// 플레이어 입력 가능
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_StageRaceStart);
			GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
		}
	}

	if (false == RaceStartSignal && true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageRaceStart))
	{
		RaceStartSignal = true;
		Player_->SetInputAvailable(true);
	}


	// 5. 상태변경
	if (GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageRaceChangeReady))
	{
		if (true == GameServer::IsHost_)
		{
			// 호스트는 유저 다 변경시 들감
			if (true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StageRaceChangeOver))
			{
				StageStateManager_.ChangeState("End");
				return;
			}
		}
		else
		{
			// 유저먼저 보냄
			StageStateManager_.ChangeState("End");
			return;
		}
	}

	// 강제로 자신의 레이스 종료상태 만드는 키
	if (true == GameEngineInput::GetInst()->IsDown(KEY_ENTER))
	{
		Player_->SetGoal(true);
	}

	// 4. 호스트는 모든 플레이어 준비확인
	if (true == GameServer::IsHost_ 
		&& true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StageRaceChangeReady))
	{
		// 자기 자신 + 유저 준비 확인
		if (true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_StageRaceChangeReady)
			&& true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StageRaceChangeReady))
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_StageRaceChangeReady);
		}
	}


	// 점수획득
	if (true == Player_->GetIsGoal() && false == FinishScoreSetted)
	{
		FinishScoreSetted = true;

		// 점수 획득
		GetGameScoreByCurrentType();

		Player_->SetPlayerForze(true);
		Player_->SetPlayerNetDeath(true);
		Player_->SetPlayerInvisible();
	}

	// 관전 : 다음 플레이어
	if (true == FinishScoreSetted && true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_StageRaceChangeReady))
	{
		if (true == GameEngineInput::GetInst()->IsDown(KEY_MOUSELEFT))
		{
			SetWatchCamNextPlayer();
		}
	}

	// 3. 플레이어 준비
	if (true == Player_->GetIsGoal() && !GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_StageRaceChangeReady))
	{
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_StageRaceChangeReady);
	}
	
}

///////////////////////////
// 종료 
///////////////////////////
bool CheckOnce;
void StageParentLevel::EndStart(const StateInfo& _Info)
{
	CheckOnce = false;

	// 유저나 호스트나 신호 끔
	GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_StageRaceChangeOver);
	if (true == GameServer::IsHost_)
	{
		GameServer::GetInst()->SetServerSignal(ServerFlag::S_StageRaceChangeOver);
	}

	TimerUI_->Off();
	UIs_->OnOffEnd();

	GameServer::RaceStart_ = false;
}

void StageParentLevel::EndUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 1. 유저가 먼저 신호 끔
	if (false == GameServer::IsHost_
		&& !GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_None)
		&& GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageRaceChangeOver))
	{
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
	}

	// 2. 호스트도 신호 끔
	if (true == GameServer::IsHost_)
	{
		if (GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_None))
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_None);
			GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
		}
	}



	// 다음레벨로
	if (true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_None))
	{

		if (false == CheckOnce)
		{
			CheckOnce = true;
			UIs_->Off();

			if (LEVEL_NAME_HOOPSLEGENDS == ContentsCore::GetInst()->GetCurStage())
			{
				ContentsCore::GetInst()->ChangeLevelByThread(LEVEL_NAME_WINNER);
				return;
			}
			else
			{
				ContentsCore::GetInst()->ChangeLevelByThread(LEVEL_NAME_MIDSCORE);
				return;
			}
		}

		// 미드스코어레벨 리소스 로딩 끝나면 레벨 체인지
		if (1 <= ContentsCore::GetInst()->GetLoadingProgress() && true == CheckOnce)
		{

			if (LEVEL_NAME_HOOPSLEGENDS == ContentsCore::GetInst()->GetCurStage())
			{
				GEngine::ChangeLevel(LEVEL_NAME_WINNER);
				return;
			}
			else
			{
				GEngine::ChangeLevel(LEVEL_NAME_MIDSCORE);
				return;
			}
		}

	}


}

