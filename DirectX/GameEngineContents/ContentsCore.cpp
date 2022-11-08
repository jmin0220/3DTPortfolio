#include "PreCompile.h"
#include "ContentsCore.h"
#include "tmpLevel.h"
#include "LoadingLevel.h"
#include "MapEditorLevel.h"
#include "MapEditorGUI.h"
#include "PhysicsTestLevel.h"
#include "LJM_PhysXHelloWorld.h"
#include "LJM_PhysXPlayerTest.h"
#include "CameraTestLevel.h"

#pragma comment(lib, "GameEngineBase.lib")

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
	LoadResources();

	CreateShaders();
	LoadShaders();

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
	GameEngineInput::GetInst()->CreateKey("SpaceBar", VK_SPACE);
}

// 기본적인 리소스(UI, 로비, ...)
// 스테이지의 메쉬들은 각각의 OnEvent에서 로드해야됨
void ContentsCore::LoadResources()
{
	{
		//스프라이트
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory(DIR_RESOURCES);
		Dir.Move(DIR_RESOURCES);

		// 텍스쳐 로드
		{
			std::vector<GameEngineFile> Files = Dir.GetAllFile();

			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineTexture::Load(Files[i].GetFullPath());
			}
		}

		GameEngineFont::Load(FONT_NOTO_SANS_CJK_SC);//폴가이즈 폰트
		GameEngineFont::Load(FONT_TITAN_ONE);
	}

	{
		//게임 설명샷
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory(DIR_RESOURCES);
		Dir.Move(DIR_RESOURCES);
		Dir.Move(DIR_GAMES);

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Load(Files[i].GetFullPath());
		}
	}

	// TODO::테스트용 임시코드
	// 캐릭터 텍스쳐 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory(DIR_RESOURCES);
		Dir.Move(DIR_RESOURCES);
		Dir.Move(DIR_MESH);
		Dir.Move(DIR_CHARACTER);

		std::vector<GameEngineFile> Files = Dir.GetAllFile(EXT_PNG);

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Load(Files[i].GetFullPath());
		}

		// 메쉬 로드
		GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(Dir.PlusFilePath(FBX_NAME_CHARACTER));
	}
	

	//메쉬 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory(DIR_RESOURCES);
		Dir.Move(DIR_RESOURCES);
		Dir.Move(DIR_MESH);
		Dir.Move(DIR_DOORDASH_MESH);

		{
			GameEngineDirectory MeshDir = Dir;
			MeshDir.Move(DIR_RAINBOW);
			GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath(FBX_NAME_RAINBOW));
		}

	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory(DIR_RESOURCES);
		Dir.Move(DIR_RESOURCES);
		Dir.Move(DIR_MESH);

		{
			GameEngineDirectory MeshDir = Dir;
			MeshDir.Move(DIR_TESTMAP);
			GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath(FBX_NAME_TESTMAP));
		}
	}
}

void ContentsCore::CreateLevels()
{
	CreateLevel<tmpLevel>(LEVEL_NAME_TMP);
	CreateLevel<LoadingLevel>(LEVEL_NAME_LOADING);
	CreateLevel<MapEditorLevel>(LEVEL_NAME_MAP_EDITER);
	CreateLevel<PhysicsTestLevel>(LEVEL_NAME_PHYSICS_TEST);
	//CreateLevel<LJM_PhysXHelloWorld>(LEVEL_NAME_PHYSX_HELLOWORLD);
	CreateLevel<LJM_PhysXPlayerTest>(LEVEL_NAME_PHYSX_PLAYER_TEST);
	CreateLevel<CameraTestLevel>(LEVEL_NAME_CAMERA_TEST);
	ChangeLevel(LEVEL_NAME_MAP_EDITER);
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
		GameEngineMaterial* Material = GameEngineMaterial::Create("Water");
		Material->SetVertexShader("WaterShader.hlsl");
		Material->SetPixelShader("WaterShader.hlsl");
	}

	{
		GameEngineMaterial* Material = GameEngineMaterial::Create("TextureCustom");
		Material->SetVertexShader("TextureCustom.hlsl");
		Material->SetPixelShader("TextureCustom.hlsl");
	}
}
