#pragma once
#include <atomic>
#include <list>

enum class ServerObjectBaseState
{
	Base,
	Death,
};

// 각자가 컨트롤 하는 엑터를 나누기 위함
enum class ServerObjectType
{
	Player,

	// Stage1
	SpinBarDouble,
	SpinBarSingle,
	
	// Stage2
	Cannon,

	// Stage5
	HoopRing,
};


// 설명 :
class GameServerObject
{
public:
	static std::atomic<int> IdSeed;
	static std::map<int, GameServerObject*> AllServerActor;

public:
	static void ServerRelease();

	static int GetAllActorsCount()
	{
		return static_cast<int>(AllServerActor.size());
	}

	static GameServerObject* GetServerObject(int _ID) 
	{
		std::map<int, GameServerObject*>::iterator FindIter = AllServerActor.find(_ID);

		if (FindIter == AllServerActor.end())
		{
			return nullptr;
		}

		return FindIter->second;
	}

public:
	static int GetServerID() 
	{
		return ++IdSeed;
	}

public:
	// constrcuter destructer
	GameServerObject(/*ServerObjectType _Type*/);
	~GameServerObject();

	// delete Function
	GameServerObject(const GameServerObject& _Other) = delete;
	GameServerObject(GameServerObject&& _Other) noexcept = delete;
	GameServerObject& operator=(const GameServerObject& _Other) = delete;
	GameServerObject& operator=(GameServerObject&& _Other) noexcept = delete;

	void ServerInit(ServerObjectType _Type);
	void ClientInit(ServerObjectType _Type, int _ID);

	bool GetIsNetInit() 
	{
		return IsNetInit;
	}

	int GetNetID()
	{
		return ID;
	}

	void PushPacket(std::shared_ptr<GameServerPacket> _Packet);
	bool IsPacketEmpty();
	std::shared_ptr<GameServerPacket> PopPacket();

protected:

private:
	std::list<std::shared_ptr<GameServerPacket>> PacketList;
	bool IsNetInit;
	ServerObjectType ServerType;
	int ID;

public:
	void SetMoveStartActivate(bool _MoveStart)
	{
		MoveStartActiaved_ = _MoveStart;
	}

	bool GetMoveStartActivate()
	{
		return MoveStartActiaved_;
	}

private:
	bool MoveStartActiaved_ = false;
};

