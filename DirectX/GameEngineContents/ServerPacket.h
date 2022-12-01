#pragma once
#include <GameEngineBase/GameServerPacket.h>

enum class ContentsPacketType
{
	ObjectUpdate,
};

class ObjectUpdatePacket : public GameServerPacket
{
public:
	int ObjectID;
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
		_Ser << Pos;
		_Ser << Rot;
		_Ser << Scale;
		_Ser << Animation;
	}
	virtual void DeSerialize(GameServerSerializer& _Ser)
	{
		GameServerPacket::DeSerialize(_Ser);
		_Ser >> ObjectID;
		_Ser >> Pos;
		_Ser >> Rot;
		_Ser >> Scale;
		_Ser >> Animation;
	}
};
