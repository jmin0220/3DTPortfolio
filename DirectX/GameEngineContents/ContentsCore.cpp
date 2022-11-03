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
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("Resources");
	Dir.Move("Resources");

	// 텍스쳐 로드
	{
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Load(Files[i].GetFullPath());
		}
	}

	GameEngineFont::Load("Noto Sans CJK SC");//폴가이즈 폰트
	GameEngineFont::Load("Titan One");
	
	// TODO::테스트용 임시코드
	// 캐릭터 텍스쳐 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources/Mesh/Character");

		std::vector<GameEngineFile> Files = Dir.GetAllFile(".png");

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Load(Files[i].GetFullPath());
		}
	}



	//메쉬 로드
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Mesh");
		Dir.Move("DoorDashMesh");

		{
			GameEngineDirectory MeshDir = Dir;
			MeshDir.Move("RainBow");
			GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Rainbow.FBX"));
			std::vector<FBXNodeInfo> Nodes = Mesh->CheckAllNode();
		}
	}
}

void ContentsCore::CreateLevels()
{
	CreateLevel<tmpLevel>("tmpLevel");
	CreateLevel<LoadingLevel>("Loading");
	CreateLevel<MapEditorLevel>("MapEditorLevel");
	CreateLevel<PhysicsTestLevel>("PhysicsTestLevel");
	CreateLevel<LJM_PhysXHelloWorld>("LJM_PhysXHelloWorld");
	CreateLevel<LJM_PhysXPlayerTest>("LJM_PhysXPlayerTest");
	CreateLevel<CameraTestLevel>("CameraTestLevel");
	ChangeLevel("MapEditorLevel");
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
