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
}

// 기본적인 리소스
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
	
}

void ContentsCore::CreateLevels()
{
	CreateLevel<tmpLevel>("tmpLevel");
	CreateLevel<MapEditorLevel>("MapEditorLevel");
	CreateLevel<PhysicsTestLevel>("PhysicsTestLevel");
	CreateLevel<LJM_PhysXHelloWorld>("LJM_PhysXHelloWorld");
	ChangeLevel("LJM_PhysXHelloWorld");
}
