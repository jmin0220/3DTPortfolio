#include "PreCompile.h"
#include "ContentsCore.h"
#include "TitleLevel.h"
#include "LobbyLevel.h"
#include "MidScoreLevel.h"
#include "LoadingLevel.h"
#include "WinnerLevel.h"
#include "MapEditorLevel.h"
#include "MapEditorGUI.h"
#include "PhysicsTestLevel.h"
#include "LJM_PhysXHelloWorld.h"
#include "LJM_PhysXPlayerTest.h"
#include "LJM_PhysXBoxGeometryTest.h"
#include "PhysXLevel.h"
#include "CameraTestLevel.h"
#include "ScaleTestLevel.h"
#include "ShaderTutorialLevel.h"
#include "GameManagerGUI.h"
#include "StageTestLevel.h"
#include "DoorDashLevel.h"
#include "HoopsLegendsLevel.h"
#include "JumpClubLevel.h"
#include "BigShotsLevel.h"
#include "HexAGoneLevel.h"
#include "PlayerTestLevel.h"
#include "GameServer.h"

#pragma comment(lib, "GameEngineBase.lib")
#include <GameEngineCore/GameEngineRes.h>
#include <GameEngineBase/GameEnginePath.h>

std::shared_ptr<ContentsCore> ContentsCore::Inst_ = std::make_shared<ContentsCore>();
std::vector<GameEngineLevel*> ContentsCore::TestLevels_;
std::vector<GameEngineLevel*> ContentsCore::GameLevels_;

std::shared_ptr<GameServerGUI> ContentsCore::ServerGUI_;

void ContentsCore::ChangeLevelByLoading(std::string_view _Level)
{
	// �ε������� �ϴ� ��, ���� ���������� �����...
	InitLoadingProgress();
	LoadingLevel::SetLoadingStage(_Level);
	ChangeLevel(LEVEL_NAME_LOADING);
}

void ContentsCore::ChangeLevelByThread(std::string_view _Level)
{
	InitLoadingProgress();
	
	GameEngineCore::EngineThreadPool.Work(
		[=]()
		{
			LoadLevelResource(StringLevelToLEVELS(_Level));
		}
	);

}

ContentsCore::ContentsCore()
	: GameEngineCore()
	, LoadingSize_(0)
	, LoadingProgress_(0)
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	GameEngineTime::SetLimitFrame(60);

	CreateKeys();
	CreateShaders();
	LoadShaders();
	LoadCommonResources();
	CreateLevels();

	//GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("GameEngineStatusWindow", nullptr); //GUI �߰� 
	GameEngineGUI::CreateGUIWindow<GameManagerGUI>("GameManager", nullptr);
}

void ContentsCore::Update(float _DeltaTime)
{
	if (false == GameServer::GetInst()->IsServerStart())
	{
		return;
	}
	
	// ID�� ���� ���� ����(���� : ȣ��Ʈ, Ŭ���̾�Ʈ) �� ��Ŷ ������
	if (-1 == GameServer::GetInst()->PlayerID_)
	{
		return;
	}


	////////////////////////////
	// ȣ��Ʈ�� ���� ����ȭ ����
	// - �κ� -> �ε�ȭ�� �Ѿ�� �κ�
	// - �ε� -> �������� �Ѿ�� �κ�
	// - �������� -> ���ӻ���(�غ�, ����, ����) �Ѿ�� �κ�
	////////////////////////////

	// ����(ȣ��Ʈ)
	if (true == GameServer::IsHost_)
	{
		// GUI���� ���ӽ��� ��ư ������
		if (true == ServerGUI_->GameStart_)
		{
			GameServer::GetInst()->SetServerSignal(ServerFlag::S_GameStartChangeReady);
			ServerGUI_->GameStart_ = false;
		}

		//// �ε�����
		//if (true == LoadingLevel::AllPlayersReady_)
		//{
		//	GameServer::GetInst()->AddServerSignal(ServerFlag::StateChange);
		//	LoadingLevel::AllPlayersReady_ = false;
		//}

		//// ������������
		//if (true == StageParentLevel::AllPlayersReady_)
		//{
		//	GameServer::GetInst()->AddServerSignal(ServerFlag::StateChange);
		//}

		// ȣ��Ʈ�� ��ü ���� ��ȣ ����
		GameServer::GetInst()->SendGameStatePacket();
	}

	// ȣ��Ʈ ���� ��� ������ ���� ���� ����
	GameServer::GetInst()->SendPlayerStatePacket();

}

void ContentsCore::End()
{
}

void ContentsCore::CreateKeys()
{
	GameEngineInput::GetInst()->CreateKey(KEY_MOUSELEFT, VK_LBUTTON);
	GameEngineInput::GetInst()->CreateKey(KEY_MOUSERIGHT, VK_RBUTTON);
	GameEngineInput::GetInst()->CreateKey(KEY_W, 'W');
	GameEngineInput::GetInst()->CreateKey(KEY_A, 'A');
	GameEngineInput::GetInst()->CreateKey(KEY_S, 'S');
	GameEngineInput::GetInst()->CreateKey(KEY_D, 'D');
	GameEngineInput::GetInst()->CreateKey(AXIS_MOVE, 'Q');
	GameEngineInput::GetInst()->CreateKey(AXIS_ROTATE, 'E');
	GameEngineInput::GetInst()->CreateKey(KEY_SPACEBAR, VK_SPACE);
	GameEngineInput::GetInst()->CreateKey(KEY_ENTER, VK_RETURN);
}

// �⺻���� ���ҽ�(UI, �κ�, ...)
// ���������� �޽����� ������ OnEvent���� �ε��ؾߵ�
void ContentsCore::LoadCommonResources()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("Resources");
	Dir.Move("Resources");

	// ��Ʈ
	{
		GameEngineDirectory FontDir(Dir);
		FontDir.Move("Font");

		GameEngineFont::Load(FONT_NOTO_SANS_CJK_SC);
		GameEngineFont::Load(FONT_TITAN_ONE);
	}

	// Texture2D
	{
		GameEngineDirectory TextureDir(Dir);
		TextureDir.Move("Texture2D");
		for (GameEngineDirectory& Folder : TextureDir.GetRecursiveAllDirectory())
		{
			std::vector<GameEngineFile> Files = Folder.GetAllFile(EXT_PNG);
			for (GameEngineFile& File : Files)
			{
				std::shared_ptr<GameEngineTexture>Texture = GameEngineTexture::Load(File.GetFullPath());
			}
		}
	}

	// �Ҹ�
	{
		GameEngineDirectory TextureDir(Dir);
		TextureDir.Move("Sound");

		std::vector<GameEngineFile> Files = TextureDir.GetAllFile(EXT_MP3);
		for (GameEngineFile& File : Files)
		{
			GameEngineSound::LoadRessource(File.GetFullPath());
		}
	}
}

void ContentsCore::CreateLevels()
{
	{
		GameEngineLevel* Level = CreateLevel<TitleLevel>(LEVEL_NAME_TITLE);
		GameLevels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<LobbyLevel>(LEVEL_NAME_LOBBY);
		GameLevels_.push_back(Level);

		ServerGUI_ = GameEngineGUI::CreateGUIWindow<GameServerGUI>("ServerManager", Level);
		ServerGUI_->Off();
	}
	{
		GameEngineLevel* Level = CreateLevel<LoadingLevel>(LEVEL_NAME_LOADING);
		GameLevels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<MidScoreLevel>(LEVEL_NAME_MIDSCORE);
		GameLevels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<DoorDashLevel>(LEVEL_NAME_DOORDASH);
		GameLevels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<JumpClubLevel>(LEVEL_NAME_JUMPCLUB);
		GameLevels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<BigShotsLevel>(LEVEL_NAME_BIGSHOTS);
		GameLevels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<HexAGoneLevel>(LEVEL_NAME_HEXAGONE);
		GameLevels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<HoopsLegendsLevel>(LEVEL_NAME_HOOPSLEGENDS);
		GameLevels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<WinnerLevel>(LEVEL_NAME_WINNER);
		GameLevels_.push_back(Level);
	}
	

	for (GameEngineLevel* Level : GameLevels_)
	{
		Level->GetMainCameraActor()->OffFreeCameraMode();
		Level->GetUICameraActor()->OffFreeCameraMode();
	}

	// ********* ���� *********
	//		  �׽�Ʈ ���� 

	{
		GameEngineLevel* Level = CreateLevel<MapEditorLevel>(LEVEL_NAME_MAP_EDITER);
		TestLevels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<CameraTestLevel>(LEVEL_NAME_CAMERA_TEST);
		TestLevels_.push_back(Level);
	}
	{
		//GameEngineLevel* Level = CreateLevel<PhysXLevel>("PhysXLevel");
		//TestLevels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<ScaleTestLevel>(LEVEL_NAME_SCALE_TEST);
		TestLevels_.push_back(Level);
	}	

	{
		GameEngineLevel* Level = CreateLevel<PlayerTestLevel>(LEVEL_NAME_PLAYER_TEST);
		TestLevels_.push_back(Level);
	}

	{
		GameEngineLevel* Level = CreateLevel<ShaderTutorialLevel>(LEVEL_NAME_SHADER_TUTORIAL);
		TestLevels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<StageTestLevel>("StageTestLevel");
		TestLevels_.push_back(Level);
	}

	//{
	//	GameEngineLevel* Level = CreateLevel<LJM_PhysXHelloWorld>(LEVEL_NAME_PHYSX_HELLOWORLD);
	//	Levels_.push_back(Level);
	//}
	
	//CreateLevel<PhysicsTestLevel>(LEVEL_NAME_PHYSICS_TEST);
	//CreateLevel<LJM_PhysXPlayerTest>(LEVEL_NAME_PHYSX_PLAYER_TEST);
	//CreateLevel<LJM_PhysXBoxGeometryTest>(LEVEL_NAME_PHYSX_BOX_GEOMETRY_TEST);



	ChangeLevel(LEVEL_NAME_TITLE);
}

void ContentsCore::CreateShaders()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ContentsShader");
	Dir.Move("ContentsShader");

	std::vector<GameEngineFile> Shaders = Dir.GetAllFile("hlsl");
	for (size_t i = 0; i < Shaders.size(); i++)
	{
		GameEngineShader::AutoCompile(Shaders[i].GetFullPath());
	}
}

void ContentsCore::LoadShaders()
{
	{
		std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Create("MaskShader");
		Material->SetVertexShader("MaskShader.hlsl");
		Material->SetPixelShader("MaskShader.hlsl");
	}


	{
		std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Create("Water");
		Material->SetVertexShader("WaterShader.hlsl");
		Material->SetPixelShader("WaterShader.hlsl");
	}

	{
		std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Create("TextureCustom");
		Material->SetVertexShader("TextureCustom.hlsl");
		Material->SetPixelShader("TextureCustom.hlsl");
	}

	{
		std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Create("TextureAnimationCustom");
		Material->SetVertexShader("TextureAnimationCustom.hlsl");
		Material->SetPixelShader("TextureAnimationCustom.hlsl");
	}

	{
		std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Create("TextureLoop");
		Material->SetVertexShader("TextureLoop.hlsl");
		Material->SetPixelShader("TextureLoop.hlsl");
	}

	{
		//�ؽ��� Color ��
		std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Create("TextureColor");
		Material->SetVertexShader("TextureColor.hlsl");
		Material->SetPixelShader("TextureColor.hlsl");
	}

	{
		std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Create("CustomColor");
		Material->SetVertexShader("CustomColor.hlsl");
		Material->SetPixelShader("CustomColor.hlsl");
	}

	{
		//�迹�� ���̴� �׽�Ʈ
		std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Create("RtoLSlice");
		Material->SetVertexShader("RtoLSlice.hlsl");
		Material->SetPixelShader("RtoLSlice.hlsl");
	}

	{
		//�迹�� ���̴� �߰�
		std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Create("DownLoop");
		Material->SetVertexShader("DownLoop.hlsl");
		Material->SetPixelShader("DownLoop.hlsl");
	}

	{
		std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Create("Fog");
		Material->SetVertexShader("Fog.hlsl");
		Material->SetPixelShader("Fog.hlsl");
	}


	// ����Ʈ ����Ʈ��
	{
		std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Create("Bloom");
		Material->SetVertexShader("Bloom.hlsl");
		Material->SetPixelShader("Bloom.hlsl");
	}
	// ~ ����Ʈ ����Ʈ��

}

//////////////////////////////////////////////////////
//	���� ���ҽ� �ε� (�޽�)
//////////////////////////////////////////////////////

// ���緹�� �����, ������ ���ҽ� ����
void ContentsCore::ReleaseCurLevelResource()
{
	//GameEngineRes<GameEngineFBXMesh>::ResourcesDestroy();
	//GameEngineRes<GameEngineFBXAnimation>::ResourcesDestroy();

	GameEngineFBXMesh::ResourcesDestroy();
	GameEngineFBXAnimation::ResourcesDestroy();
}

void ContentsCore::LoadLevelResource(LEVELS _LEVEL)
{

	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory(DIR_RESOURCES);
	Dir.Move(DIR_RESOURCES);

	switch (_LEVEL)
	{
		//////////////////////
		// ���ӿ� ����� ����
		//////////////////////

	case LEVELS::LOBBY:
		Dir.Move(DIR_LEVEL_LOBBY);
		ResLoadLobby(Dir);
		break;
	case LEVELS::MIDSCORE:
		Dir.Move(DIR_LEVEL_MIDSCORE);
		ResLoadMidScore(Dir);
		break;
	case LEVELS::LOADING:
		break;
	case LEVELS::STAGE01_DOORDASH:
		Dir.Move(DIR_LEVEL_STAGE01);
		ResLoadStage01(Dir);
		break;
	case LEVELS::STAGE02_JUMPCLUB:
		Dir.Move(DIR_LEVEL_STAGE02);
		ResLoadStage02(Dir);
		break;
	case LEVELS::STAGE03_BIGSHOTS:
		Dir.Move(DIR_LEVEL_STAGE03);
		ResLoadStage02(Dir);
		break;
	case LEVELS::STAGE04_HEX_A_GONE:
		Dir.Move(DIR_LEVEL_STAGE04);
		ResLoadStage04(Dir);
		break;
	case LEVELS::STAGE05_HOOPS_LEGENDS:
		Dir.Move(DIR_LEVEL_STAGE05);
		ResLoadStage05(Dir);
		break;
	case LEVELS::WINNNER:
		Dir.Move(DIR_LEVEL_WINNER);
		ResLoadWinner(Dir);
		break;

		////////////////////
		//	�ӽ�/�׽�Ʈ ����
		////////////////////

	case LEVELS::LOBBY_TEST:
		Dir.Move(DIR_TESTLEVEL_LOBBY);
		ResLoadCameraTest(Dir);
		break;
	case LEVELS::CAMERA_TEST:
		Dir.Move(DIR_TESTLEVEL_CAMERA);
		ResLoadCameraTest(Dir);
		break;
	case LEVELS::PHYSX_TEST:
		Dir.Move(DIR_TESTLEVEL_PHYSX);
		ResLoadCameraTest(Dir);
		break;
	case LEVELS::PHYSICS_TEST:
		Dir.Move(DIR_TESTLEVEL_PHISICS);
		ResLoadCameraTest(Dir);
		break;
		// Editor GUI���� ���ҽ� �ε� ���ֱ� ������ �ӽÿ뵵
	case LEVELS::MAP_EDITOR:
		Dir.Move(DIR_TESTLEVEL_MAPEDITOR);
		ResLoadMapEditor(Dir);
		break;
	case LEVELS::SCALE_TEST:
		Dir.Move(DIR_TESTLEVEL_SCALETEST);
		ResScaleTest(Dir);
		break;
	case LEVELS::PLAYER_TEST:
		Dir.Move(DIR_TESTLEVEL_PLAYERTEST);
		ResScaleTest(Dir);
		break;

	default:
		break;
	}
}

/////////////////////////////////////////////////////////
// # ���ҽ� �ε�
// - ���� ���� ��, ��� ���� ��ȸ 
// - �ؽ��Ĵ� ���� ��� ��ο��� �ߺ��� ����
// - ���� �ȿ��� �ߺ��� FBX�� ����, ������ �ٸ��� �������
// 
//  
// # LevelAllResourceLoad
// - ���丮�� ��� ���ҽ� �ε�
// - ���������� ���ҽ� �����Ͽ� �ε��ϰ� ������ �ּ�ó��
/////////////////////////////////////////////////////////


// ���� ����
void ContentsCore::ResLoadLobby(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}

void ContentsCore::ResLoadLoading(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}

void ContentsCore::ResLoadMidScore(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}

void ContentsCore::ResLoadStage02(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}

void ContentsCore::ResLoadStage03(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}

void ContentsCore::ResLoadStage04(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}

void ContentsCore::ResLoadStage05(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}

void ContentsCore::ResLoadWinner(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}


// �ӽ�/�׽�Ʈ ����
void ContentsCore::ResLoadTmpTest(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}

void ContentsCore::ResLoadMapEditor(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}

void ContentsCore::ResLoadStage01(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}



void ContentsCore::ResScaleTest(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}

void ContentsCore::ResLoadCameraTest(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}

void ContentsCore::ResLoadPhysXTest(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}

void ContentsCore::ResLoadPhysicsTest(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}


void ContentsCore::LevelAllResourceLoad(GameEngineDirectory& _LevelDir)
{
	std::vector<GameEngineDirectory> LevelFolders = _LevelDir.GetRecursiveAllDirectory();

	// ��ü ũ�� ��

	for (GameEngineDirectory& Folder : LevelFolders)
	{
		GameEngineDirectory Dir(Folder.GetFullPath());
		std::vector<GameEngineFile> Files = Dir.GetAllFile(EXT_FBX);
		LoadingSize_ += static_cast<float>(Files.size());
	}


	for (GameEngineDirectory& Folder : LevelFolders)
	{
		GameEngineDirectory Dir(Folder.GetFullPath());

		// Mesh & Animation
		{
			std::vector<GameEngineFile> Files = Dir.GetAllFile(EXT_FBX);
			
			for (GameEngineFile& File : Files)
			{
				File.ChangeExtension(".FBX");
				std::string Path = File.GetFullPath();

				std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Path);

				std::shared_ptr<GameEngineFBXAnimation> Anim = GameEngineFBXAnimation::Load(Path);
				++LoadingProgress_;
			}
		}
	}
}

LEVELS ContentsCore::StringLevelToLEVELS(std::string_view _StringLevel)
{
	std::string Level = GameEngineString::ToUpperReturn(_StringLevel.data());

	if (0 == Level.compare(GameEngineString::ToUpperReturn(LEVEL_NAME_LOBBY)))
	{
		return LEVELS::LOBBY;
	}
	else if (0 == Level.compare(GameEngineString::ToUpperReturn(LEVEL_NAME_MIDSCORE)))
	{
		return LEVELS::MIDSCORE;
	}
	else if (0 == Level.compare(GameEngineString::ToUpperReturn(LEVEL_NAME_DOORDASH)))
	{
		return LEVELS::STAGE01_DOORDASH;
	}
	else if (0 == Level.compare(GameEngineString::ToUpperReturn(LEVEL_NAME_JUMPCLUB)))
	{
		return LEVELS::STAGE02_JUMPCLUB;
	}
	else if (0 == Level.compare(GameEngineString::ToUpperReturn(LEVEL_NAME_BIGSHOTS)))
	{
		return LEVELS::STAGE03_BIGSHOTS;
	}
	else if (0 == Level.compare(GameEngineString::ToUpperReturn(LEVEL_NAME_HEXAGONE)))
	{
		return LEVELS::STAGE04_HEX_A_GONE;
	}
	else if (0 == Level.compare(GameEngineString::ToUpperReturn(LEVEL_NAME_HOOPSLEGENDS)))
	{
		return LEVELS::STAGE05_HOOPS_LEGENDS;
	}
	else if (0 == Level.compare(GameEngineString::ToUpperReturn(LEVEL_NAME_WINNER)))
	{
		return LEVELS::WINNNER;
	}

	return LEVELS::NONE;
}

std::string_view ContentsCore::StringLevelToStringSetLevel(std::string_view _StringLevel)
{
	std::string Level = GameEngineString::ToUpperReturn(_StringLevel.data());
	if (0 == Level.compare(GameEngineString::ToUpperReturn(LEVEL_NAME_LOBBY)))
	{
		return LEVEL_NAME_LOBBY;
	}
	else if (0 == Level.compare(GameEngineString::ToUpperReturn(LEVEL_NAME_MIDSCORE)))
	{
		return LEVEL_NAME_MIDSCORE;
	}
	else if (0 == Level.compare(GameEngineString::ToUpperReturn(LEVEL_NAME_DOORDASH)))
	{
		return LEVEL_NAME_DOORDASH;
	}
	else if (0 == Level.compare(GameEngineString::ToUpperReturn(LEVEL_NAME_JUMPCLUB)))
	{
		return LEVEL_NAME_JUMPCLUB;
	}
	else if (0 == Level.compare(GameEngineString::ToUpperReturn(LEVEL_NAME_BIGSHOTS)))
	{
		return LEVEL_NAME_BIGSHOTS;
	}
	else if (0 == Level.compare(GameEngineString::ToUpperReturn(LEVEL_NAME_HEXAGONE)))
	{
		return LEVEL_NAME_HEXAGONE;
	}
	else if (0 == Level.compare(GameEngineString::ToUpperReturn(LEVEL_NAME_HOOPSLEGENDS)))
	{
		return LEVEL_NAME_HOOPSLEGENDS;
	}
	else if (0 == Level.compare(GameEngineString::ToUpperReturn(LEVEL_NAME_WINNER)))
	{
		return LEVEL_NAME_WINNER;
	}

	return "";
}
