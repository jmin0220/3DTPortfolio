#pragma once


// 설명 :
class GameServerPacket : public std::enable_shared_from_this<GameServerPacket>
{
public:
	// constrcuter destructer
	GameServerPacket();
	~GameServerPacket();

	// delete Function
	GameServerPacket(const GameServerPacket& _Other) = delete;
	GameServerPacket(GameServerPacket&& _Other) noexcept = delete;
	GameServerPacket& operator=(const GameServerPacket& _Other) = delete;
	GameServerPacket& operator=(GameServerPacket&& _Other) noexcept = delete;

	int PacketID; // 패킷의 종류
	int Size; // 패킷의 크기

	void DataInput() 
	{
	}

protected:

private:

};

