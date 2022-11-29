#include "PreCompile.h"
#include "GameManagerGUI.h"
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCore.h>

GameManagerGUI::GameManagerGUI() 
{
}

GameManagerGUI::~GameManagerGUI() 
{
}

void GameManagerGUI::Initialize(GameEngineLevel* _Level)
{
}

void GameManagerGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	int FPS = static_cast<int>(1.0f / _DeltaTime);
	// printf 형식인데 안씀.

	std::string Name = "FPS : " + std::to_string(GameEngineTime::GetFPS());
	ImGui::Text(Name.c_str());


	if (true == ImGui::Button("CollisionDebugSwtich"))
	{
		GEngine::CollisionDebugSwitch();
	}
	ImGui::SameLine();
	if (true == ImGui::Button("FreeCameaOnOff"))
	{
		GEngine::GetCurrentLevel()->GetMainCameraActor()->FreeCameraModeOnOff();
	}

	ImGui::Text("TestLevel Select");
	for (GameEngineLevel* Level : ContentsCore::TestLevels_)
	{
		if (true == ImGui::Button(Level->GetName().data()))
		{
			ContentsCore::GetInst()->ChangeLevel(Level->GetName().data());
		}

		ImGui::SameLine();
	}

	ImGui::NewLine();
	ImGui::Text("GameLevel Select");

	// 리소스로딩 하면 로딩 레벨로 들어가서 스레드로딩 방식으로 변경
	for (GameEngineLevel* Level : ContentsCore::GameLevels_)
	{
		if (true == ImGui::Button(Level->GetName().data()))
		{
			ContentsCore::GetInst()->ChangeLevelByLoading(Level->GetName().data());
		}

		ImGui::SameLine();
	}
}