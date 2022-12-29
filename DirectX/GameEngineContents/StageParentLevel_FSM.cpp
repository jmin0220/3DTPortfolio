#include "PreCompile.h"
#include "StageParentLevel.h"
#include "PlayerActor.h"
#include "InGameSetUI.h"
#include "Cinemachine.h"
#include "IntroduceGame.h"
#include "TimerActor.h"

#include "OptionActor.h"

///////////////////////////
// �������� ������ �غ� �ܰ�
///////////////////////////
bool IdleEnd = false;
bool AllUserOver = false;
void StageParentLevel::IdleStart(const StateInfo& _Info)
{
	// ����
	// �ε��������� �Ѿ�� ������
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
			//�迹�� : ���ӼҰ� �κ� ��� �߰�
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

	// 1. �������� ȣ��Ʈ ���°� Ȯ�������� ChangeOver��ȣ ��
	if (false == GameServer::IsHost_ 
		&& GameServer::GetInst()->CheckServerSignal(ServerFlag::S_LoadingChangeOver)
		&& GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_LoadingChangeOver))
	{
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
	}

	// 2. ȣ��Ʈ�� ������ ��
	if (true == GameServer::IsHost_ && GameServer::GetInst()->CheckServerSignal(ServerFlag::S_LoadingChangeOver))
	{
		if (true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_None))
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_None);
			GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
		}
	}

	
	// 5. �غ�Ϸ� ������ ���º������
	if (true == IdleEnd && true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_StageIdleChangeReady))
	{
		if (true == GameServer::IsHost_)
		{
			// ȣ��Ʈ�� ���� ���߿� ���º���
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


	// 4. ȣ��Ʈ�� ��� �غ� �Ϸ�Ǿ����� Ȯ��
	if (true == IdleEnd && true == GameServer::IsHost_)
	{
		if (true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StageIdleChangeReady))
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_StageIdleChangeReady);
		}
	}


	// 3. UI���� ���� ��ٸ� -> �غ�Ϸ�
	if (false == IdleEnd && _Info.StateTime > 8.0f)
	{
		IdleEnd = true;
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_StageIdleChangeReady);
		return;
	}


}

///////////////////////////
// ī�޶� �ó׸ӽ�
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
		//�迹�� : ���� �Ұ� ������ �Ұ� ��ݵ� ���� ����
		GlobalBGM::GetInst()->GetBGM().Stop();
	}
	MainCam_->OffFreeCameraMode();

	// �ó׸ӽ� �۵�
	CinemaCam_->SetActivated();
	{
		//�迹�� : �ó׸� ī�޶� ���۽� ������ ��� On
		GlobalBGM::GetInst()->SetBGM(GameEngineSound::SoundPlayControl("Ready_Go.mp3"));
		GlobalBGM::GetInst()->GetBGM().Volume(OptionActor::VolumeRatio_);
	}
}

void StageParentLevel::StagePreviewUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 1. ������ ���� ��ȣ ��
	if (false == GameServer::IsHost_
		&& GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageIdleChangeOver))
	{
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
	}

	// 2. ȣ��Ʈ�� ��ȣ ��
	if (true == GameServer::IsHost_)
	{
		if (GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_None))
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_None);
			GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
		}
	}

	// 5. ���º���
	if (GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StagePreviewChangeReady))
	{
		if (true == GameServer::IsHost_)
		{
			// ȣ��Ʈ�� ���� �� ����� �鰨
			if (true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StagePreviewChangeOver))
			{
				StageStateManager_.ChangeState("Ready");
				return;
			}
		}
		else
		{
			// �������� ����
			StageStateManager_.ChangeState("Ready");
			return;
		}
	}

	// 4. ������ ������ �غ� �ƴ��� Ȯ��
	if (true == GameServer::IsHost_ && GameServer::GetInst()->CheckServerSignal(ServerFlag::S_None))
	{
		// �ڱ� �ڽ� + ���� �غ� Ȯ��
		if (true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_StagePreviewChangeReady)
			&& true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StagePreviewChangeReady))
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_StagePreviewChangeReady);
		}
	}


	// 3. �ó׸ӽ� ������ �غ�Ϸ�
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
	// ������ ȣ��Ʈ�� ��ȣ ��
	GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_StagePreviewChangeOver);
	if (true == GameServer::IsHost_)
	{
		GameServer::GetInst()->SetServerSignal(ServerFlag::S_StagePreviewChangeOver);
	}


	// ī�޶�� -> �÷��̾�� ����
	MainCam_->OffFreeCameraMode();
	CameraArm_->SetFollowCamera(MainCam_, Player_);

	//UIs_-> ī��Ʈ�ٿ� ��ŸƮ
	UIs_->CountdownStart();
}

void StageParentLevel::ReadyUpdate(float _DeltaTime, const StateInfo& _Info)
{

	// ī��Ʈ�ٿ� ����Ǹ� ���º���
	// �÷��̾� ������ �� ����
	if (true == UIs_->IsCountDownEnd())
	{
		StageStateManager_.ChangeState("Race");
		return;
	}
}

///////////////////////////
// ���ݺ��� �޸� �� ����
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
	// 1. ������ ���� ��ȣ ��
	if (false == GameServer::IsHost_
		&& GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StagePreviewChangeOver) && false == FinishScoreSetted)
	{
		// �÷��̾� �Է� ����
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
	}

	// 2. ȣ��Ʈ�� ��ȣ ��
	if (true == GameServer::IsHost_)
	{
		if (GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_None) && false == FinishScoreSetted)
		{
			// �÷��̾� �Է� ����
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_StageRaceStart);
			GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
		}
	}

	if (false == RaceStartSignal && true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageRaceStart))
	{
		RaceStartSignal = true;
		Player_->SetInputAvailable(true);
	}


	// 5. ���º���
	if (GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageRaceChangeReady))
	{
		if (true == GameServer::IsHost_)
		{
			// ȣ��Ʈ�� ���� �� ����� �鰨
			if (true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StageRaceChangeOver))
			{
				StageStateManager_.ChangeState("End");
				return;
			}
		}
		else
		{
			// �������� ����
			StageStateManager_.ChangeState("End");
			return;
		}
	}

	// ������ �ڽ��� ���̽� ������� ����� Ű
	if (true == GameEngineInput::GetInst()->IsDown(KEY_ENTER))
	{
		Player_->SetGoal(true);
	}

	// 4. ȣ��Ʈ�� ��� �÷��̾� �غ�Ȯ��
	if (true == GameServer::IsHost_ 
		&& true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StageRaceChangeReady))
	{
		// �ڱ� �ڽ� + ���� �غ� Ȯ��
		if (true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_StageRaceChangeReady)
			&& true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_StageRaceChangeReady))
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_StageRaceChangeReady);
		}
	}


	// ����ȹ��
	if (true == Player_->GetIsGoal() && false == FinishScoreSetted)
	{
		FinishScoreSetted = true;

		// ���� ȹ��
		GetGameScoreByCurrentType();

		Player_->SetPlayerForze(true);
		Player_->SetPlayerNetDeath(true);
		Player_->SetPlayerInvisible();
	}

	// ���� : ���� �÷��̾�
	if (true == FinishScoreSetted && true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_StageRaceChangeReady))
	{
		if (true == GameEngineInput::GetInst()->IsDown(KEY_MOUSELEFT))
		{
			SetWatchCamNextPlayer();
		}
	}

	// 3. �÷��̾� �غ�
	if (true == Player_->GetIsGoal() && !GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_StageRaceChangeReady))
	{
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_StageRaceChangeReady);
	}
	
}

///////////////////////////
// ���� 
///////////////////////////
bool CheckOnce;
void StageParentLevel::EndStart(const StateInfo& _Info)
{
	CheckOnce = false;

	// ������ ȣ��Ʈ�� ��ȣ ��
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
	// 1. ������ ���� ��ȣ ��
	if (false == GameServer::IsHost_
		&& !GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_None)
		&& GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageRaceChangeOver))
	{
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
	}

	// 2. ȣ��Ʈ�� ��ȣ ��
	if (true == GameServer::IsHost_)
	{
		if (GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_None))
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_None);
			GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
		}
	}



	// ����������
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

		// �̵彺�ھ�� ���ҽ� �ε� ������ ���� ü����
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

