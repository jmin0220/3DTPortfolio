#pragma once
#include <GameEngineBase/GameServerNetServer.h>
#include <GameEngineBase/GameServerNetClient.h>
#include <functional>
#include "ServerPacket.h"
#include "GlobalValues.h"


struct ServerPlayerInfo
{
	unsigned int ID_;
	unsigned int Color_;
	unsigned int Score_;
	std::string Name_;
};

// 설명 :
class GameServer
{
private:
	static std::shared_ptr<GameServer> Inst_;
	static bool ServerStart_;
	static GameServerNetServer Server;
	static GameServerNetClient Client;

	static bool IdSmaller(ServerPlayerInfo& _Left, ServerPlayerInfo& _Right)
	{
		return _Left.ID_ < _Right.ID_;
	}

public:
	static std::shared_ptr<GameServer>& GetInst()
	{
		return Inst_;
	}

	bool IsServerStart()
	{
		return ServerStart_;
	}

	int GetAllPlayersCount()
	{
		return static_cast<int>(OtherPlayersInfo_.size()) + 1;
	}


	bool CheckOtherPlayersFlag(PlayerFlag _Flag);
	unsigned int CheckOtherPlayersFlagCount(PlayerFlag _Flag);
	bool CheckHostFlag(PlayerFlag _Flag);

	std::map<int, std::shared_ptr<class PlayerStatePacket>>& GetOtherPlayersInfo()
	{
		return OtherPlayersInfo_;
	}
	
	void GetAllPlayersInfo(std::vector<ServerPlayerInfo>& _PlayerInfos)
	{
		_PlayerInfos.clear();

		std::map<int, std::shared_ptr<class PlayerStatePacket>>::iterator StartIt = OtherPlayersInfo_.begin();
		std::map<int, std::shared_ptr<class PlayerStatePacket>>::iterator EndIt = OtherPlayersInfo_.end();

		for (; StartIt != EndIt; ++StartIt)
		{
			std::shared_ptr<PlayerStatePacket> Packet = (*StartIt).second;
			_PlayerInfos.emplace_back(Packet->PlayerID, Packet->PlayerColor, Packet->PlayerScore, Packet->PlayerName);
		}

		// 자기정보도 넣는다
		ServerPlayerInfo MyInfo;
		MyInfo.ID_ = PlayerID_;
		MyInfo.Color_ = PlayerColorID_;
		MyInfo.Score_ = PlayerScore_;
		MyInfo.Name_ = UserName_;
		_PlayerInfos.push_back(MyInfo);

		std::sort(_PlayerInfos.begin(), _PlayerInfos.end(), IdSmaller);
	}

	// ID + float4
	void SetPlayerColorID(unsigned int _PlayerColor)
	{
		PlayerColorID_ = _PlayerColor;

		switch (static_cast<PlayerColor>(PlayerColorID_))
		{
		case PlayerColor::PINK:
		{
			PlayerColor_ = float4(0.93f, 0.21f, 0.54f);
			break;
		}
		case PlayerColor::RED:
		{
			PlayerColor_ = float4(0.93f, 0.21f, 0.21f);
			break;
		}
		case PlayerColor::GREEN:
		{
			PlayerColor_ = float4(0.21f, 0.93f, 0.21f);
			break;
		}
		case PlayerColor::BLUE:
		{
			PlayerColor_ = float4(0.37f, 0.64f, 0.91f);
			break;
		}
		case PlayerColor::BLACK:
		{
			PlayerColor_ = float4(0.21f, 0.21f, 0.21f);
			break;
		}
		case PlayerColor::WHITE:
		{
			PlayerColor_ = float4(0.93f, 0.93f, 0.93f);
			break;
		}
		default:
			PlayerColor_ = float4::ZERO;
			break;
		}
	}

	float4 GetPlayerColorReturn(unsigned int _PlayerColor)
	{
		switch (static_cast<PlayerColor>(_PlayerColor))
		{
		case PlayerColor::PINK:
		{
			return float4(0.93f, 0.21f, 0.54f);
			break;
		}
		case PlayerColor::RED:
		{
			return float4(0.93f, 0.21f, 0.21f);
			break;
		}
		case PlayerColor::GREEN:
		{
			return float4(0.21f, 0.93f, 0.21f);
			break;
		}
		case PlayerColor::BLUE:
		{
			return float4(0.37f, 0.64f, 0.91f);
			break;
		}
		case PlayerColor::BLACK:
		{
			return float4(0.21f, 0.21f, 0.21f);
			break;
		}
		case PlayerColor::WHITE:
		{
			return float4(0.93f, 0.93f, 0.93f);
			break;
		}
		default:
			return float4::ZERO;
			break;
		}
	}

	static bool IsHost_;
	static GameServerNet* Net;
	static ServerFlag ServerSignal_;
	static PlayerFlag PlayerSignal_;
	static unsigned int PlayerID_;
	static unsigned int PlayerColorID_;
	static float4 PlayerColor_;
	static unsigned int PlayerScore_;
	static unsigned int PlayTime_;
	static std::string UserName_;
	static bool RaceStart_;
	
	// 모든 유저 정보
	std::map<int, std::shared_ptr<class PlayerStatePacket>> OtherPlayersInfo_;

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
		return _Flag == ServerSignal_;
	}

	void SetServerSignal(ServerFlag _Flag)
	{
		ServerSignal_ = _Flag;
	}

	bool CheckPlayerSignal(PlayerFlag _Flag)
	{
		return _Flag == PlayerSignal_;
	}

	void SetPlayerSignal(PlayerFlag _Flag)
	{
		PlayerSignal_ = _Flag;
	}

};

