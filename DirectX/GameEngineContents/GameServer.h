#pragma once
#include <GameEngineBase/GameServerNetServer.h>
#include <GameEngineBase/GameServerNetClient.h>
#include <functional>


// ���� :
class GameServer
{
private:
	static std::shared_ptr<GameServer> Inst_;
	static bool ServerStart_;

public:
	static std::shared_ptr<GameServer> GetInst()
	{
		return Inst_;
	}

	bool IsServerStart()
	{
		return ServerStart_;
	}

	static bool IsHost_;
	static GameServerNet* Net;
	static UINT32 PlayersCount_;

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

	// ��Ŷ ó��
	void ObjectUpdatePacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	void ClientInitPacketProcess(std::shared_ptr<GameServerPacket> _Packet);
	void GameStatePacketProcess(std::shared_ptr<GameServerPacket> _Packet);

	// ����->Ŭ��
	void SendGameStatePacketToClient();

private:
	static GameServerNetServer Server;
	static GameServerNetClient Client;

};

