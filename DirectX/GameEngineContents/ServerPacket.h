#pragma once
#include <GameEngineBase/GameServerPacket.h>
#include "GameServerObject.h"

enum class ContentsPacketType
{
	ClientInit,			// Ŭ���̾�Ʈ�� ������ ������ ������ ��Ŷ
	ObjectUpdate,
	GameState,			// ������ ��, ��� �÷��̾� ���� ��

	Garbage				// ������ �̻��� ��Ŷ
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
	// ������, ������ Ŭ�󿡰� �����ִ� ��ȣ
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
	unsigned int Garbage = 0; // ������, ������ Ŭ�󿡰� �����ִ� ��ȣ

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