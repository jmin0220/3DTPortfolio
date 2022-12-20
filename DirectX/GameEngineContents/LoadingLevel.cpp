#include "PreCompile.h"
#include "LoadingLevel.h"
#include "LoadingActor.h"
#include "CustomableGUI.h"

#include <GameEngineBase/magic_enum.hpp>
#include "GameServerGUI.h"

LEVELS LoadingLevel::CurLoadingLevel_(LEVELS::NONE);
std::string_view LoadingLevel::StrCurLoadingLevel_;
bool LoadingLevel::AllPlayersReady_ = false;

void LoadingLevel::SetLoadingStage(std::string_view _Level)
{
	if (_Level == LEVEL_NAME_JUMPCLUB)
	{
		int a = 0;
	}
	CurLoadingLevel_ = ContentsCore::GetInst()->StringLevelToLEVELS(_Level);
	StrCurLoadingLevel_ = ContentsCore::GetInst()->StringLevelToStringSetLevel(_Level);
}

LoadingLevel::LoadingLevel()
	: SelectedMap_(MapSelect::NONE)
{
}

LoadingLevel::~LoadingLevel() 
{
}

void LoadingLevel::Start()
{
	
}

void LoadingLevel::Update(float _DeltaTime)
{
	// ���� ���������� �������� ���� �����ϵ���
	if (false == GameServer::GetInst()->IsServerStart())
	{
		if (LoadingProgress_ >= 0.999f)
		{
			GEngine::ChangeLevel(StrCurLoadingLevel_.data());
			return;
		}
	}

	// *. MidScore���� �� ������
	// ������ ���� ��ȣ ��
	if (true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_StageMidScoreChangeOver))
	{
		// ����
		if (false == GameServer::IsHost_)
		{
			GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
		}

		// �״��� ȣ��Ʈ
		else
		{
			if (GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_None))
			{
				GameServer::GetInst()->SetServerSignal(ServerFlag::S_None);
				GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_None);
			}
		}
	}

	// 3. ���� ���º���
	// ȣ��Ʈ
	if (true == GameServer::GetInst()->CheckServerSignal(ServerFlag::S_LoadingChangeReady))
	{

		if (true == GameServer::IsHost_)
		{
			// ȣ��Ʈ�� �������� �� �ٲ� �ڿ� �ٲ�
			if (true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_LoadingChangeOver))
			{
				GEngine::ChangeLevel(StrCurLoadingLevel_.data());
				return;
			}
		}
		// ����
		else
		{
			if (true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_LoadingChangeReady))
			{
				GEngine::ChangeLevel(StrCurLoadingLevel_.data());
				return;
			}
		}

	}

	
	// 2. ������ ������ȣ ���� (ȣ��Ʈ)
	if (!GameServer::GetInst()->CheckServerSignal(ServerFlag::S_LoadingChangeReady) && true == GameServer::IsHost_)
	{
		// �÷��̾� ���, �ڱ��ڽ� ���� Ȯ��
		if (true == GameServer::GetInst()->CheckOtherPlayersFlag(PlayerFlag::P_LoadingChangeReady)
			&& true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_LoadingChangeReady))
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_LoadingChangeReady);
			return;
		}
	}



	// 1. �ε� �Ϸ�� ���º��� �غ�(ȣ��Ʈ, ����)
	if (LoadingProgress_ >= 0.999f && !GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_LoadingChangeReady))
	{
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_LoadingChangeReady);
	}

}

// �������� ���������� �����ϴ°� �ƴ϶� ���ϴ� ���������� ������ �� �ֵ���
void LoadingLevel::LevelStartEvent()
{
	LevelChangeReady_ = false;
	LoadingComplete_ = false;

	// ���� 
	// ������ �ε������� �� �������� ȣ��Ʈ�� �Ѿ����� ���־����
	// MidScore���� ��
	// �������� ȣ��Ʈ�� ������ ChangeOver��ȣ�� ���ߵ�

	// �κ񿡼� �� ������
	if (false == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_StageMidScoreChangeReady))
	{
		if (false == GameServer::IsHost_)
		{
			GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_GameStartChangeOver);
		}
		// ȣ��Ʈ
		else
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_GameStartChangeOver);
		}
	}
	// MidScore���� �� ������
	else if (true == GameServer::GetInst()->CheckPlayerSignal(PlayerFlag::P_StageMidScoreChangeReady))
	{
		// ������ ȣ��Ʈ�� ��ȣ ��
		GameServer::GetInst()->SetPlayerSignal(PlayerFlag::P_StageMidScoreChangeOver);
		if (true == GameServer::IsHost_)
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_StageMidScoreChangeOver);
		}
	}



	// ~~ ����

	LoadingGUI_ = GameEngineGUI::CreateGUIWindow<CustomableGUI>("LoadingGUI", this);
	LoadingGUI_->SetGUIDebugFunc([=]() {ShowLoadingProgress(); });

	// ���� ����
	Loadings_ = CreateActor<LoadingActor>();


	// ������ �̿� �ε� ����
	LoadingProgress_ = 0.0f;
	if (CurLoadingLevel_ != LEVELS::NONE)
	{
		GameEngineCore::EngineThreadPool.Work(
			[=]()
			{
				ContentsCore::GetInst()->LoadLevelResource(CurLoadingLevel_);
			}
		);
	}

}

void LoadingLevel::LevelEndEvent()
{
	// ���� ����
	Loadings_->Death();

	LoadingGUI_->Death();


}

void LoadingLevel::ShowLoadingProgress()
{
	// ������ ��������
	{
		std::string MapName = magic_enum::enum_name(CurLoadingLevel_).data();
		ImGui::Text(("SelectedMap :" + MapName).c_str());
	}

	// ������ �������� �ε� ����
	{
		LoadingProgress_ = ContentsCore::GetInst()->GetLoadingProgress();
		std::string Out = "Loading... " + std::to_string(static_cast<int>(LoadingProgress_ * 100)) + " %";
		ImGui::Text(Out.c_str());
	}


}

LEVELS LoadingLevel::MapSelectToLevels()
{
	switch (SelectedMap_)
	{
	case MapSelect::Splash_CoY_DoorDash:
		return LEVELS::STAGE01_DOORDASH;
		break;
	case MapSelect::Splash_JumpClub:
		return LEVELS::STAGE02_JUMPCLUB;
		break;
	case MapSelect::Splash_Hexagone:
		return LEVELS::STAGE04_HEX_A_GONE;
		break;
	case MapSelect::Splash_HoopsLegends:
		return LEVELS::STAGE05_HOOPS_LEGENDS;
		break;
	default:
		return LEVELS::NONE;
		break;
	}
}

void LoadingLevel::ChangeLevelByMap()
{
	switch (SelectedMap_)
	{
	case MapSelect::Splash_CoY_DoorDash:
		GEngine::ChangeLevel(LEVEL_NAME_DOORDASH);
		break;
	case MapSelect::Splash_JumpClub:
		GEngine::ChangeLevel(LEVEL_NAME_JUMPCLUB);
		break;
	case MapSelect::Splash_Hexagone:
		GEngine::ChangeLevel(LEVEL_NAME_HEXAGONE);
		break;
	case MapSelect::Splash_HoopsLegends:
		GEngine::ChangeLevel(LEVEL_NAME_HOOPSLEGENDS);
		break;
	default:
		break;
	}

}
