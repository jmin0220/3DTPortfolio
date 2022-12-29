#include "PreCompile.h"
#include "GameServerObject.h"

std::atomic<int> GameServerObject::IdSeed = 0;
std::map<int, GameServerObject*> GameServerObject::AllServerActor;

std::mutex PacketLock;

void GameServerObject::ServerRelease()
{
	AllServerActor.clear();
	IdSeed = 0;
}

void GameServerObject::PushPacket(std::shared_ptr<GameServerPacket> _Packet)
{
	std::lock_guard L(PacketLock);
	// PacketLock.lock();
	PacketList.push_back(_Packet);
	// PacketLock.unlock();
}
bool GameServerObject::IsPacketEmpty()
{
	std::lock_guard L(PacketLock);
	// PacketLock.lock();
	bool Check = PacketList.empty();
	// PacketLock.unlock();

	return Check;
}

std::shared_ptr<GameServerPacket> GameServerObject::PopPacket()
{

	// PacketLock.lock();
	if (PacketList.empty())
	{
		return nullptr;
	}

	std::lock_guard L(PacketLock);
	std::shared_ptr<GameServerPacket> Packet = PacketList.front();
	PacketList.pop_front();
	// PacketLock.unlock();
	return Packet;
}

GameServerObject::GameServerObject(/*ServerObjectType _Type*/)
	: IsNetInit(false)
{

}

GameServerObject::~GameServerObject()
{
}



void GameServerObject::ServerInit(ServerObjectType _Type)
{
	ServerType = _Type;
	ID = GetServerID();

	IsNetInit = true;

	AllServerActor.insert(std::make_pair(ID, this));
}

void GameServerObject::ClientInit(ServerObjectType _Type, int _ID)
{
	ServerType = _Type;
	ID = _ID;

	GameEngineDebug::OutPutString("[ ���� IDSEED ���� : " + std::to_string(IdSeed) + " ]");

	IsNetInit = true;

	AllServerActor.insert(std::make_pair(ID, this));
}