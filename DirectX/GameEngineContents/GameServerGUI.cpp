#include "PreCompile.h"
#include "GameServerGUI.h"
#include <GameEngineCore/CoreMinimal.h>

#include "GameServer.h"
#include "GameServerObject.h"
#include "ServerPacket.h"
#include "PlayerActor.h"

GameServerGUI::GameServerGUI() 
{
}

GameServerGUI::~GameServerGUI() 
{
}

void GameServerGUI::Initialize(GameEngineLevel* _Level)
{
	LobbyLevel_ = _Level;
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
			// ȣ��Ʈ�� �ڽ��� �ε� �����ϰ�
			ContentsCore::GetInst()->ChangeLevelByLoading(LEVEL_NAME_DOORDASH);

			// ��� ����ڿ��� Falling -> Loading ���� �ٲٴ� ��ȣ
			GameServer::StateChangeSignal_ = 1;
		}
	}
}

void GameServerGUI::InGameGUI()
{
	{
		std::string Text = GameServer::IsHost_ == true ? "@@@ ȣ��Ʈ @@@" : "@@@ Ŭ���̾�Ʈ @@@";
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
		ImGui::NewLine();
	}
	
	{
		std::string Text = "�÷��̾� �� :";
		Text += std::to_string(GameServer::GetInst()->GetAllPlayersCount());
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
	}

	{
		std::string Text = "�÷��̾� �غ� :";
		Text += std::to_string(GameServer::GetInst()->GetAllPlayersReadyCount());
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
	}


	// ���� �����
	ImGui::NewLine();
	{
		std::string Text = "StateChangeSignal : ";
		Text += GameServer::StateChangeSignal_ == 1 ? "TRUE" : "FALSE";
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
	}

	{
		std::string Text = "ObjectUpdateSignal_ : ";
		Text += GameServer::ObjectUpdateSignal_ == 1 ? "TRUE" : "FALSE";
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
	}

	{
		std::string Text = "AllActorsCount : ";
		Text += std::to_string(GameServerObject::GetAllActorsCount());
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
	}

	ImGui::NewLine();
	{
		std::string Text = "PlayerID : ";
		Text += PlayerActor::MainPlayer == nullptr ? "���� �÷��̾� �������� �ʾ���" : std::to_string(PlayerActor::GetPlayerID());
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
	}
	
}
