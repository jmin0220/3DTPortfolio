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
UINT32 GameServer::PlayersCount_ = 0;

GameServer::GameServer()
{
}

GameServer::~GameServer()
{
	Inst_.reset();
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
		PlayersCount_++; // ȣ��Ʈ�� �÷��̾� �߰�

		Server.AcceptCallBack = [&](SOCKET _User)
		{
			std::shared_ptr<ClientInitPacket> Packet = std::make_shared<ClientInitPacket>();

			Packet->ObjectID = GameServerObject::GetServerID();

			Server.NetSendPacket(_User, Packet);

			PlayersCount_++; // �÷��̾ ����õ� �ϸ� �߰�
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
			break;
		}

		NewPacket->DeSerializePacket(Data);

		return NewPacket;
	};

	////// ���� ��Ŷ�� ���� Ŭ���̾�Ʈ���� ��ó������ �Լ� ���ε� //////

	// ����
	Net->Dis.AddHandler(ContentsPacketType::ObjectUpdate, std::bind(&GameServer::ObjectUpdatePacketProcess, this, std::placeholders::_1));


	// �и�
	if (true == Net->GetIsHost())
	{
		// ���� �����϶��� ����ؾ��ϴ� ��Ŷ
	}
	else
	{
		// ���� Ŭ���̾�Ʈ �϶��� ����ؾ��ϴ� ��Ŷ
		Net->Dis.AddHandler(ContentsPacketType::ClientInit, std::bind(&GameServer::ClientInitPacketProcess, this, std::placeholders::_1));

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

	std::shared_ptr<GameServerObject> FindObject = GameServerObject::GetServerObject(Packet->ObjectID);

	// �������� ������ ��Ŷ(�÷��̾�, ��ֹ�)�� Ŭ�� ������ ������ �����.
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
}

// ������������, Ŭ�� ���� ���ӻ��� ����
void GameServer::GameStatePacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	if (true == Net->GetIsHost())
	{
		MsgBoxAssert("ȣ��Ʈ�ε� Ŭ���̾�Ʈ�� ��Ŷ�� �޾ҽ��ϴ�.");
	}

	std::shared_ptr<GameStatePacket> Packet = std::dynamic_pointer_cast<GameStatePacket>(_Packet);

	PlayersCount_ = Packet->PlayersCount;
	
}
////////////////////
///	 ~ ��Ŷ ó��
////////////////////

// ȣ��Ʈ->Ŭ�� �ܹ���
void GameServer::SendGameStatePacketToClient()
{
	std::shared_ptr<GameStatePacket> Packet = std::make_shared<GameStatePacket>();
	Packet->PlayersCount = PlayersCount_;
	Net->SendPacket(Packet);
}