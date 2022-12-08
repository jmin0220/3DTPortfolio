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
	ImGui::Checkbox(GameEngineString::AnsiToUTF8Return("호스트").c_str(), &GameServer::IsHost_);

	std::string Name = GameServer::IsHost_ == true ? "< I'm Host >" : "< I'm Client > ";
	ImGui::Text(Name.c_str());

	// 접속자 수
	std::string PlayersCount = "접속자 수 : ";
	PlayersCount += std::to_string(GameServer::GetInst()->GetAllPlayersCount());
	ImGui::Text(GameEngineString::AnsiToUTF8Return(PlayersCount).c_str());

	ImGui::NewLine();

	// 호스트
	if (true == GameServer::IsHost_)
	{
		// 게임시작 버튼
		if (ImGui::Button(GameEngineString::AnsiToUTF8Return("게임시작").c_str()))
		{
			// 호스트는 자신이 로딩 시작하고
			ContentsCore::GetInst()->ChangeLevelByLoading(LEVEL_NAME_DOORDASH);

			// 모든 사용자에게 Falling -> Loading 으로 바꾸는 신호
			GameServer::StateChangeSignal_ = 1;
		}
	}
}

void GameServerGUI::InGameGUI()
{
	{
		std::string Text = GameServer::IsHost_ == true ? "@@@ 호스트 @@@" : "@@@ 클라이언트 @@@";
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
		ImGui::NewLine();
	}
	
	{
		std::string Text = "플레이어 수 :";
		Text += std::to_string(GameServer::GetInst()->GetAllPlayersCount());
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
	}

	{
		std::string Text = "플레이어 준비 :";
		Text += std::to_string(GameServer::GetInst()->GetAllPlayersReadyCount());
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
	}


	// 상태 디버깅
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
		Text += PlayerActor::MainPlayer == nullptr ? "메인 플레이어 생성되지 않았음" : std::to_string(PlayerActor::GetPlayerID());
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
	}
	
}
