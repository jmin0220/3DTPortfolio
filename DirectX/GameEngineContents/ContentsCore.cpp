#include "PreCompile.h"
#include "ContentsCore.h"
#include "tmpLevel.h"
#include "MapEditorLevel.h"
#include "MapEditorGUI.h"
#include "PhysicsTestLevel.h"
#include "LJM_PhysXHelloWorld.h"

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
}

// �⺻���� ���ҽ�
void ContentsCore::LoadResources()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("Resources");
	Dir.Move("Resources");

	// �ؽ��� �ε�
	{
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Load(Files[i].GetFullPath());
		}
	}

	GameEngineFont::Load("Noto Sans CJK SC");//�������� ��Ʈ
	GameEngineFont::Load("Titan One");
	




	//�޽� �ε�
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
	CreateLevel<MapEditorLevel>("MapEditorLevel");
	CreateLevel<PhysicsTestLevel>("PhysicsTestLevel");
	CreateLevel<LJM_PhysXHelloWorld>("LJM_PhysXHelloWorld");
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
}
