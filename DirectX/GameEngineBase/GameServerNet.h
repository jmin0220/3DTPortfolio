#pragma once

// Ό³Έν :
class GameServerNet
{
public:
	static void WindowNetStartUp();

public:
	// constrcuter destructer
	GameServerNet();
	~GameServerNet();

	// delete Function
	GameServerNet(const GameServerNet& _Other) = delete;
	GameServerNet(GameServerNet&& _Other) noexcept = delete;
	GameServerNet& operator=(const GameServerNet& _Other) = delete;
	GameServerNet& operator=(GameServerNet&& _Other) noexcept = delete;


	virtual int Send(const char* Data, size_t _Size);

protected:
	int Send(SOCKET _Socket, const char* Data, size_t _Size);

private:

};

