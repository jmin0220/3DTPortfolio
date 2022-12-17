#pragma once
#include <GameEngineBase/GameServerNetServer.h>
#include <GameEngineBase/GameServerNetClient.h>
#include <functional>
#include "ServerPacket.h"

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


	bool CheckOtherPlayersFlag(PlayerFlag _Flag);
	//int CheckOtherPlayersFlagCount(PlayerFlag _Flag);

	const std::map<int, std::shared_ptr<class PlayerStatePacket>>& GetAllPlayersInfo()
	{
		return AllPlayersInfo_;
	}

	static bool IsHost_;
	static GameServerNet* Net;
	static ServerFlag ServerSignal_;
	static PlayerFlag PlayerSignal_;
	static unsigned int PlayerID_;
	
	// 모든 유저 정보
	std::map<int, std::shared_ptr<class PlayerStatePacket>> AllPlayersInfo_;

	// 모든 UpdateObject 정보
	std::list<std::shared_ptr<ObjectUpdatePacket>> NewObjectUpdatePacketList_;

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
	void PlayerStatePacketProcess(std::shared_ptr<GameServerPacket> _Packet);

	// 모든 유저
	void SendPlayerStatePacket();

	// 서버->클라
	void SendGameStatePacket();
	bool CheckGameStatePacketSignal(unsigned int _PacketSignal, ServerFlag _Flag)
	{
		return _PacketSignal & _Flag;
	}

	bool CheckServerSignal(ServerFlag _Flag)
	{
		if (_Flag & ServerSignal_)
		{
			int tmp = static_cast<int>(ServerSignal_);
			if (tmp != 0)
			{
				GameEngineDebug::OutPutString("ServerSignalSended!! >> " + std::to_string(tmp));
			}

			//ServerSignal_ = static_cast<ServerFlag>(ServerSignal_ - _Flag);

			return true;
		}
		return false;
	}

	void SetServerSignal(ServerFlag _Flag)
	{
		ServerSignal_ = _Flag;
	}
	
	//void AddServerSignal(ServerFlag _Flag)
	//{
	//	if (false == (ServerSignal_ & _Flag))
	//	{
	//		ServerSignal_ = static_cast<ServerFlag>(ServerSignal_ | _Flag);
	//	}
	//}

	//void SubServerSignal(ServerFlag _Flag)
	//{
	//	if (ServerSignal_ & _Flag)
	//	{
	//		ServerSignal_ = static_cast<ServerFlag>(ServerSignal_ ^ _Flag);
	//	}
	//}


	bool CheckPlayerSignal(PlayerFlag _Flag)
	{
		return _Flag & PlayerSignal_;
	}

	void SetPlayerSignal(PlayerFlag _Flag)
	{
		PlayerSignal_ = _Flag;
	}

	//void AddPlayerSignal(PlayerFlag _Flag)
	//{
	//	if (false == (PlayerStateSignal_ & _Flag))
	//	{
	//		PlayerStateSignal_ = static_cast<PlayerFlag>(PlayerStateSignal_ | _Flag);
	//	}
	//}

	//void SubPlayerSignal(PlayerFlag _Flag)
	//{
	//	if (PlayerStateSignal_ & _Flag)
	//	{
	//		PlayerStateSignal_ = static_cast<PlayerFlag>(PlayerStateSignal_ ^ _Flag);
	//	}
	//}

};

