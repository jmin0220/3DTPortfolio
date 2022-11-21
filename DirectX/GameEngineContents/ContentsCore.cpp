#include "PreCompile.h"
#include "ContentsCore.h"
#include "TitleLevel.h"
#include "LobbyLevel.h"
#include "LoadingLevel.h"
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
#include "HexAGoneLevel.h"
#include "PlayerTestLevel.h"

#pragma comment(lib, "GameEngineBase.lib")
#include <GameEngineCore/GameEngineRes.h>
#include <GameEngineBase/GameEnginePath.h>

std::shared_ptr<ContentsCore> ContentsCore::Inst_ = std::make_shared<ContentsCore>();
std::vector<GameEngineLevel*> ContentsCore::Levels_;

ContentsCore::ContentsCore()
	: GameEngineCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{

	CreateKeys();
	CreateShaders();
	LoadShaders();
	LoadCommonResources();
	CreateLevels();

	//GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("GameEngineStatusWindow", nullptr); //GUI 추가 
	GameEngineGUI::CreateGUIWindow<GameManagerGUI>("GameManager", nullptr);
}

void ContentsCore::Update(float _DeltaTime)
{
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
}

// 기본적인 리소스(UI, 로비, ...)
// 스테이지의 메쉬들은 각각의 OnEvent에서 로드해야됨
void ContentsCore::LoadCommonResources()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("Resources");
	Dir.Move("Resources");

	// 폰트
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

}

void ContentsCore::CreateLevels()
{
	{
		GameEngineLevel* Level = CreateLevel<TitleLevel>(LEVEL_NAME_TITLE);
		Levels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<LobbyLevel>(LEVEL_NAME_LOBBY);
		Levels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<LoadingLevel>(LEVEL_NAME_LOADING);
		Levels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<MapEditorLevel>(LEVEL_NAME_MAP_EDITER);
		Levels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<CameraTestLevel>(LEVEL_NAME_CAMERA_TEST);
		Levels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<PhysXLevel>("PhysXLevel");
		Levels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<ScaleTestLevel>(LEVEL_NAME_SCALE_TEST);
		Levels_.push_back(Level);
	}	

	{
		GameEngineLevel* Level = CreateLevel<PlayerTestLevel>(LEVEL_NAME_PLAYER_TEST);
		Levels_.push_back(Level);
	}

	{
		GameEngineLevel* Level = CreateLevel<ShaderTutorialLevel>(LEVEL_NAME_SHADER_TUTORIAL);
		Levels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<StageTestLevel>("StageTestLevel");
		Levels_.push_back(Level);
	}
	{
		GameEngineLevel* Level = CreateLevel<HexAGoneLevel>(LEVEL_NAME_HEXAGONE);
		Levels_.push_back(Level);
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
		std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Create("TextureLoop");
		Material->SetVertexShader("TextureLoop.hlsl");
		Material->SetPixelShader("TextureLoop.hlsl");
	}

	{
		//텍스쳐 Color 용
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
		//김예나 쉐이더 테스트
		std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Create("RtoLSlice");
		Material->SetVertexShader("RtoLSlice.hlsl");
		Material->SetPixelShader("RtoLSlice.hlsl");
	}


	// 포스트 이펙트용
	{
		std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Create("Bloom");
		Material->SetVertexShader("Bloom.hlsl");
		Material->SetPixelShader("Bloom.hlsl");
	}
	// ~ 포스트 이펙트용
}

//////////////////////////////////////////////////////
//	레벨 리소스 로딩 (메쉬)
//////////////////////////////////////////////////////

// 현재레벨 종료시, 종류별 리소스 해제
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
	case LEVELS::LOBBY:
		break;
	case LEVELS::LOADING:
		break;


		// 임시/테스트 레벨
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
		// Editor GUI에서 리소스 로드 해주기 때문에 임시용도
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
	// 확인을 위해 DIR_TESTLEVEL_MAPEDITOR 그대로 사용, 추후 각 스테이지에 맞게 로드 필요
	case LEVELS::STAGE1_TEST:
		Dir.Move(DIR_TESTLEVEL_MAPEDITOR);
		ResScaleTest(Dir);
		break;
	case LEVELS::STAGE04_HEX_A_GONE:
		Dir.Move(DIR_LEVEL_STAGE04);
		ResStage04(Dir);
	default:
		break;
	}
}


/////////////////////////////////////////////////////////
// # 리소스 로드
// - 레벨 폴더 안, 모든 폴더 순회 
// - 텍스쳐는 레벨 모든 경로에서 중복시 오류
// - 레벨 안에서 중복된 FBX는 오류, 레벨이 다르면 상관없음
// 
//  
// # LevelAllResourceLoad
// - 디렉토리의 모든 리소스 로드
// - 개별적으로 리소스 선택하여 로드하고 싶으면 주석처리
/////////////////////////////////////////////////////////


// 게임 레벨
void ContentsCore::ResLoadLobby(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}

void ContentsCore::ResLoadLoading(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}

void ContentsCore::ResStage04(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}


// 임시/테스트 레벨
void ContentsCore::ResLoadTmpTest(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}

void ContentsCore::ResLoadMapEditor(GameEngineDirectory& _Dir)
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

	for (GameEngineDirectory& Folder : LevelFolders)
	{
		GameEngineDirectory Dir(Folder.GetFullPath());

		// PNG
		{
			std::vector<GameEngineFile> Files = Dir.GetAllFile(EXT_PNG);
			for (GameEngineFile& File : Files)
			{
				std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Load(File.GetFullPath());
			}
		}

		// Mesh & Animation
		{
			std::vector<GameEngineFile> Files = Dir.GetAllFile(EXT_FBX);
			for (GameEngineFile& File : Files)
			{
				File.ChangeExtension(".FBX");
				std::string Path = File.GetFullPath();

				std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Path);

				std::shared_ptr<GameEngineFBXAnimation> Anim = GameEngineFBXAnimation::Load(Path);
			}
		}
	}
}
