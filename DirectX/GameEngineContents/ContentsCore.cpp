#include "PreCompile.h"
#include "ContentsCore.h"
#include "tmpLevel.h"
#include "LoadingLevel.h"
#include "MapEditorLevel.h"
#include "MapEditorGUI.h"
#include "PhysicsTestLevel.h"
#include "LJM_PhysXHelloWorld.h"
#include "LJM_PhysXPlayerTest.h"
#include "LJM_PhysXBoxGeometryTest.h"
#include "PhysXLevel.h"
#include "CameraTestLevel.h"

#pragma comment(lib, "GameEngineBase.lib")
#include <GameEngineCore/GameEngineRes.h>

std::shared_ptr<ContentsCore> ContentsCore::Inst_ = std::make_shared<ContentsCore>();

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

	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("GameEngineStatusWindow", nullptr); //GUI 추가 

}

void ContentsCore::Update(float _DeltaTime)
{
}

void ContentsCore::End()
{
}

void ContentsCore::CreateKeys()
{
	GameEngineInput::GetInst()->CreateKey("VK_LBUTTON", VK_LBUTTON);
	GameEngineInput::GetInst()->CreateKey("W", 'W');
	GameEngineInput::GetInst()->CreateKey("A", 'A');
	GameEngineInput::GetInst()->CreateKey("S", 'S');
	GameEngineInput::GetInst()->CreateKey("D", 'D');
	GameEngineInput::GetInst()->CreateKey(AXIS_MOVE, 'Q');
	GameEngineInput::GetInst()->CreateKey(AXIS_ROTATE, 'E');
	GameEngineInput::GetInst()->CreateKey("SpaceBar", VK_SPACE);
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
	CreateLevel<tmpLevel>(LEVEL_NAME_TMP);
	CreateLevel<LoadingLevel>(LEVEL_NAME_LOADING);
	CreateLevel<MapEditorLevel>(LEVEL_NAME_MAP_EDITER);
	//CreateLevel<PhysicsTestLevel>(LEVEL_NAME_PHYSICS_TEST);
	//CreateLevel<LJM_PhysXHelloWorld>(LEVEL_NAME_PHYSX_HELLOWORLD);
	//CreateLevel<LJM_PhysXPlayerTest>(LEVEL_NAME_PHYSX_PLAYER_TEST);
	//CreateLevel<LJM_PhysXBoxGeometryTest>(LEVEL_NAME_PHYSX_BOX_GEOMETRY_TEST);
	CreateLevel<CameraTestLevel>(LEVEL_NAME_CAMERA_TEST);

	// PhysX 튜토리얼 레벨
	CreateLevel<PhysXLevel>("PhysXLevel");

	ChangeLevel(LEVEL_NAME_TMP);
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
		std::shared_ptr<GameEngineMaterial> Material = GameEngineMaterial::Create("CustomColor");
		Material->SetVertexShader("CustomColor.hlsl");
		Material->SetPixelShader("CustomColor.hlsl");
	}
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


// 임시/테스트 레벨
void ContentsCore::ResLoadTmpTest(GameEngineDirectory& _Dir)
{
	LevelAllResourceLoad(_Dir);
}

void ContentsCore::ResLoadMapEditor(GameEngineDirectory& _Dir)
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
				std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(File.GetFullPath());

				std::shared_ptr<GameEngineFBXAnimation> Anim = GameEngineFBXAnimation::Load(File.GetFullPath());
			}
		}
	}
}