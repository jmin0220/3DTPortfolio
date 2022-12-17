#pragma once
#include <GameEngineBase/GameServerPacket.h>
#include "GameServerObject.h"

enum class ContentsPacketType
{
	ClientInit,			// 클라이언트가 들어오면 서버가 보내줄 패킷
	ObjectUpdate,
	GameState,			// 게임 전체 상태 컨트롤
	PlayerState,		// 플레이어의 정보(준비, 점수 등)

	Garbage,				// 가끔씩 이상한 패킷
};

class ClientInitPacket : public GameServerPacket
{
public:
	int ObjectID;

	ClientInitPacket()
	{
		SetPacketID(ContentsPacketType::ClientInit);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << ObjectID;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> ObjectID;
	}
};

class ObjectUpdatePacket : public GameServerPacket
{
public:
	int ObjectID;
	ServerObjectType Type;
	ServerObjectBaseState State;
	float4 Pos;
	float4 Rot;
	float4 Scale;
	std::string Animation;

	ObjectUpdatePacket()
	{
		SetPacketID(ContentsPacketType::ObjectUpdate);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << ObjectID;
		_Ser.WriteEnum(Type);
		_Ser.WriteEnum(State);
		_Ser << Pos;
		_Ser << Rot;
		_Ser << Scale;
		_Ser << Animation;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> ObjectID;
		_Ser.ReadEnum(Type);
		_Ser.ReadEnum(State);
		_Ser >> Pos;
		_Ser >> Rot;
		_Ser >> Scale;
		_Ser >> Animation;
	}
};

class GameStatePacket : public GameServerPacket
{
public:
	// 서버만, 서버가 클라에게 보내주는 "신호"
	unsigned int ServerSignal; 

	GameStatePacket()
	{
		SetPacketID(ContentsPacketType::GameState);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << ServerSignal;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> ServerSignal;
	}
};

class PlayerStatePacket : public GameServerPacket
{
public:
	// 호스트, 클라 전부 다 보내는 정보
	unsigned int PlayerID;
	unsigned int PlayerStateSignal;

	PlayerStatePacket()
	{
		SetPacketID(ContentsPacketType::PlayerState);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << PlayerID;
		_Ser << PlayerStateSignal;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> PlayerID;
		_Ser >> PlayerStateSignal;
	}
};

// 혹시나
class GarbagePacket : public GameServerPacket
{
public:
	unsigned int Garbage = 0;

	GarbagePacket()
	{
		SetPacketID(ContentsPacketType::Garbage);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << Garbage;

	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> Garbage;
	}
};