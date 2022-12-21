#pragma once
#include <GameEngineBase/GameServerPacket.h>
#include "GameServerObject.h"

enum class ContentsPacketType
{
	ClientInit,			// Ŭ���̾�Ʈ�� ������ ������ ������ ��Ŷ
	ObjectUpdate,
	GameState,			// ���� ��ü ���� ��Ʈ��
	PlayerState,		// �÷��̾��� ����(�غ�, ���� ��)

	Garbage,				// ������ �̻��� ��Ŷ
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
	std::string Animation;		// �÷��̾� : �ִϸ��̼�, ��Ÿ : ���ڿ� ���� �ʿ��ϸ� ����
	unsigned int PlayerColor;	// �÷��̾� : ��Ų����, ��Ÿ : ...
	float4 CannonInfo;
	
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
		_Ser << PlayerColor;
		_Ser << CannonInfo;
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
		_Ser >> PlayerColor;
		_Ser >> CannonInfo;
	}
};

class GameStatePacket : public GameServerPacket
{
public:
	// ������, ������ Ŭ�󿡰� �����ִ� "��ȣ"
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
	// ȣ��Ʈ, Ŭ�� ���� �� ������ ����
	unsigned int PlayerID;
	unsigned int PlayerStateSignal;

	//TODO :: �÷��̾� ����
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

// Ȥ�ó�
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