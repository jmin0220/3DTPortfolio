#include "PreCompile.h"
#include "ServerLevel.h"

#include "ServerPacket.h"

bool ServerLevel::IsHost_ = false;

GameServerNet* ServerLevel::Net;
GameServerNetServer ServerLevel::Server;
GameServerNetClient ServerLevel::Client;

ServerLevel::ServerLevel()
{
}

ServerLevel::~ServerLevel()
{
}

void ServerLevel::Start()
{
}

void ServerLevel::ObjectUpdatePacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	_Packet;
}

void ServerLevel::Update(float _DeltaTime)
{
}

void ServerLevel::End()
{
}

void ServerLevel::LevelStartEvent()
{
	if (true == IsHost_)
	{
		Server.Accept(30001);

		Net = &Server;
	}
	else
	{
		// "127.0.0.1" 인터넷 통신 규약의 약속으로
		// 이 번호는 localhost
		// 나한테 접속하겠다.
		// Client.Connect("127.0.0.1", 30222);

		//Client.Connect("127.0.0.1", 30001);
		Client.Connect(SOCKADDR_HOST, 30001);
		Net = &Client;
	}

	Net->Dis.PacketReturnCallBack = [=](int _PacketType, int _PacketSize, GameServerSerializer& Data)
	{
		ContentsPacketType Type = static_cast<ContentsPacketType>(_PacketType);

		std::shared_ptr<GameServerPacket> NewPacket;

		switch (Type)
		{
		case ContentsPacketType::ObjectUpdate:
			NewPacket = std::make_shared<ObjectUpdatePacket>();
			break;
		default:
			break;
		}

		NewPacket->DeSerializePacket(Data);

		return NewPacket;
	};

	Net->Dis.AddHandler(ContentsPacketType::ObjectUpdate, std::bind(&ServerLevel::ObjectUpdatePacketProcess, this, std::placeholders::_1));

}

void ServerLevel::LevelEndEvent()
{
}
