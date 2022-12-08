#pragma once
#include <GameEngineBase/GameServerPacket.h>
#include "GameServerObject.h"

enum class ContentsPacketType
{
	ClientInit,			// 클라이언트가 들어오면 서버가 보내줄 패킷
	ObjectUpdate,
	GameState,			// 접속자 수, 모든 플레이어 레디 등

	Garbage				// 가끔씩 이상한 패킷
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
	// 서버만, 서버가 클라에게 보내주는 신호
	unsigned int StateChangeSignal; 
	unsigned int ObjectUpdateSignal;

	unsigned int PlayerID;
	unsigned int PlayerReady; // 0 or 1

	GameStatePacket()
	{
		SetPacketID(ContentsPacketType::GameState);
	}

	virtual void Serialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::Serialize(_Ser);
		_Ser << StateChangeSignal;
		_Ser << ObjectUpdateSignal;
		_Ser << PlayerID;
		_Ser << PlayerReady;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> StateChangeSignal;
		_Ser >> ObjectUpdateSignal;
		_Ser >> PlayerID;
		_Ser >> PlayerReady;
	}
};

class GarbagePacket : public GameServerPacket
{
public:
	unsigned int Garbage = 0; // 서버만, 서버가 클라에게 보내주는 신호

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