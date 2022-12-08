#pragma once
#include <GameEngineBase/GameServerNetServer.h>
#include <GameEngineBase/GameServerNetClient.h>
#include <functional>


// 설명 :
class GameServer
{
private:
	static std::shared_ptr<GameServer> Inst_;
	static bool ServerStart_;
	static GameServerNetServer Server;
	static GameServerNetClient Client;

public:
	static std::shared_ptr<GameServer> GetInst()
	{
		return Inst_;
	}

	bool IsServerStart()
	{
		return ServerStart_;
	}

	int GetAllPlayersCount()
	{
		return static_cast<int>(AllPlayersInfo_.size()) + 1;
	}

	int GetAllPlayersReadyCount();

	// 호스트만 호출해서 사용
	bool IsPlayersReady()
	{
		return GetAllPlayersCount() == GetAllPlayersReadyCount();
	}
	

	static bool IsHost_;
	static GameServerNet* Net;
	static ServerFlags ServerSignal_;
	static unsigned int PlayerID_;
	
	std::map<int, std::shared_ptr<class GameStatePacket>> AllPlayersInfo_;

public:
	// constrcuter destructer
	GameServer();
	~GameServer();

	// delete Function
	GameServer(const GameServer& _Other) = delete;
	GameServer(GameServer&& _Other) noexcept = delete;
	GameServer& operator=(const GameServer& _Other) = delete;
	GameServer& operator=(GameServer&& _Other) noexcept = delete;

	void ServerStart();
	void ServerEnd();

	// 패킷 처리
	void ObjectUpdatePacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	void ClientInitPacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	void GameStatePacketProcess(std::shared_ptr<GameServerPacket> _Packet);

	// 서버->클라
	void SendGameStatePacket();
	bool CheckGameStatePacketSignal(unsigned int _Signal, ServerFlags _Flag)
	{
		if (ServerFlags::PlayerReady & _Signal )
		{
			return true;
		}
		else if (ServerFlags::ResourceLoad & _Signal)
		{
			return true;
		}
		else if (ServerFlags::StateChange & _Signal)
		{
			return true;
		}
		else if (ServerFlags::ServerObjectsSpawnCompleted & _Signal)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool CheckServerSignal(ServerFlags _Flag)
	{
		return _Flag & ServerSignal_;
	}

	void SetServerSignal(ServerFlags _Flag)
	{
		ServerSignal_ = _Flag;
	}
	
	void AddServerSignal(ServerFlags _Flag)
	{
		ServerSignal_ = static_cast<ServerFlags>(ServerSignal_ | _Flag);
	}

	void SubServerSignal(ServerFlags _Flag)
	{
		if (ServerSignal_ & _Flag)
		{
			ServerSignal_ = static_cast<ServerFlags>(ServerSignal_ ^ _Flag);
		}
	}

	unsigned int GetClientSignal()
	{
		
	}


	ServerFlags& GetServerSignal()
	{
		return ServerSignal_;
	}

};

