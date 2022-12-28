#include "PreCompile.h"
#include "GameServer.h"
#include "PlayerActor.h"

std::shared_ptr<GameServer> GameServer::Inst_ = std::make_shared<GameServer>();
bool GameServer::IsHost_ = false;
bool GameServer::ServerStart_ = false;
GameServerNet* GameServer::Net;
GameServerNetServer GameServer::Server;
GameServerNetClient GameServer::Client;
ServerFlag GameServer::ServerSignal_ = ServerFlag::S_None;
PlayerFlag GameServer::PlayerSignal_ = PlayerFlag::P_None;
unsigned int GameServer::PlayerID_ = -1;
unsigned int GameServer::PlayerColorID_ = 0;
float4 GameServer::PlayerColor_ = float4::ZERO;
unsigned int GameServer::PlayerScore_ = 0;
unsigned int GameServer::PlayTime_ = 0;

#include <atomic>
std::mutex Lock;

bool GameServer::CheckOtherPlayersFlag(PlayerFlag _Flag)
{
	std::map<int, std::shared_ptr<class PlayerStatePacket>>::iterator Begin = OtherPlayersInfo_.begin();
	std::map<int, std::shared_ptr<class PlayerStatePacket>>::iterator End = OtherPlayersInfo_.end();

	// ȥ�ڸ� ���� ���ؿ�Ф�
	if (0 == OtherPlayersInfo_.size())
	{
		return false;
	}

	bool Result = true;
	for (; Begin != End; ++Begin)
	{
		Result = (static_cast<bool>((*Begin).second->PlayerStateSignal == _Flag));
		if (false == Result)
		{
			return Result;
		}
	}

	return Result;
}

unsigned int GameServer::CheckOtherPlayersFlagCount(PlayerFlag _Flag)
{
	std::map<int, std::shared_ptr<class PlayerStatePacket>>::iterator Begin = OtherPlayersInfo_.begin();
	std::map<int, std::shared_ptr<class PlayerStatePacket>>::iterator End = OtherPlayersInfo_.end();

	// ȥ�ڸ� ���� ���ؿ�Ф�
	if (0 == OtherPlayersInfo_.size())
	{
		return 0;
	}

	int Result = 0;
	for (; Begin != End; ++Begin)
	{
		if ((*Begin).second->PlayerStateSignal == static_cast<unsigned int>(_Flag))
		{
			Result++;
		}
	}

	return Result;
}

GameServer::GameServer()
{
}

GameServer::~GameServer()
{
	Inst_.reset();
	OtherPlayersInfo_.clear();
}

// Lobby���� ���ӽ��� ��ư ������ ȣ��
void GameServer::ServerStart()
{
	ServerStart_ = true;
	ServerSignal_ = ServerFlag::S_None;
	PlayerSignal_ = PlayerFlag::P_None;

	////// ȣ��Ʈ : ���� ���� //////
	if (true == IsHost_)
	{
		Server.Accept(30001);
		Net = &Server;
		PlayerID_ = 0;

		Server.AcceptCallBack = [&](SOCKET _User)
		{
			std::shared_ptr<ClientInitPacket> Packet = std::make_shared<ClientInitPacket>();

			Packet->ObjectID = GameServerObject::GetServerID();

			Server.NetSendPacket(_User, Packet);

		};

	}
	////// Ŭ���̾�Ʈ  : ������ ���� ������ ���� //////
	else
	{
		Client.Connect(IP_HOST, 30001);
		Net = &Client;
	}

	////// ���� �ݹ� ���� : ���� ��Ŷ�� Ÿ�Կ� ���� Deserialize���� //////
	Net->Dis.PacketReturnCallBack = [=](int _PacketType, int _PacketSize, GameServerSerializer& Data)
	{
		ContentsPacketType Type = static_cast<ContentsPacketType>(_PacketType);

		std::shared_ptr<GameServerPacket> NewPacket;

		switch (Type)
		{
		case ContentsPacketType::ObjectUpdate:
			NewPacket = std::make_shared<ObjectUpdatePacket>();
			break;
		case ContentsPacketType::ClientInit:
			NewPacket = std::make_shared<ClientInitPacket>();
			break;
		case ContentsPacketType::GameState:
			NewPacket = std::make_shared<GameStatePacket>();
			break;
		case ContentsPacketType::PlayerState:
			NewPacket = std::make_shared<PlayerStatePacket>();
			break;
		default:
			// �̻��� ��Ŷ�� ����Դ�
			NewPacket = std::make_shared<GarbagePacket>();
			break;
		}

		NewPacket->DeSerializePacket(Data);

		return NewPacket;
	};

	////// ���� ��Ŷ�� ���� Ŭ���̾�Ʈ���� ��ó������ �Լ� ���ε� //////

	// ����
	Net->Dis.AddHandler(ContentsPacketType::ObjectUpdate, std::bind(&GameServer::ObjectUpdatePacketProcess, this, std::placeholders::_1));

	// �ڽ��� ���� ��Ŷ ó��, ���� : ���� �غ�, 
	Net->Dis.AddHandler(ContentsPacketType::PlayerState, std::bind(&GameServer::PlayerStatePacketProcess, this, std::placeholders::_1));

	// �и�
	if (true == Net->GetIsHost())
	{
		// ���� �����϶��� ����ؾ��ϴ� ��Ŷó��
	}
	else
	{
		// ���� Ŭ���̾�Ʈ �϶��� ����ؾ��ϴ� ��Ŷó��
		Net->Dis.AddHandler(ContentsPacketType::ClientInit, std::bind(&GameServer::ClientInitPacketProcess, this, std::placeholders::_1));

		// ������ �����ִ� ��ȣ��Ŷ ó��
		Net->Dis.AddHandler(ContentsPacketType::GameState, std::bind(&GameServer::GameStatePacketProcess, this, std::placeholders::_1));
	}

}

// ���ȭ�� ������ ���̻� ���� ���� �ʿ� ���� �� ȣ��
void GameServer::ServerEnd()
{
}


////////////////////
///	 ��Ŷ ó��
////////////////////
void GameServer::ObjectUpdatePacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{

	// ���� ��Ŷ�� ObjectUpdatePacket
	// ObjectUpdatePacket �� Ÿ���� ���� ó��
	std::shared_ptr<ObjectUpdatePacket> Packet = std::dynamic_pointer_cast<ObjectUpdatePacket>(_Packet);

	GameServerObject* FindObject = GameServerObject::GetServerObject(Packet->ObjectID);

	// ������ ����
	if (nullptr == FindObject)
	{
		std::lock_guard<std::mutex> LockGuard(Lock);
		NewObjectUpdatePacketList_.push_back(Packet);
	}
	// ������ �ڽ��� ó���ؾ��� ��Ŷ ����Ʈ�� �߰�
	else
	{
		std::lock_guard<std::mutex> LockGuard(Lock);
		FindObject->PushPacket(_Packet);
	}

	// ȣ��Ʈ��� ��� Ŭ�󿡰� ����
	if (true == Net->GetIsHost())
	{
		GameServer::Net->SendPacket(Packet);
	}
}

void GameServer::ClientInitPacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<ClientInitPacket> Packet = std::dynamic_pointer_cast<ClientInitPacket>(_Packet);

	if (nullptr == Packet)
	{
		MsgBoxAssert("Ŭ���̾�Ʈ init��Ŷ�� �ƴմϴ�");
	}

	if (true == Net->GetIsHost())
	{
		MsgBoxAssert("ȣ��Ʈ�ε� Ŭ���̾�Ʈ�� ��Ŷ�� �޾ҽ��ϴ�.");
	}


	// Ŭ���̾�Ʈ�� mainplayer
	//MainPlayer->ClientInit(ServerObjectType::Player, Packet->ObjectID);

	PlayerID_ = Packet->ObjectID;
}

// ���ӻ��� ����
void GameServer::GameStatePacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<GameStatePacket> Packet = std::dynamic_pointer_cast<GameStatePacket>(_Packet);

	if (Packet->ServerSignal != 0)
	{
		GameEngineDebug::OutPutString("GameStatePacketProcess >> " + std::to_string(Packet->ServerSignal));
	}

	// Ŭ���̾�Ʈ�� ���� ��ȣ ����
	if (false == Net->GetIsHost())
	{
		//ServerSignal_ = static_cast<ServerFlag>(ServerSignal_ | Packet->ServerSignal);
		ServerSignal_ = static_cast<ServerFlag>(Packet->ServerSignal);
	}

}

// ��� ������ ������ ������ �˰� ����
void GameServer::PlayerStatePacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<PlayerStatePacket> Packet = std::dynamic_pointer_cast<PlayerStatePacket>(_Packet);

	// ��� �÷��̾� ���� ����
	OtherPlayersInfo_[Packet->PlayerID] = Packet;

	if (true == Net->GetIsHost())
	{
		GameServer::Net->SendPacket(Packet);
	}
	else
	{
		PlayTime_ = Packet->PlayTime;
	}
}

////////////////////
///	 ~ ��Ŷ ó��
////////////////////

// *ȣ��Ʈ�� ȣ��
void GameServer::SendGameStatePacket()
{
	if (ServerFlag::S_None == ServerSignal_)
	{
		return;
	}

	std::shared_ptr<GameStatePacket> Packet = std::make_shared<GameStatePacket>();	

	// ������ ��� Ŭ���̾�Ʈ���� �ִ� ��ȣ
	Packet->ServerSignal = static_cast<unsigned int>(ServerSignal_);

	Net->SendPacket(Packet);
}

// ��� ȣ��
void GameServer::SendPlayerStatePacket()
{ 
	std::shared_ptr<PlayerStatePacket> Packet = std::make_shared<PlayerStatePacket>();

	Packet->PlayerID = PlayerID_;
	
	// �ڽ��� ���¸� �˸�
	Packet->PlayerStateSignal = static_cast<unsigned int>(PlayerSignal_);

	// ����
	Packet->PlayerScore = PlayerScore_;

	// �÷��̾� ��Ų����(����)
	Packet->PlayerColor = PlayerColorID_;

	// �ð�
	if (true == IsHost_)
	{
		Packet->PlayTime = PlayTime_;
	}
	else
	{
		Packet->PlayTime = 0;
	}

	Net->SendPacket(Packet);
}
