#include "PreCompile.h"
#include "MapEditorGUI.h"
#include <GameEngineCore/CoreMinimal.h>

#include "ActorPicker.h"
#include "ColorBox.h"

MapEditorGUI::MapEditorGUI()
	: IsChange_(false)
{
}

MapEditorGUI::~MapEditorGUI()
{
}


void MapEditorGUI::Initialize(GameEngineLevel* _Level)
{
	ConnectedLevel = _Level;
}

void MapEditorGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (GEngine::GetCurrentLevel() != ConnectedLevel)
	{
		Off();
		return;
	}


	if (true == ImGui::Button("FreeCameaOnOff"))
	{
		_Level->GetMainCameraActor()->FreeCameraModeOnOff();
	}

	ImGui::SameLine();
	if (true == ImGui::Button("CollisionDebugSwtich"))
	{
		GEngine::CollisionDebugSwitch();
	}

	ImGui::SameLine();
	//ImGui::InputFloat3;
	if (true == ImGui::Button("CreateBox"))
	{
		GameEngineActor* Box = GEngine::GetCurrentLevel()->CreateActor<ColorBox>();
		Box->GetTransform().SetWorldPosition({ 0, 0, 300 });
		ActorVector_.push_back(Box);

		ActorPicker::SelectedActor = Box;
	}
	{
		float4 Pos = _Level->GetMainCamera()->GetTransform().GetWorldPosition();
		std::string Name = "MainCameraWorldPos : " + std::to_string(Pos.x) + " | " + std::to_string(Pos.y) + " | " + std::to_string(Pos.z);
		ImGui::Text(Name.c_str());
	}
	
	if (true == ImGui::Button("ResLoad"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Mesh");

		std::string Path = GameEngineGUI::OpenFolderDlg(GameEngineString::AnsiToUTF8Return("폴더 매쉬 로드"), Dir.GetFullPath());

		if (false == Path.empty())
		{
			SelectFolderTexture_ = GameEnginePath::GetFileName(Path);

			//Dir.Move(SelectFolderTexture_);
			
			/*GameEngineDirectory MeshDir = Dir;
			MeshDir.Move(SelectFolderTexture_);
			GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(MeshDir.PlusFilePath(SelectFolderTexture_ + ".FBX"));*/
			
			//GameEngineFBXMesh::Load(MeshDir.PlusFilePath("Character.FBX"))
			// 매쉬 로드 후 생성
			// json 파일로 출력 save, Load
		}
	}

	ImGui::BeginChild("MeshLoad", ImVec2(200, 100), true);
	ImGui::EndChild();

	if (false == SelectFolderTexture_.empty())
	{

	}

	ImGui::SameLine();

	static int Num = 0;
	ImGui::BeginChild("MeshList", ImVec2(200, 100), true);
	if (0 == ActorVector_.size())
	{
		if (ImGui::Selectable("Null", Num == 0))
		{
			Num = 0;
		}
	}
	else
	{
		for (int i = 0; i < ActorVector_.size(); ++i)
		{
			std::string Temp = "CreateBox";
			
			if (ImGui::Selectable((Temp + std::to_string(i)).c_str(), Num == i))
			{
				Num = i;
				ActorPicker::SelectedActor = ActorVector_[i];
			}
		}
	}
	ImGui::EndChild();

	LoadSave();
	DebugPicking();

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
		// 현재 마우스 위치의 액터 = 클릭하면 선택될 예정의 액터
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

	{
		// 클릭해서 현재 선택된 액터
		if (CurActor_ != ActorPicker::SelectedActor)
		{
			CurActor_ = ActorPicker::SelectedActor;

			// TODO::Root를 수정하는 경우에만 유효
			UpdateData();
		}
		// 같은 액터인 경우
		//else
		//{
		//	// if(Scale != size)
		//	//  scale = size;
		//}

		if (nullptr == CurActor_)
		{
			ImGui::Text("There is no Selected Actor");
		}
		else
		{
			UpdateData();

			std::string Name = "SelectedActor : ";
			ImGui::Text(Name.c_str());
			ImGui::InputFloat3("Scale", Scale);
			ImGui::InputFloat3("Rotation", Rotate);
			ImGui::InputFloat3("Position", Position);

			if (false == IsChange_)
			{
				if (true == ImGui::Button("ChangeModeOn"))
				{
					IsChange_ = !IsChange_;
				}
			}
			else
			{
				if (true == ImGui::Button("Setting"))
				{
					CurActor_->GetTransform().SetWorldScale({ Scale[0], Scale[1], Scale[2] });
					CurActor_->GetTransform().SetWorldRotation({ Rotate[0], Rotate[1], Rotate[2] });
					CurActor_->GetTransform().SetWorldPosition({ Position[0], Position[1], Position[2] });
					IsChange_ = false;
				}
			}
		}
	}
}

void MapEditorGUI::LoadSave()
{
	if (true == ImGui::Button("Load"))
	{
		Load();
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Save"))
	{
		Save();
	}
}

void MapEditorGUI::UpdateData()
{
	if (nullptr == CurActor_ || true == IsChange_)
	{
		return;
	}

	float4 Size = CurActor_->GetTransform().GetWorldScale();
	float4 Rot = CurActor_->GetTransform().GetLocalRotation();
	float4 Pos = CurActor_->GetTransform().GetWorldPosition();

	Scale[0] = { Size.x };
	Scale[1] = { Size.y };
	Scale[2] = { Size.z };

	Rotate[0] = { Rot.x };
	Rotate[1] = { Rot.y };
	Rotate[2] = { Rot.z };

	Position[0] = { Pos.x };
	Position[1] = { Pos.y };
	Position[2] = { Pos.z };
}

void MapEditorGUI::Load()
{	
}

void MapEditorGUI::Save()
{
}
