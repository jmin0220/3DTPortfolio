#pragma once
#include <GameEngineBase/GameServerNetServer.h>
#include <GameEngineBase/GameServerNetClient.h>
#include <functional>


// Ό³Έν :
class ServerLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	ServerLevel();
	~ServerLevel();

	// delete Function
	ServerLevel(const ServerLevel& _Other) = delete;
	ServerLevel(ServerLevel&& _Other) noexcept = delete;
	ServerLevel& operator=(const ServerLevel& _Other) = delete;
	ServerLevel& operator=(ServerLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;
private:
	static GameServerNet* Net;
	static GameServerNetServer Server;
	static GameServerNetClient Client;

	std::map<__int64, std::shared_ptr<GameEngineActor>> AllServerActor;
};

