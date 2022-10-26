#include "PreCompile.h"
#include "MapEditorGUI.h"
#include <GameEngineCore/CoreMinimal.h>

#include "ActorPicker.h"

MapEditorGUI::MapEditorGUI() 
{
}

MapEditorGUI::~MapEditorGUI() 
{
}


void MapEditorGUI::Initialize(GameEngineLevel* _Level)
{
}

void MapEditorGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (true == ImGui::Button("FreeCameaOnOff"))
	{
		_Level->GetMainCameraActor()->FreeCameraModeOnOff();
	}

	ImGui::SameLine();
	if (true == ImGui::Button("CollisionDebugSwtich"))
	{
		GEngine::CollisionDebugSwitch();
	}

	{
		float4 Pos = _Level->GetMainCamera()->GetTransform().GetWorldPosition();
		std::string Name = "MainCameraWorldPos : " + std::to_string(Pos.x) + " | " + std::to_string(Pos.y) + " | " + std::to_string(Pos.z);
		ImGui::Text(Name.c_str());
	}

	DebugPicking();

	LevelSelect();
}

void MapEditorGUI::DebugPicking()
{
	ImGui::Text("");
	{
		size_t Num = ActorPicker::PickedActors.size();
		std::string Name = "PickedActorsNum : " + std::to_string(Num);
		ImGui::Text(Name.c_str());
	}

	{
		GameEngineActor* Actor = ActorPicker::PickedActor;
		if (nullptr == Actor)
		{
			ImGui::Text("There is no Picked Actor");
		}
		else
		{
			float4 Pos = Actor->GetTransform().GetWorldPosition();
			std::string Name = "PickedActor : " + std::to_string(Pos.x) + " | " + std::to_string(Pos.y) + " | " + std::to_string(Pos.z);
			ImGui::Text(Name.c_str());
		}
	}

	{
		GameEngineActor* Actor = ActorPicker::ClickedActor;
		if (nullptr == Actor)
		{
			ImGui::Text("There is no Clicked Actor");
		}
		else
		{
			float4 Pos = Actor->GetTransform().GetWorldPosition();
			std::string Name = "ClickedActor : " + std::to_string(Pos.x) + " | " + std::to_string(Pos.y) + " | " + std::to_string(Pos.z);
			ImGui::Text(Name.c_str());
		}
	}
}

void MapEditorGUI::LevelSelect()//±è¿¹³ª-¸¸µé¾î ºÃ¾î¿ë..
{
	ImGui::Text("Level Select");

	if (true == ImGui::Button("tmpLevel"))
	{
		GEngine::ChangeLevel("tmpLevel");
	}

	ImGui::SameLine();

	if (true == ImGui::Button("MapEditorLevel"))
	{
		GEngine::ChangeLevel("MapEditorLevel");
	}
}