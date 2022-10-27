#include "PreCompile.h"
#include "ContentsCore.h"
#include "tmpLevel.h"
#include "MapEditorLevel.h"
#include "MapEditorGUI.h"
#include "PhysicsTestLevel.h"

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
	{	//���ҽ� �б�
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}
	// TODO::�ӽ÷�������
	CreateLevel<tmpLevel>("tmpLevel");
	CreateLevel<MapEditorLevel>("MapEditorLevel");
	CreateLevel<PhysicsTestLevel>("PhysicsTestLevel");
	ChangeLevel("tmpLevel");

	GameEngineGUI::CreateGUIWindow<MapEditorGUI>("MapEditorGUI", nullptr);
	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("GameEngineStatusWindow", nullptr);

	CreateKeys();
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
