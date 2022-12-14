#include "PreCompile.h"
#include "GameServerNetServer.h"
#include "GameEngineString.h"
#include "GameEngineDebug.h"
#include "GameEngineThread.h"
#include "GameServerSerializer.h"

//enum PacketType
//{
//	Move,
//	Attack,
//};
//
//class Pakcet {
//	char String[100] 
//};


GameServerNetServer::GameServerNetServer()
{
	IsHost = true;
}

GameServerNetServer::~GameServerNetServer()
{
	for (size_t i = 0; i < UserThreads.size(); i++)
	{
		closesocket(UserSockets[i]);
		UserSockets[i] = 0;
		UserThreads[i]->Join();
	}

	if (0 != ServerAccpetSocket)
	{
		closesocket(ServerAccpetSocket);
		ServerAccpetSocket = 0;
		AcceptThread.Join();
	}
}

void GameServerNetServer::Accept(int Port)
{
	GameServerNet::WindowNetStartUp();

	// windowapi에서 서버통신을 하려면 무조건 소켓을 우선적으로 만들어줘야 한다.

	// 00000001 00000000 00000000 00000000
	// int a = 1;

	// 
	SOCKADDR_IN Add;
	Add.sin_family = AF_INET; // ip4 주소

	// 1   1   1   1     2
	// 255.255.255.255 + 30001
	// 127.0.0.1 + 30001
	// 1.0.0.127 + 30001

	Add.sin_port = htons(Port);

	// sin_addr
	if (SOCKET_ERROR == inet_pton(AF_INET, "0.0.0.0", &Add.sin_addr))
	{
		return;
	}

	// OSI 7계층이라는 통신 규약에 의해서
	// 물리단계
	// 랜카드단계

	// SOCK_STREAM 연결지향형
	// SOCK_DRAM UDP
	// 프로토콜

	// 주소를 만드는 겁니다.
	ServerAccpetSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == ServerAccpetSocket)
	{
		return;
	}

	if (SOCKET_ERROR == bind(ServerAccpetSocket, (const sockaddr*)&Add, sizeof(SOCKADDR_IN)))
	{
		return;
	}

	if (SOCKET_ERROR == listen(ServerAccpetSocket, 512))
	{
		return;
	}

	AcceptThread.Start("AcceptThread", std::bind(&GameServerNetServer::AcceptFunction, this, &AcceptThread));
}


void GameServerNetServer::AcceptFunction(GameEngineThread* Thread)
{
	// 쓰레드에서 따로 돌아갈 겁니다.
	while (ServerAccpetSocket)
	{
		SOCKADDR_IN UserAddress;

		int AddressLen = sizeof(SOCKADDR_IN);

		// accept을 호출해야 접속자를 받는걸로 착각하는데 아니야.
		SOCKET NewUser = accept(ServerAccpetSocket, (sockaddr*)&UserAddress, &AddressLen);

		// SOCKET NewUser
		if (-1 == NewUser)
		{
			return;
		}

		std::shared_ptr<GameEngineThread> NewThread = std::make_shared<GameEngineThread>();
		UserThreads.push_back(NewThread);
		std::stringstream ThreadName;
		ThreadName << NewUser;
		ThreadName << "UserThread";

		if (nullptr != AcceptCallBack)
		{
			AcceptCallBack(NewUser);
		}

		UserSockets.push_back(NewUser);
		NewThread->Start(ThreadName.str(), std::bind(&GameServerNetServer::UserFunction, this, NewThread.get(), NewUser));


		// 처리해야할께 많다고만 해둘께요.

	}
}

void GameServerNetServer::UserFunction(GameEngineThread* Thread, SOCKET _Socket)
{
	// 1500 - 1024
	char Packet[1024] = { 0 };
	std::vector<char> PacketVector;

	while (true)
	{
		// 476
		int Result = recv(_Socket, Packet, sizeof(Packet), 0);

		//if (Result == 1024)
		//{
		//	MsgBoxAssert("최대치가 왔습니다.");
		//}
		// -> 클라이언트 잠깐 멈추면 서버 일로 들어옴

		//if (-1 == Result)
		//{
		//	MsgBoxAssert("네트워크 에러");
		//	return;
		//}

		size_t PrevSize = PacketVector.size();

		PacketVector.resize(PacketVector.size() + Result);

		memcpy_s(&PacketVector[PrevSize], PacketVector.size() - PrevSize, Packet, Result);

		while (true)
		{
			if (8 >= PacketVector.size())
			{
				break;
			}

			int PacketType;
			int PacketSize;

			memcpy_s(&PacketType, sizeof(int), &PacketVector[0], sizeof(int));
			memcpy_s(&PacketSize, sizeof(int), &PacketVector[4], sizeof(int));

			if (PacketVector.size() < PacketSize)
			{
				break;
			}

			GameServerSerializer Ser = GameServerSerializer(&PacketVector[0], PacketSize);

			// 패킷을 만들어 낸다.
			std::shared_ptr<GameServerPacket> Packet =
				Dis.PacketReturnCallBack(PacketType, PacketSize, Ser);

			Packet->SetMaster(_Socket);

			Dis.ProcessPacket(Packet);

			if (PacketVector.size() > PacketSize)
			{
				memcpy_s(&PacketVector[0], PacketVector.size(), &PacketVector[PacketSize], PacketVector.size() - PacketSize);
			}

			PacketVector.resize(PacketVector.size() - PacketSize);
		}

	}
}

int GameServerNetServer::SendPacket(std::shared_ptr<GameServerPacket> _Packet)
{
	// 문제가 있음.
	for (size_t i = 0; i < UserSockets.size(); i++)
	{
		if (UserSockets[i] == _Packet->GetMaster())
		{
			continue;
		}

		NetSendPacket(UserSockets[i], _Packet);
	}

	return 0;
}
