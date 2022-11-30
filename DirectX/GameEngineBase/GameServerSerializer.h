#pragma once

// Ό³Έν :
class GameServerSerializer
{
public:
	// constrcuter destructer
	GameServerSerializer(const char* _Data, unsigned int _Size);
	~GameServerSerializer();

	// delete Function
	GameServerSerializer(const GameServerSerializer& _Other) = delete;
	GameServerSerializer(GameServerSerializer&& _Other) noexcept = delete;
	GameServerSerializer& operator=(const GameServerSerializer& _Other) = delete;
	GameServerSerializer& operator=(GameServerSerializer&& _Other) noexcept = delete;

protected:

private:
	unsigned int Offset;
	std::vector<unsigned char> Data;



};

