#include "PreCompile.h"
#include "GameServerGUI.h"
#include <GameEngineCore/CoreMinimal.h>

#include "GameServer.h"
#include "ServerPacket.h"

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
	std::string Name = "FPS : " + std::to_string(GameEngineTime::GetFPS());
	ImGui::Text(Name.c_str());
	// printf �����ε� �Ⱦ�.

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
	PlayersCount += std::to_string(GameServer::PlayersCount_);
	ImGui::Text(GameEngineString::AnsiToUTF8Return(PlayersCount).c_str());

}

void GameServerGUI::InGameGUI()
{

	if (true == GameServer::IsHost_)
	{
		/// ȣ��Ʈ ȭ�� ///


		// ���ӽ��� ��ư
		if (ImGui::Button(GameEngineString::AnsiToUTF8Return("���ӽ���").c_str()))
		{
			// ��� ����ڿ��� Falling -> Loading ���� �ٲٴ� ��ȣ
		}
	}
	else
	{
		/// Ŭ���̾�Ʈ ȭ�� ///

	}

}
