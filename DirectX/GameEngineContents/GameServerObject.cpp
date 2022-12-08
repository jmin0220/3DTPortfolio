#include "PreCompile.h"
#include "GameServerObject.h"

std::atomic<int> GameServerObject::IdSeed = 0;
std::map<int, std::shared_ptr<GameServerObject>> GameServerObject::AllServerActor;

std::mutex PacketLock;


void GameServerObject::PushPacket(std::shared_ptr<GameServerPacket> _Packet)
{
	PacketLock.lock();
	PacketList.push_back(_Packet);
	PacketLock.unlock();
}
bool GameServerObject::IsPacketEmpty()
{
	PacketLock.lock();
	bool Check = PacketList.empty();
	PacketLock.unlock();

	return Check;
}

std::shared_ptr<GameServerPacket> GameServerObject::PopPacket()
{
	std::lock_guard L(PacketLock);
	//PacketLock.lock();
	if (PacketList.empty())
	{
		return nullptr;
	}

	std::shared_ptr<GameServerPacket> Packet = PacketList.front();
	PacketList.pop_front();
	//PacketLock.unlock();
	return Packet;
}

GameServerObject::GameServerObject(/*ServerObjectType _Type*/)
	: IsNetInit(false)
{
	
}

GameServerObject::~GameServerObject() 
{
}


// 호스트가 생성하는 ServerObject 초기화
void GameServerObject::ServerInit(ServerObjectType _Type)
{
	ServerType = _Type;
	ID = GetServerID();

	IsNetInit = true;

	AllServerActor.insert(std::make_pair(ID, this));
}

// 클라가 생성하는 ServerObject 초기화
void GameServerObject::ClientInit(ServerObjectType _Type, int _ID)
{
	ServerType = _Type;
	ID = _ID;

	IsNetInit = true;

	AllServerActor.insert(std::make_pair(ID, this));
}