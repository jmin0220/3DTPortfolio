#include "PreCompile.h"
#include "GameServerObject.h"

std::atomic<int> GameServerObject::IdSeed = 0;
std::map<int, GameServerObject*> GameServerObject::AllServerActor;

std::mutex PacketLock;

void GameServerObject::ServerRelease()
{
	AllServerActor.clear();
	IdSeed = PlayersCount;
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

	

	// 플레이어(호스트, 유저1, 유저2, ...)는 자신의 UserId(0, 1, 2로 초기화 할것임
	// 플레이어 ID는 겹치지 않음
	// 새로운 클라이언트 올때 가장 큰 넘버 다음부터 오브젝트 생성시작 넘버
	if (_Type == ServerObjectType::Player)
	{
		ID = GameServer::GetInst()->PlayerID_;
	}
	// 장애물
	else
	{
		ID = GetServerID();
	}


	IsNetInit = true;

	std::map<int, GameServerObject*>::iterator FindIt = AllServerActor.find(_ID);
	if (FindIt != AllServerActor.end())
	{
		GameEngineDebug::OutPutString("서버 겹치는 오브젝트생성");
	}

	AllServerActor.insert(std::make_pair(ID, this));
}