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

	// 다른 사람들
	for (; Begin != End; ++Begin)
	{
		std::shared_ptr<GameStatePacket> Packet = (*Begin).second;
		if (1 == Packet->PlayerReady)
		{
			++ReadyCount;
		}
	}

	// 자기자신
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

// Lobby에서 게임시작 버튼 누르면 호출
void GameServer::ServerStart()
{
	ServerStart_ = true;

	////// 호스트 : 서버 생성 //////
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
			// 이상한 패킷이 날라왔다
			break;
		}

		NewPacket->DeSerializePacket(Data);

		return NewPacket;
	};

	////// 받은 패킷에 따라 클라이언트에서 후처리해줄 함수 바인딩 //////

	// 공통
	Net->Dis.AddHandler(ContentsPacketType::ObjectUpdate, std::bind(&GameServer::ObjectUpdatePacketProcess, this, std::placeholders::_1));

	Net->Dis.AddHandler(ContentsPacketType::GameState, std::bind(&GameServer::GameStatePacketProcess, this, std::placeholders::_1));

	// 분리
	if (true == Net->GetIsHost())
	{
		// 내가 서버일때만 등록해야하는 패킷처리
	}
	else
	{
		// 내가 클라이언트 일때만 등록해야하는 패킷처리
		Net->Dis.AddHandler(ContentsPacketType::ClientInit, std::bind(&GameServer::ClientInitPacketProcess, this, std::placeholders::_1));

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
	if (false == ObjectUpdate_)
	{
		return;
	}

	// 받은 패킷이 ObjectUpdatePacket
	// ObjectUpdatePacket 중 타입을 통해 처리
	std::shared_ptr<ObjectUpdatePacket> Packet = std::dynamic_pointer_cast<ObjectUpdatePacket>(_Packet);

	std::shared_ptr<GameServerObject> FindObject = GameServerObject::GetServerObject(Packet->ObjectID);

	// 서버에서 보내준 패킷(플레이어, 장애물)이 클라에 없으면 무조건 만들어.
	// -> StageParentLevel에서 수행
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

	PlayerID_ = Packet->ObjectID;
}

// 게임상태 정보
void GameServer::GameStatePacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<GameStatePacket> Packet = std::dynamic_pointer_cast<GameStatePacket>(_Packet);

	// 모든 플레이어 정보 저장
	AllPlayersInfo_[Packet->PlayerID] = Packet;

	// 클라이언트 라면
	if (false == Net->GetIsHost())
	{
		StateChangeSignal_ = Packet->StateChangeSignal;
	}

}
////////////////////
///	 ~ 패킷 처리
////////////////////


void GameServer::SendGameStatePacket()
{
	std::shared_ptr<GameStatePacket> Packet = std::make_shared<GameStatePacket>();
	Packet->StateChangeSignal = 0;
	Packet->PlayerID = PlayerID_;
	Packet->PlayerReady = PlayerReady_;


	// 호스트라면
	if (true == Net->GetIsHost())
	{
		Packet->StateChangeSignal = StateChangeSignal_;
	}

	Net->SendPacket(Packet);
}