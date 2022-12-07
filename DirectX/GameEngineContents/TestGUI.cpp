#include "PreCompile.h"
#include "TestGUI.h"
#include <GameEngineCore/CoreMinimal.h>
#include <iostream>


TestGUI::TestGUI()
{

}

TestGUI::~TestGUI()
{
}


void TestGUI::Initialize(GameEngineLevel* _Level)
{
	ConnectedLevel = _Level;
}

void TestGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (GEngine::GetCurrentLevel() != ConnectedLevel)
	{
		Off();
		return;
	}

	//// 키와 값을 가져오기
	//for (auto const& tmpactor : ActorMap_)
	//{
	//	std::string a = tmpactor.first;
	//	std::shared_ptr<GameEngineActor> b = tmpactor.second;
	//}

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


	float Data_[4];
	Data_[0]= Obj->GetData().Data_.x;
	Data_[1] = Obj->GetData().Data_.y;
	Data_[2] = Obj->GetData().Data_.z;
	Data_[3] = Obj->GetData().Data_.w;


	ImGui::SliderFloat4("Data", Data_,0.0f,30.0f);
	Obj->SetDataPosX(Data_[0]);
	Obj->SetDataPosY(Data_[1]);
	Obj->SetDataScaleX(Data_[2]);
	Obj->SetDataScaleY(Data_[3]);
	//ImGui::SliderFloat4("Data :  ", Data_, 0.0f, 1.0f, "%.3f", 0.1f);

}


