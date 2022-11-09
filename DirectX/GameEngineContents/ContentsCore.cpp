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
	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("GameEngineStatusWindow", nullptr); //GUI �߰� 

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

// �⺻���� ���ҽ�(UI, �κ�, ...)
// ���������� �޽����� ������ OnEvent���� �ε��ؾߵ�
void ContentsCore::LoadResources()
{
	//1. ��Ʈ 
	//2. ��������Ʈ
	//3. Games
	//3. ĳ����
	//4. ������
	//5. �׽�Ʈ ��
	


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

	// ��������Ʈ
	{
		GameEngineDirectory SpriteDir(Dir);
		SpriteDir.Move("UI");

		std::vector<GameEngineFile> Files = SpriteDir.GetAllFile(".png");

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Load(Files[i].GetFullPath());
		}
	}

	// �� ����ȭ���
	{
		GameEngineDirectory GamesDir(Dir);
		GamesDir.Move("Games");

		std::vector<GameEngineFile> Files = GamesDir.GetAllFile(".png");

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Load(Files[i].GetFullPath());
		}
	}

	// ĳ����
	{
		GameEngineDirectory CharacterDir(Dir);
		CharacterDir.Move("Levels\\TestLevel\\Character");

		std::vector<GameEngineFile> Files = CharacterDir.GetAllFile(".png");
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Load(Files[i].GetFullPath());
		}

		GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(CharacterDir.PlusFilePath(FBX_NAME_CHARACTER));
	}

	// ������
	{
		GameEngineDirectory RainbowDir(Dir);
		RainbowDir.Move("Levels\\TestLevel\\DoorDashMesh\\RainBow");

		GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(RainbowDir.PlusFilePath(FBX_NAME_RAINBOW));
	}

	// �׽�Ʈ��
	{
		GameEngineDirectory TestMapDir(Dir);
		TestMapDir.Move("Levels\\TestLevel\\TestMap");

		GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(TestMapDir.PlusFilePath(FBX_NAME_TESTMAP));
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

	{
		GameEngineMaterial* Material = GameEngineMaterial::Create("TextureLoop");
		Material->SetVertexShader("TextureLoop.hlsl");
		Material->SetPixelShader("TextureLoop.hlsl");
	}

	{
		GameEngineMaterial* Material = GameEngineMaterial::Create("CustomColor");
		Material->SetVertexShader("CustomColor.hlsl");
		Material->SetPixelShader("CustomColor.hlsl");


	}
}
