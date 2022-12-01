#include "PreCompile.h"
#include "GameServerGUI.h"
#include <GameEngineCore/CoreMinimal.h>

#include "ServerLevel.h"
#include "ServerPacket.h"

GameServerGUI::GameServerGUI() 
{
}

GameServerGUI::~GameServerGUI() 
{
}

void GameServerGUI::Initialize(GameEngineLevel* _Level)
{
	ServerLevel_ = _Level;
}

void GameServerGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	int FPS = static_cast<int>(1.0f / _DeltaTime);
	// printf �����ε� �Ⱦ�.

	if (ContentsCore::GetCurLevel() != ServerLevel_)
	{
		LobbyGUI();
	}
	else
	{
		ServerGUI();
	}
}

void GameServerGUI::LobbyGUI()
{
	std::string Name = "FPS : " + std::to_string(GameEngineTime::GetFPS());
	ImGui::Text(Name.c_str());

	// ��ư
	if (true == ImGui::Button("Create Host"))
	{
		ServerLevel::IsHost_ = true;
		GEngine::ChangeLevel("ServerLevel");
	}

	ImGui::SameLine();
	if (true == ImGui::Button("Connect Server"))
	{
		ServerLevel::IsHost_ = false;
		GEngine::ChangeLevel("ServerLevel");
	}
}

void GameServerGUI::ServerGUI()
{
	std::string Name = "FPS : " + std::to_string(GameEngineTime::GetFPS());
	ImGui::Text(Name.c_str());

	if (true == ImGui::Button("Send Data"))
	{
		std::shared_ptr<ObjectUpdatePacket> Packet = std::make_shared<ObjectUpdatePacket>();

		Packet->ObjectID = 1;
		Packet->Scale = { 1.0f, 122.f, 122.f };
		Packet->Pos = { 999.0f, 999.f, 999.f };
		Packet->Rot = { 45.0f, 45.f, 45.f };
		Packet->Animation = "Idle";

		ServerLevel::Net->SendPacket(Packet);
	}
}
