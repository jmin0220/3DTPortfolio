#include "PreCompile.h"
#include "TestGUI.h"
#include <GameEngineCore/CoreMinimal.h>
#include "StageParentLevel.h"
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

	std::string Name = "Stage : " + _Level->GetNameCopy();
	ImGui::Text(Name.c_str());

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
		float4 LightPos = Light_->GetTransform().GetWorldPosition();
		std::string Name = "LightPos : " + std::to_string(LightPos.x) + " | " + std::to_string(LightPos.y) + " | " + std::to_string(LightPos.z);
		ImGui::Text(Name.c_str());
	}

	{
		float4 LightRot = Light_->GetTransform().GetWorldRotation();
		std::string Name = "LightRot : " + std::to_string(LightRot.x) + " | " + std::to_string(LightRot.y) + " | " + std::to_string(LightRot.z);
		ImGui::Text(Name.c_str());
	}

	{
		std::string Name = "DifPower : " + std::to_string(Light_->GetLightData().DifLightPower);
		ImGui::Text(Name.c_str());
	}

	{
		std::string Name = "SpcPower : " + std::to_string(Light_->GetLightData().SpcLightPower);
		ImGui::Text(Name.c_str());
	}

	{
		std::string Name = "LightPower : " + std::to_string(Light_->GetLightData().SpcPow);
		ImGui::Text(Name.c_str());
	}


	//{
	//	ImGui::Text("LightTargetSizeX : ");
	//	ImGui::SameLine();
	//	float Power = Light_->GetLightData().LightTargetSizeX;
	//	ImGui::SliderFloat("                ", &Power, 0.0f, 10000.0f, "%.1f", 1.0f);
	//	Light_->GetLightData().LightTargetSizeX = Power;
	//}


	//{
	//	ImGui::Text("LightTargetSizeY : ");
	//	ImGui::SameLine();
	//	float Power = Light_->GetLightData().LightTargetSizeY;
	//	ImGui::SliderFloat(" ", &Power, 0.0f, 10000.0f, "%.1f", 1.0f);
	//	Light_->GetLightData().LightTargetSizeY = Power;
	//}


	//{
	//	ImGui::Text("LightNear : ");
	//	ImGui::SameLine();
	//	float Power = Light_->GetLightData().LightNear;
	//	ImGui::SliderFloat("                      ", &Power, 0.0f, 100.0f, "%.1f", 1.0f);
	//	Light_->GetLightData().LightNear = Power;
	//}


	//{
	//	ImGui::Text("LightFar : ");
	//	ImGui::SameLine();
	//	float Power = Light_->GetLightData().LightFar;
	//	ImGui::SliderFloat("                                ", &Power, 0.0f, 10000.0f, "%.1f", 1.0f);
	//	Light_->GetLightData().LightFar = Power;
	//}



	{
		ImGui::Text("DifLightPower : ");
		ImGui::SameLine();
		float Power = Light_->GetLightData().DifLightPower;
		ImGui::SliderFloat("                                       ", &Power, 0.0f, 100.0f, "%.1f",1.0f);
		Light_->GetLightData().DifLightPower = Power;
	}

	{
		ImGui::Text("SpcLightPower : ");
		ImGui::SameLine();
		float Power = Light_->GetLightData().SpcLightPower;
		ImGui::SliderFloat("  ", &Power, 0.0f, 100.0f, "%.1f",1.0f);
		Light_->GetLightData().SpcLightPower = Power;
	}
	
	{
		ImGui::Text("AmbLightPower : ");
		ImGui::SameLine();
		float Power = Light_->GetLightData().AmbLightPower;
		ImGui::SliderFloat("          ", &Power, 0.0f, 100.0f, "%.1f", 1.0f);
		Light_->GetLightData().AmbLightPower = Power;
	}

	{
		ImGui::Text("LightPower : ");
		ImGui::SameLine();
		float Power = Light_->GetLightData().SpcPow;
		ImGui::SliderFloat("   ", &Power, 0.0f, 1000.0f, "%.1f",1.0f);
		Light_->GetLightData().SpcPow = Power;
	}

	{
		ImGui::Text("LightPos : ");
		ImGui::SameLine();
		float4 Pos = Light_->GetTransform().GetWorldPosition();
		float Position[3] = { Pos.x,Pos.y,Pos.z };
		ImGui::SliderFloat3("      ", Position, -500, 500.0f, "%.1f", 1.0f);
		Light_->GetTransform().SetWorldPosition({ Position[0],Position[1],Position[2]});
	}

	{
		ImGui::Text("LightRot : ");
		ImGui::SameLine();
		float4 Rot = Light_->GetTransform().GetWorldRotation();
		float Rotation[3] = { Rot.x,Rot.y,Rot.z};
		ImGui::SliderFloat3("        ", Rotation, 0, 360.0f, "%.1f", 1.0f);
		Light_->GetTransform().SetWorldRotation({ Rotation[0],Rotation[1],Rotation[2]});
	}


	{
		ImGui::Text("LightColor : ");
		ImGui::SameLine();
		float4 Power = Light_->GetLightData().LightColor;
		float Color[4] = { Power.x,Power.y,Power.z,Power.w };
		ImGui::SliderFloat4("                                      ", Color, 0.0f, 1.0f, "%.1f", 1.0f);
		Light_->GetLightData().LightColor.x = Color[0];
		Light_->GetLightData().LightColor.y = Color[1];
		Light_->GetLightData().LightColor.z = Color[2];
		Light_->GetLightData().LightColor.w = Color[3];
	}


	{
		ImGui::Text("AmbientLightColor : ");
		ImGui::SameLine();
		float4 Power = Light_->GetLightData().AmbientLight;
		float Color[4] = { Power.x,Power.y,Power.z,Power.w };
		ImGui::SliderFloat4("                                   ", Color, 0.0f, 1.0f, "%.1f", 1.0f);
		Light_->GetLightData().AmbientLight.x = Color[0];
		Light_->GetLightData().AmbientLight.y = Color[1];
		Light_->GetLightData().AmbientLight.z = Color[2];
		Light_->GetLightData().AmbientLight.w = Color[3];
	}
}


