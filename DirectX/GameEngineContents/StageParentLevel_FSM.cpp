#include "PreCompile.h"
#include "StageParentLevel.h"
#include "PlayerActor.h"
#include "InGameSetUI.h"
#include "Cinemachine.h"
#include "IntroduceGame.h"

///////////////////////////
// �������� ������ �غ� �ܰ�
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


	// 1. �������� ȣ��Ʈ ���°� Ȯ�������� ChangeOver��ȣ ��
	if (false == GameServer::IsHost_ && GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_LoadingChangeOver))
	{
		if (false == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_LoadingChangeOver))
		{
			GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
		}
	}

	// 2. ȣ��Ʈ�� ������ ��
	if (true == GameServer::IsHost_ && GameServer::GetInst()->CheckServerSignal(ServerFlag::S_LoadingChangeOver))
	{
		if (true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_LoadingChangeOver))
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
	if (false == IdleEnd && _Info.StateTime > 7.0f)
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

	IntroduceGame_->Off();
	MainCam_->OnFreeCameraMode();

	// �ó׸ӽ� �۵�
	CinemaCam_->SetActivated();
}

void StageParentLevel::StagePreviewUpdate(float _DeltaTime, const StateInfo& _Info)
{
	
	// 1. �ó׸ӽ� ������ �غ�Ϸ�
}

///////////////////////////
// 3, 2, 1, GO!
///////////////////////////
void StageParentLevel::ReadyStart(const StateInfo& _Info)
{
	// ������ ȣ��Ʈ�� ��ȣ ��
	//GameServer::GetInst()->SubServerSignal(ServerFlag::StateChange);

	// ��� ���� ������ ȣ��Ʈ�� ���������� ���Դ�
	if (true == GameServer::IsHost_)
	{
		AllPlayersReady_ = false;
	}



	// ī�޶�� -> �÷��̾�� ����
	MainCam_->OffFreeCameraMode();
	CameraArm_->SetFollowCamera(MainCam_, Player_);

	//UIs_-> ī��Ʈ�ٿ� ��ŸƮ
	UIs_->CountdownStart();
}

void StageParentLevel::ReadyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// ������ ȣ��Ʈ�� ���������� ���Դ��� Ȯ���� �Ŀ� ��ȣ ��
	// �̷����� ȣ��Ʈ�� �������¿��� �Ѿ�� �� ����
	// ȣ��Ʈ�� �������� ��ȣ ��
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
// ���ݺ��� �޸� �� ����
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
// ���� 
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

