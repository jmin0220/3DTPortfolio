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


	ImGui::Text("Level Select");
	for (GameEngineLevel* Level : ContentsCore::Levels_)
	{
		if (true == ImGui::Button(Level->GetName().data()))
		{
			GameEngineCore::ChangeLevel(Level->GetName().data());
		}

		ImGui::SameLine();
	}
}