#include "PreCompile.h"
#include "GameServer.h"
#include "ServerPacket.h"
#include "PlayerActor.h"

std::shared_ptr<GameServer> GameServer::Inst_ = std::make_shared<GameServer>();
bool GameServer::IsHost_ = false;
bool GameServer::ServerStart_ = false;
GameServerNet* GameServer::Net;
GameServerNetServer GameServer::Server;
GameServerNetClient GameServer::Client;
unsigned int GameServer::StateChangeSignal_ = 0;
unsigned int GameServer::PlayerID_ = 0;
unsigned int GameServer::PlayerReady_ = 0;
bool GameServer::ObjectUpdate_ = false;

int GameServer::GetAllPlayersReadyCount()
{
	std::map<int, std::shared_ptr<class GameStatePacket>>::iterator Begin = AllPlayersInfo_.begin();
	std::map<int, std::shared_ptr<class GameStatePacket>>::iterator End = AllPlayersInfo_.end();

	int ReadyCount = 0;

	// �ٸ� �����
	for (; Begin != End; ++Begin)
	{
		std::shared_ptr<GameStatePacket> Packet = (*Begin).second;
		if (1 == Packet->PlayerReady)
		{
			++ReadyCount;
		}
	}

	// �ڱ��ڽ�
	if (1 == PlayerReady_)
	{
		++ReadyCount;
	}

	return ReadyCount;
}

GameServer::GameServer()
{
}

GameServer::~GameServer()
{
	Inst_.reset();
	AllPlayersInfo_.clear();
}

// Lobby���� ���ӽ��� ��ư ������ ȣ��
void GameServer::ServerStart()
{
	ServerStart_ = true;

	////// ȣ��Ʈ : ���� ���� //////
	if (true == IsHost_)
	{
		Server.Accept(30001);
		Net = &Server;

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
		default:
			int a = 0;
			// �̻��� ��Ŷ�� ����Դ�
			break;
		}

		NewPacket->DeSerializePacket(Data);

		return NewPacket;
	};

	////// ���� ��Ŷ�� ���� Ŭ���̾�Ʈ���� ��ó������ �Լ� ���ε� //////

	// ����
	Net->Dis.AddHandler(ContentsPacketType::ObjectUpdate, std::bind(&GameServer::ObjectUpdatePacketProcess, this, std::placeholders::_1));

	Net->Dis.AddHandler(ContentsPacketType::GameState, std::bind(&GameServer::GameStatePacketProcess, this, std::placeholders::_1));

	// �и�
	if (true == Net->GetIsHost())
	{
		// ���� �����϶��� ����ؾ��ϴ� ��Ŷó��
	}
	else
	{
		// ���� Ŭ���̾�Ʈ �϶��� ����ؾ��ϴ� ��Ŷó��
		Net->Dis.AddHandler(ContentsPacketType::ClientInit, std::bind(&GameServer::ClientInitPacketProcess, this, std::placeholders::_1));

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
	if (false == ObjectUpdate_)
	{
		return;
	}

	// ���� ��Ŷ�� ObjectUpdatePacket
	// ObjectUpdatePacket �� Ÿ���� ���� ó��
	std::shared_ptr<ObjectUpdatePacket> Packet = std::dynamic_pointer_cast<ObjectUpdatePacket>(_Packet);

	std::shared_ptr<GameServerObject> FindObject = GameServerObject::GetServerObject(Packet->ObjectID);

	// �������� ������ ��Ŷ(�÷��̾�, ��ֹ�)�� Ŭ�� ������ ������ �����.
	// -> StageParentLevel���� ����
	if (nullptr == FindObject)
	{

		ServerObjectType Type = Packet->Type;

		switch (Type)
		{
		case ServerObjectType::Player:
		{
			std::shared_ptr<PlayerActor> NewPlayer = GEngine::GetCurrentLevel()->CreateActor<PlayerActor>();
			NewPlayer->ClientInit(Packet->Type, Packet->ObjectID);
			FindObject = NewPlayer;
			break;
		}
		default:
			break;
		}
	}

	// �ڽ��� ó���ؾ��� ��Ŷ ����Ʈ�� �߰�
	FindObject->PushPacket(_Packet);

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

	// ��� �÷��̾� ���� ����
	AllPlayersInfo_[Packet->PlayerID] = Packet;

	// Ŭ���̾�Ʈ ���
	if (false == Net->GetIsHost())
	{
		StateChangeSignal_ = Packet->StateChangeSignal;
	}

}
////////////////////
///	 ~ ��Ŷ ó��
////////////////////


void GameServer::SendGameStatePacket()
{
	std::shared_ptr<GameStatePacket> Packet = std::make_shared<GameStatePacket>();
	Packet->StateChangeSignal = 0;
	Packet->PlayerID = PlayerID_;
	Packet->PlayerReady = PlayerReady_;


	// ȣ��Ʈ���
	if (true == Net->GetIsHost())
	{
		Packet->StateChangeSignal = StateChangeSignal_;
	}

	Net->SendPacket(Packet);
}