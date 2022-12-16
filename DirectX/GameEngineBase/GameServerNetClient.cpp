#include "PreCompile.h"
#include "GameServerNetClient.h"
#include "GameEngineDebug.h"

GameServerNetClient::GameServerNetClient()
{
	IsHost = false;
}

GameServerNetClient::~GameServerNetClient()
{
}

void GameServerNetClient::Connect(std::string _Ip, int Port)
{
	GameServerNet::WindowNetStartUp();

	if (0 == SessionSocket)
	{
		SessionSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (INVALID_SOCKET == SessionSocket)
		{
			return;
		}
	}

	SOCKADDR_IN Add;
	Add.sin_family = AF_INET;
	Add.sin_port = htons(Port);

	const char* IP = _Ip.c_str();

	if (SOCKET_ERROR == inet_pton(AF_INET, IP, &Add.sin_addr))
	{
		return;
	}

	int Len = sizeof(SOCKADDR_IN);
	if (SOCKET_ERROR == connect(SessionSocket, (const sockaddr*)&Add, Len))
	{
		MsgBoxAssert("서버 접속에 실패했습니다");
		return;
	}

	RecvThread.Start("RecvThread", std::bind(&GameServerNetClient::RecvThreadFunction, this, &RecvThread));
}

int GameServerNetClient::Send(const char* Data, size_t _Size)
{
	return GameServerNet::NetSend(SessionSocket, Data, _Size);
}

int GameServerNetClient::SendPacket(std::shared_ptr<GameServerPacket> _Packet)
{
	GameServerSerializer Ser = PacketSerializ(_Packet);
	return Send(Ser.GetDataPtrConvert<const char*>(), Ser.GetOffSet());
}

void GameServerNetClient::RecvThreadFunction(GameEngineThread* _Thread)
{
	// 1500 - 1024
	char Packet[1024] = { 0 };
	std::vector<char> PacketVector;

	while (true)
	{
		// 476
		int Result = recv(SessionSocket, Packet, sizeof(Packet), 0);

		//if (Result == 1024)
		//{
		//	MsgBoxAssert("최대치가 왔습니다.");
		//}

		if (-1 == Result)
		{
			MsgBoxAssert("네트워크 에러");
			return;
		}

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

			Packet->SetMaster(SessionSocket);

			Dis.ProcessPacket(Packet);

			if (PacketVector.size() > PacketSize)
			{
				memcpy_s(&PacketVector[0], PacketVector.size(), &PacketVector[PacketSize], PacketVector.size() - PacketSize);
			}

			PacketVector.resize(PacketVector.size() - PacketSize);
		}

	}
}