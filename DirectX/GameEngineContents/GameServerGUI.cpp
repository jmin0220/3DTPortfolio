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
			GameServer::GetInst()->SetServerSignal(ServerFlags::StateChange);
		}
	}
}

void GameServerGUI::InGameGUI()
{
	ImGui::Text(GameEngineString::AnsiToUTF8Return("@@@ 유저 @@@").c_str());
	{
		std::string Text = GameServer::IsHost_ == true ? "호스트" : "클라이언트";
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

	// 서버신호
	ImGui::NewLine();
	ImGui::Text(GameEngineString::AnsiToUTF8Return("@@@ 서버 신호 @@@").c_str());
	{
		std::string Text = "StateChangeSignal : ";
		Text += GameServer::GetInst()->CheckServerSignal(ServerFlags::StateChange) ? "1" : "0";
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
	}

	{
		std::string Text = "PlayerReady : ";
		Text += GameServer::GetInst()->CheckServerSignal(ServerFlags::PlayerReady) ? "1" : "0";
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
	}

	ImGui::NewLine();
	{
		std::string Text = "PlayerID : ";
		Text += std::to_string(GameServer::GetInst()->PlayerID_);
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
	}

	ImGui::NewLine();
	{
		std::string Text = "PlayerActorID : ";
		Text += PlayerActor::MainPlayer == nullptr ? "메인 플레이어 생성되지 않았음" : std::to_string(PlayerActor::GetPlayerID());
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
	}

	{
		int ActorsCount = GameServerObject::GetAllActorsCount();
		std::string Text = "모든 서버 오브젝트 수 : ";
		Text += std::to_string(ActorsCount);
		ImGui::Text(GameEngineString::AnsiToUTF8Return(Text).c_str());
		
	}
	
}
