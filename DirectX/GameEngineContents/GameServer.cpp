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
std::string GameServer::UserName_;
bool GameServer::RaceStart_ = false;

#include <atomic>
std::mutex Lock;

bool GameServer::CheckOtherPlayersFlag(PlayerFlag _Flag)
{
	std::map<int, std::shared_ptr<class PlayerStatePacket>>::iterator Begin = OtherPlayersInfo_.begin();
	std::map<int, std::shared_ptr<class PlayerStatePacket>>::iterator End = OtherPlayersInfo_.end();

	// 去磊搁 立加 给秦夸ばば
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

	// 去磊搁 立加 给秦夸ばば
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

bool GameServer::CheckHostFlag(PlayerFlag _Flag)
{
	if (true == IsHost_)
	{
		return false;
	}

	return OtherPlayersInfo_[0]->PlayerStateSignal == static_cast<unsigned int>(_Flag);
}

GameServer::GameServer()
{
}

GameServer::~GameServer()
{
	Inst_.reset();
	OtherPlayersInfo_.clear();
}

// Lobby俊辑 霸烙矫累 滚瓢 穿福搁 龋免
void GameServer::ServerStart()
{
	ServerStart_ = true;
	ServerSignal_ = ServerFlag::S_None;
	PlayerSignal_ = PlayerFlag::P_None;

	////// 龋胶飘 : 辑滚 积己 //////
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
	////// 努扼捞攫飘  : 积己等 辑滚 乐栏搁 楷搬 //////
	else
	{
		Client.Connect(IP_HOST, 30001);
		Net = &Client;
	}

	////// 辑滚 妮归 技泼 : 罐篮 菩哦狼 鸥涝俊 蝶扼 Deserialize秦淋 //////
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
			// 捞惑茄 菩哦捞 朝扼吭促
			NewPacket = std::make_shared<GarbagePacket>();
			break;
		}

		NewPacket->DeSerializePacket(Data);

		return NewPacket;
	};

	////// 罐篮 菩哦俊 蝶扼 努扼捞攫飘俊辑 饶贸府秦临 窃荐 官牢爹 //////

	// 傍烹
	Net->Dis.AddHandler(ContentsPacketType::ObjectUpdate, std::bind(&GameServer::ObjectUpdatePacketProcess, this, std::placeholders::_1));

	// 磊脚狼 惑怕 菩哦 贸府, 惑怕 : 蜡历 霖厚, 
	Net->Dis.AddHandler(ContentsPacketType::PlayerState, std::bind(&GameServer::PlayerStatePacketProcess, this, std::placeholders::_1));

	// 盒府
	if (true == Net->GetIsHost())
	{
		// 郴啊 辑滚老锭父 殿废秦具窍绰 菩哦贸府
	}
	else
	{
		// 郴啊 努扼捞攫飘 老锭父 殿废秦具窍绰 菩哦贸府
		Net->Dis.AddHandler(ContentsPacketType::ClientInit, std::bind(&GameServer::ClientInitPacketProcess, this, std::placeholders::_1));

		// 辑滚啊 焊郴林绰 脚龋菩哦 贸府
		Net->Dis.AddHandler(ContentsPacketType::GameState, std::bind(&GameServer::GameStatePacketProcess, this, std::placeholders::_1));
	}

}

// 搬苞拳搁 唱坷绊 歹捞惑 辑滚 楷搬 鞘夸 绝阑 锭 龋免
void GameServer::ServerEnd()
{
}


////////////////////
///	 菩哦 贸府
////////////////////
void GameServer::ObjectUpdatePacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{

	// 罐篮 菩哦捞 ObjectUpdatePacket
	// ObjectUpdatePacket 吝 鸥涝阑 烹秦 贸府
	std::shared_ptr<ObjectUpdatePacket> Packet = std::dynamic_pointer_cast<ObjectUpdatePacket>(_Packet);

	GameServerObject* FindObject = GameServerObject::GetServerObject(Packet->ObjectID);

	// 绝栏搁 积己
	if (nullptr == FindObject)
	{
		std::lock_guard<std::mutex> LockGuard(Lock);
		NewObjectUpdatePacketList_.push_back(Packet);
	}
	// 乐栏搁 磊脚捞 贸府秦具且 菩哦 府胶飘俊 眠啊
	else
	{
		std::lock_guard<std::mutex> LockGuard(Lock);
		FindObject->PushPacket(_Packet);
	}

	// 龋胶飘扼搁 葛电 努扼俊霸 傈崔
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
		MsgBoxAssert("努扼捞攫飘 init菩哦捞 酒凑聪促");
	}

	if (true == Net->GetIsHost())
	{
		MsgBoxAssert("龋胶飘牢单 努扼捞攫飘侩 菩哦阑 罐疽嚼聪促.");
	}


	// 努扼捞攫飘狼 mainplayer
	//MainPlayer->ClientInit(ServerObjectType::Player, Packet->ObjectID);

	PlayerID_ = Packet->ObjectID;
}

// 霸烙惑怕 沥焊
void GameServer::GameStatePacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<GameStatePacket> Packet = std::dynamic_pointer_cast<GameStatePacket>(_Packet);

	if (Packet->ServerSignal != 0)
	{
		//GameEngineDebug::OutPutString("GameStatePacketProcess >> " + std::to_string(Packet->ServerSignal));
	}

	// 努扼捞攫飘父 辑滚 脚龋 罐澜
	if (false == Net->GetIsHost())
	{
		//ServerSignal_ = static_cast<ServerFlag>(ServerSignal_ | Packet->ServerSignal);
		ServerSignal_ = static_cast<ServerFlag>(Packet->ServerSignal);
	}

}

// 葛电 蜡历啊 辑肺狼 沥焊甫 舅绊 乐澜
void GameServer::PlayerStatePacketProcess(std::shared_ptr<GameServerPacket> _Packet)
{
	std::shared_ptr<PlayerStatePacket> Packet = std::dynamic_pointer_cast<PlayerStatePacket>(_Packet);

	// 葛电 敲饭捞绢 沥焊 历厘
	OtherPlayersInfo_[Packet->PlayerID] = Packet;

	if (true == Net->GetIsHost())
	{
		GameServer::Net->SendPacket(Packet);
	}
}

////////////////////
///	 ~ 菩哦 贸府
////////////////////

// *龋胶飘父 龋免
void GameServer::SendGameStatePacket()
{
	if (ServerFlag::S_None == ServerSignal_)
	{
		return;
	}

	std::shared_ptr<GameStatePacket> Packet = std::make_shared<GameStatePacket>();	

	// 辑滚啊 葛电 努扼捞攫飘俊霸 林绰 脚龋
	Packet->ServerSignal = static_cast<unsigned int>(ServerSignal_);

	Net->SendPacket(Packet);
}

// 葛滴 龋免
void GameServer::SendPlayerStatePacket()
{ 
	std::shared_ptr<PlayerStatePacket> Packet = std::make_shared<PlayerStatePacket>();

	Packet->PlayerID = PlayerID_;
	
	// 磊脚狼 惑怕甫 舅覆
	Packet->PlayerStateSignal = static_cast<unsigned int>(PlayerSignal_);

	// 痢荐
	Packet->PlayerScore = PlayerScore_;

	// 敲饭捞绢 胶挪沥焊(祸惑)
	Packet->PlayerColor = PlayerColorID_;

	// 矫埃
	if (true == IsHost_)
	{
		Packet->PlayTime = PlayTime_;
	}
	else
	{
		Packet->PlayTime = 0;
	}

	Packet->PlayerName = UserName_;

	Net->SendPacket(Packet);
}
