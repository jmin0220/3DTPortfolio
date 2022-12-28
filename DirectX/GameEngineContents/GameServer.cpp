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

	// 혼자면 접속 못해요ㅠㅠ
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

	// 혼자면 접속 못해요ㅠㅠ
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

// Lobby에서 게임시작 버튼 누르면 호출
void GameServer::ServerStart()
{
	ServerStart_ = true;
	ServerSignal_ = ServerFlag::S_None;
	PlayerSignal_ = PlayerFlag::P_None;

	////// 호스트 : 서버 생성 //////
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
		case ContentsPacketType::PlayerState:
			NewPacket = std::make_shared<PlayerStatePacket>();
			break;
		default:
			// 이상한 패킷이 날라왔다
			NewPacket = std::make_shared<GarbagePacket>();
			break;
		}

		NewPacket->DeSerializePacket(Data);

		return NewPacket;
	};

	////// 받은 패킷에 따라 클라이언트에서 후처리해줄 함수 바인딩 //////

	// 공통
	Net->Dis.AddHandler(ContentsPacketType::ObjectUpdate, std::bind(&GameServer::ObjectUpdatePacketProcess, this, std::placeholders::_1));

	// 자신의 상태 패킷 처리, 상태 : 유저 준비, 
	Net->Dis.AddHandler(ContentsPacketType::PlayerState, std::bind(&GameServer::PlayerStatePacketProcess, this, std::placeholders::_1));

	// 분리
	if (true == Net->GetIsHost())
	{
		// 내가 서버일때만 등록해야하는 패킷처리
	}
	else
	{
		// 내가 클라이언트 일때만 등록해야하는 패킷처리
		Net->Dis.AddHandler(ContentsPacketType::ClientInit, std::bind(&GameServer::ClientInitPacketProcess, this, std::placeholders::_1));

		// 서버가 보내주는 신호패킷 처리
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

	GameServerObject* FindObject = GameServerObject::GetServerObject(Packet->ObjectID);

	// 없으면 생성
	if (nullptr == FindObject)
	{
		std::lock_guard<std::mutex> LockGuard(Lock);
		NewObjectUpdatePacketList_.push_back(Packet);
	}
	// 있으면 자신이 처리해야할 패킷 리스트에 추가
	else
	{
		std::lock_guard<std::mutex> LockGuard(Lock);
		FindObject->PushPacket(_Packet);
	}

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

	if (Packet->ServerSignal != 0)
	{
		GameEngineDebug::OutPutString("GameStatePacketProcess >> " + std::to_string(Packet->ServerSignal));
	}

	// 클라이언트만 서버 신호 받음
	if (false == Net->GetIsHost())
	{
		//ServerSignal_ = static_cast<ServerFlag>(ServerSignal_ | Packet->ServerSignal);
		ServerSignal_ = static_cast<ServerFlag>(Packet->ServerSignal);
	}

}

// 모든 유저가 서로의 정보를 알고 있음
void GameServer::PlayerStatePacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<PlayerStatePacket> Packet = std::dynamic_pointer_cast<PlayerStatePacket>(_Packet);

	// 모든 플레이어 정보 저장
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
///	 ~ 패킷 처리
////////////////////

// *호스트만 호출
void GameServer::SendGameStatePacket()
{
	if (ServerFlag::S_None == ServerSignal_)
	{
		return;
	}

	std::shared_ptr<GameStatePacket> Packet = std::make_shared<GameStatePacket>();	

	// 서버가 모든 클라이언트에게 주는 신호
	Packet->ServerSignal = static_cast<unsigned int>(ServerSignal_);

	Net->SendPacket(Packet);
}

// 모두 호출
void GameServer::SendPlayerStatePacket()
{ 
	std::shared_ptr<PlayerStatePacket> Packet = std::make_shared<PlayerStatePacket>();

	Packet->PlayerID = PlayerID_;
	
	// 자신의 상태를 알림
	Packet->PlayerStateSignal = static_cast<unsigned int>(PlayerSignal_);

	// 점수
	Packet->PlayerScore = PlayerScore_;

	// 플레이어 스킨정보(색상)
	Packet->PlayerColor = PlayerColorID_;

	// 시간
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
