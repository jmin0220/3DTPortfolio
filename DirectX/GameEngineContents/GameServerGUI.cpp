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
	// printf 형식인데 안씀.

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
	ImGui::Checkbox(GameEngineString::AnsiToUTF8Return("호스트").c_str(), &GameServer::IsHost_);

	std::string Name = GameServer::IsHost_ == true ? "< I'm Host >" : "< I'm Client > ";
	ImGui::Text(Name.c_str());

	// 접속자 수
	std::string PlayersCount = "접속자 수 : ";
	PlayersCount += std::to_string(GameServer::PlayersCount_);
	ImGui::Text(GameEngineString::AnsiToUTF8Return(PlayersCount).c_str());

}

void GameServerGUI::InGameGUI()
{

	if (true == GameServer::IsHost_)
	{
		/// 호스트 화면 ///


		// 게임시작 버튼
		if (ImGui::Button(GameEngineString::AnsiToUTF8Return("게임시작").c_str()))
		{
			// 모든 사용자에게 Falling -> Loading 으로 바꾸는 신호
		}
	}
	else
	{
		/// 클라이언트 화면 ///

	}

}
