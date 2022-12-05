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

// Lobby에서 게임시작 버튼 누르면 호출
void GameServer::ServerStart()
{
	ServerStart_ = true;

	////// 호스트 : 서버 생성 //////
	if (true == IsHost_)
	{
		Server.Accept(30001);
		Net = &Server;
		PlayersCount_++; // 호스트도 플레이어 추가

		Server.AcceptCallBack = [&](SOCKET _User)
		{
			std::shared_ptr<ClientInitPacket> Packet = std::make_shared<ClientInitPacket>();

			Packet->ObjectID = GameServerObject::GetServerID();

			Server.NetSendPacket(_User, Packet);

			PlayersCount_++; // 플레이어가 연결시도 하면 추가
		};

	}
	////// 클라이언트  : 생성된 서버 있으면 연결 //////
	else
	{
		Client.Connect(IP_HOST, 30001);
		Net = &Client;
	}

	////// 서버 콜백 세팅 : 받은 패킷의 타입에 따라 Deserialize해줌 //////
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

	////// 받은 패킷에 따라 클라이언트에서 후처리해줄 함수 바인딩 //////

	// 공통
	Net->Dis.AddHandler(ContentsPacketType::ObjectUpdate, std::bind(&GameServer::ObjectUpdatePacketProcess, this, std::placeholders::_1));


	// 분리
	if (true == Net->GetIsHost())
	{
		// 내가 서버일때만 등록해야하는 패킷
	}
	else
	{
		// 내가 클라이언트 일때만 등록해야하는 패킷
		Net->Dis.AddHandler(ContentsPacketType::ClientInit, std::bind(&GameServer::ClientInitPacketProcess, this, std::placeholders::_1));

		Net->Dis.AddHandler(ContentsPacketType::GameState, std::bind(&GameServer::GameStatePacketProcess, this, std::placeholders::_1));
	}

}

// 결과화면 나오고 더이상 서버 연결 필요 없을 때 호출
void GameServer::ServerEnd()
{
}


////////////////////
///	 패킷 처리
////////////////////
void GameServer::ObjectUpdatePacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	// 받은 패킷이 ObjectUpdatePacket
	// ObjectUpdatePacket 중 타입을 통해 처리
	std::shared_ptr<ObjectUpdatePacket> Packet = std::dynamic_pointer_cast<ObjectUpdatePacket>(_Packet);

	std::shared_ptr<GameServerObject> FindObject = GameServerObject::GetServerObject(Packet->ObjectID);

	// 서버에서 보내준 패킷(플레이어, 장애물)이 클라에 없으면 무조건 만들어.
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

	// 자신이 처리해야할 패킷 리스트에 추가
	FindObject->PushPacket(_Packet);

	// 호스트라면 모든 클라에게 전달
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
		MsgBoxAssert("클라이언트 init패킷이 아닙니다");
	}

	if (true == Net->GetIsHost())
	{
		MsgBoxAssert("호스트인데 클라이언트용 패킷을 받았습니다.");
	}


	// 클라이언트의 mainplayer
	//MainPlayer->ClientInit(ServerObjectType::Player, Packet->ObjectID);
}

// 서버에서보냄, 클라가 받은 게임상태 정보
void GameServer::GameStatePacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	if (true == Net->GetIsHost())
	{
		MsgBoxAssert("호스트인데 클라이언트용 패킷을 받았습니다.");
	}

	std::shared_ptr<GameStatePacket> Packet = std::dynamic_pointer_cast<GameStatePacket>(_Packet);

	PlayersCount_ = Packet->PlayersCount;
	
}
////////////////////
///	 ~ 패킷 처리
////////////////////

// 호스트->클라 단방향
void GameServer::SendGameStatePacketToClient()
{
	std::shared_ptr<GameStatePacket> Packet = std::make_shared<GameStatePacket>();
	Packet->PlayersCount = PlayersCount_;
	Net->SendPacket(Packet);
}