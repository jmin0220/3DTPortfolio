#pragma once
#include <GameEngineBase/GameServerNetServer.h>
#include <GameEngineBase/GameServerNetClient.h>
#include <functional>


// ���� :
class GameServer
{
private:
	static std::shared_ptr<GameServer> Inst_;

public:
	static std::shared_ptr<GameServer> GetInst()
	{
		return Inst_;
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

private:
	static GameServerNetServer Server;
	static GameServerNetClient Client;

	std::map<__int64, std::shared_ptr<GameEngineActor>> AllServerActor;
};

