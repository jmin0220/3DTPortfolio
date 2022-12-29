#include "PreCompile.h"
#include "GameManagerGUI.h"
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCore.h>
#include <math.h>

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

	// 카메라 월드 위치
	ImGui::SameLine();
	{

		float4 Pos = GEngine::GetCurrentLevel()->GetMainCameraActorTransform().GetWorldPosition();

		PrevValidPos_;
		if (true == isnan(Pos.x))
		{
			int a = 0;
		}

		PrevValidPos_ = Pos;
		std::string Name = "MainCameraActorPos : " + std::to_string(Pos.x) + " : " + std::to_string(Pos.y) + " : " + std::to_string(Pos.z);
		ImGui::Text(Name.c_str());
	}
	ImGui::SameLine();
	{
		float4 Rot = GEngine::GetCurrentLevel()->GetMainCameraActorTransform().GetWorldRotation();
		std::string Name = "MainCameraActorRot : " + std::to_string(Rot.x) + " : " + std::to_string(Rot.y) + " : " + std::to_string(Rot.z);
		ImGui::Text(Name.c_str());
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