#include "PreCompile.h"
#include "GameServerGUI.h"
#include <GameEngineCore/CoreMinimal.h>

#include "GameServer.h"
#include "GameServerObject.h"
#include "ServerPacket.h"
#include "PlayerActor.h"
#include "LobbyPlayer.h"

#include <GameEngineBase/magic_enum.hpp>

bool GameServerGUI::GameStart_ = false;

GameServerGUI::GameServerGUI() 
{
}

GameServerGUI::~GameServerGUI() 
{
}

void GameServerGUI::Initialize(GameEngineLevel* _Level)
{
	LobbyLevel_ = _Level;

	for (int i = 0; i < static_cast<int>(PlayerColor::MAX); i++)
	{
		auto ColorName = magic_enum::enum_name<PlayerColor>(static_cast<PlayerColor>(i));
		PlayerColors_[i] = ColorName.data();
	}

	PrevColorIdx_ = -1;
}

void GameServerGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{

	if (ContentsCore::GetCurLevel() == LobbyLevel_)
	{
		LobbyGUI();
	}
	else
	{
		InGameGUI();
	}
}

void GameServerGUI::LobbyGUI()
{
	ImGui::Checkbox(GameEngineString::AnsiToUTF8Return("ȣ��Ʈ").c_str(), &GameServer::IsHost_);

	std::string Name = GameServer::IsHost_ == true ? "< I'm Host >" : "< I'm Client > ";
	ImGui::Text(Name.c_str());

	// ������ ��
	std::string PlayersCount = "������ �� : ";
	PlayersCount += std::to_string(GameServer::GetInst()->GetAllPlayersCount());
	ImGui::Text(GameEngineString::AnsiToUTF8Return(PlayersCount).c_str());

	ImGui::NewLine();

	// ȣ��Ʈ
	if (true == GameServer::IsHost_)
	{
		// ���ӽ��� ��ư
		if (ImGui::Button(GameEngineString::AnsiToUTF8Return("���ӽ���").c_str()))
		{
			GameStart_ = true;	
		}
	}

	// �÷��̾� �� ����?
	ImGui::Text(GameEngineString::AnsiToUTF8Return("ĳ���� ���� ����").c_str());
	
	//const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO", "PPPP", "QQQQQQQQQQ", "RRR", "SSSS" };

	static const char* current_item = NULL;
	
	static int ColorIdx = -1;
	if (ImGui::BeginCombo("##combo", current_item))
	{
		for (int n = 0; n < static_cast<int>(PlayerColor::MAX); n++)
		{
			bool is_selected = (current_item == PlayerColors_[n]);
			if (ImGui::Selectable(PlayerColors_[n], is_selected))
			{
				current_item = PlayerColors_[n];
				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
				ColorIdx = n;
			}
		}
		ImGui::EndCombo();
	}

	if (PrevColorIdx_ != ColorIdx)
	{
		GameServer::GetInst()->SetPlayerColorID(ColorIdx);
		//LobbyPlayer::SetPlayerColor();
		PrevColorIdx_ = ColorIdx;
	}

}

void GameServerGUI::InGameGUI()
{
	ImGui::Text(GameEngineString::AnsiToUTF8Return("@@@ ���� @@@").c_str());
	{
		std::string Text = GameServer::IsHost_ == true ? "ȣ��Ʈ" : "Ŭ���̾�Ʈ";
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
		ImGui::NewLine();
	}

	{
		std::string Text = "���� �������� :";
		Text += ContentsCore::GetInst()->GetCurStage();
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
	}


	{
		std::string Text = "���� �� :";
		Text += std::to_string(GameServer::GetInst()->GetAllPlayersCount());
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
	}


	// ������ȣ�� ����
	ImGui::NewLine();
	{
		std::string Text = "���� ��ȣ(ȣ��Ʈ) : ";

		if (ServerFlag::S_None == GameServer::ServerSignal_)
		{
			Text += "None";
		}
		else if (ServerFlag::S_GameStartChangeReady & GameServer::ServerSignal_)
		{
			Text += "S_GameStartChangeReady";
		}
		else if (ServerFlag::S_LoadingChangeReady & GameServer::ServerSignal_)
		{
			Text += "S_LoadingChangeReady";
		}
		else if (ServerFlag::S_StageIdleChangeReady & GameServer::ServerSignal_)
		{
			Text += "S_StageIdleChangeReady";
		}
		else if (ServerFlag::S_StagePreviewChangeReady & GameServer::ServerSignal_)
		{
			Text += "S_StagePreviewChangeReady";
		}
		else if (ServerFlag::S_StageMidScoreChangeReady & GameServer::ServerSignal_)
		{
			Text += "S_StageMidScoreChangeReady";
		}
		else if (ServerFlag::S_StageRaceChangeReady & GameServer::ServerSignal_)
		{
			Text += "S_StageRaceChangeReady";
		}
		else if (ServerFlag::S_StageEndChangeReady & GameServer::ServerSignal_)
		{
			Text += "S_StageEndChangeReady";
		}
		else if (ServerFlag::S_GameStartChangeOver & GameServer::ServerSignal_)
		{
			Text += "S_GameStartChangeOver";
		}
		else if (ServerFlag::S_LoadingChangeOver & GameServer::ServerSignal_)
		{
			Text += "S_LoadingChangeOver";
		}
		else if (ServerFlag::S_StageIdleChangeOver & GameServer::ServerSignal_)
		{
			Text += "S_StageIdleChangeOver";
		}
		else if (ServerFlag::S_StagePreviewChangeOver & GameServer::ServerSignal_)
		{
			Text += "S_StagePreviewChangeOver";
		}
		else if (ServerFlag::S_StageMidScoreChangeOver & GameServer::ServerSignal_)
		{
			Text += "S_StageMidScoreChangeOver";
		}
		else if (ServerFlag::S_StageRaceChangeOver & GameServer::ServerSignal_)
		{
			Text += "S_StageRaceChangeOver";
		}
		else if (ServerFlag::S_StageEndChangeOver & GameServer::ServerSignal_)
		{
			Text += "S_StageEndChangeOver";
		}

		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
	}

	// �ڽ��� ����
	ImGui::NewLine();
	ImGui::Text(GameEngineString::AnsiToUTF8Return("< �� ���� >").c_str());
	{
		std::string Text = "�÷��̾� ��ȣ : ";

		if (PlayerFlag::P_None == GameServer::PlayerSignal_)
		{
			Text += "None";
		}
		else if (PlayerFlag::P_GameStartChangeReady & GameServer::PlayerSignal_)
		{
			Text += "P_GameStartChangeReady";
		}
		else if (PlayerFlag::P_LoadingChangeReady & GameServer::PlayerSignal_)
		{
			Text += "P_LoadingChangeReady";
		}
		else if (PlayerFlag::P_StageIdleChangeReady & GameServer::PlayerSignal_)
		{
			Text += "P_StageIdleChangeReady";
		}
		else if (PlayerFlag::P_StagePreviewChangeReady & GameServer::PlayerSignal_)
		{
			Text += "P_StagePreviewChangeReady";
		}
		else if (PlayerFlag::P_StageMidScoreChangeReady & GameServer::PlayerSignal_)
		{
			Text += "P_StageMidScoreChangeReady";
		}
		else if (PlayerFlag::P_StageRaceChangeReady & GameServer::PlayerSignal_)
		{
			Text += "P_StageRaceChangeReady";
		}
		else if (PlayerFlag::P_StageEndChangeReady & GameServer::PlayerSignal_)
		{
			Text += "P_StageEndChangeReady";
		}
		else if (PlayerFlag::P_GameStartChangeOver & GameServer::PlayerSignal_)
		{
			Text += "P_GameStartChangeOver";
		}
		else if (PlayerFlag::P_LoadingChangeOver & GameServer::PlayerSignal_)
		{
			Text += "P_LoadingChangeOver";
		}
		else if (PlayerFlag::P_StageIdleChangeOver & GameServer::PlayerSignal_)
		{
			Text += "P_StageIdleChangeOver";
		}
		else if (PlayerFlag::P_StagePreviewChangeOver & GameServer::PlayerSignal_)
		{
			Text += "P_StagePreviewChangeOver";
		}
		else if (PlayerFlag::P_StageMidScoreChangeOver & GameServer::PlayerSignal_)
		{
			Text += "P_StageMidScoreChangeOver";
		}
		else if (PlayerFlag::P_StageRaceChangeOver & GameServer::PlayerSignal_)
		{
			Text += "P_StageRaceChangeOver";
		}
		else if (PlayerFlag::P_StageEndChangeOver & GameServer::PlayerSignal_)
		{
			Text += "P_StageEndChangeOver";
		}

		Text += "\n- �÷��̾� ���� : " + std::to_string(GameServer::GetInst()->PlayerScore_);
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());

	}

	ImGui::NewLine();
	// �ٸ� ������� ����
	ImGui::Text(GameEngineString::AnsiToUTF8Return("< �ٸ� �÷��̾� ���� >").c_str());
	{
		std::map<int, std::shared_ptr<class PlayerStatePacket>> PlayersInfo = GameServer::GetInst()->GetAllPlayersInfo();
		std::map<int, std::shared_ptr<class PlayerStatePacket>>::iterator Start = PlayersInfo.begin();
		std::map<int, std::shared_ptr<class PlayerStatePacket>>::iterator End = PlayersInfo.end();

		for (; Start != End; ++Start)
		{
			unsigned int PlayerID = (*Start).second->PlayerID;
			PlayerFlag Flag = static_cast<PlayerFlag>((*Start).second->PlayerStateSignal);
			unsigned int Score = (*Start).second->PlayerScore;
			{
				std::string Text = " PlayerID : ";
				Text += std::to_string(PlayerID);
				Text += "  [";

				if (false == Flag)
				{
					Text += "None";
				}
				else if (PlayerFlag::P_GameStartChangeReady & Flag)
				{
					Text += "P_GameStartChangeReady";
				}
				else if (PlayerFlag::P_LoadingChangeReady & Flag)
				{
					Text += "P_LoadingChangeReady";
				}
				else if (PlayerFlag::P_StageIdleChangeReady & Flag)
				{
					Text += "P_StageIdleChangeReady";
				}
				else if (PlayerFlag::P_StagePreviewChangeReady & Flag)
				{
					Text += "P_StagePreviewChangeReady";
				}
				else if (PlayerFlag::P_StageMidScoreChangeReady & Flag)
				{
					Text += "P_StageMidScoreChangeReady";
				}
				else if (PlayerFlag::P_StageRaceChangeReady & Flag)
				{
					Text += "P_StageRaceChangeReady";
				}
				else if (PlayerFlag::P_StageEndChangeReady & Flag)
				{
					Text += "P_StageEndChangeReady";
				}
				else if (PlayerFlag::P_GameStartChangeOver & Flag)
				{
					Text += "P_GameStartChangeOver";
				}
				else if (PlayerFlag::P_LoadingChangeOver & Flag)
				{
					Text += "P_LoadingChangeOver";
				}
				else if (PlayerFlag::P_StageIdleChangeOver & Flag)
				{
					Text += "P_StageIdleChangeOver";
				}
				else if (PlayerFlag::P_StagePreviewChangeOver & Flag)
				{
					Text += "P_StagePreviewChangeOver";
				}
				else if (PlayerFlag::P_StageMidScoreChangeOver & Flag)
				{
					Text += "P_StageMidScoreChangeOver";
				}
				else if (PlayerFlag::P_StageRaceChangeOver & Flag)
				{
					Text += "P_StageRaceChangeOver";
				}
				else if (PlayerFlag::P_StageEndChangeOver & Flag)
				{
					Text += "P_StageEndChangeOver";
				}

				Text += " ]\n";
				Text += " - �÷��̾� ���� : " + std::to_string(Score);
				ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
			}
		}
	}
	
}
