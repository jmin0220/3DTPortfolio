#include "PreCompile.h"
#include "MapEditorGUI.h"
#include <GameEngineCore/CoreMinimal.h>

#include "ActorPicker.h"
#include "ColorBox.h"

const float SliderFloatMin = -100000;
const float SliderFloatMax = 100000;

static int FileIdx = 0;
static int SpawnedIdx = 0;


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

	{
		float4 Pos = _Level->GetMainCamera()->GetTransform().GetWorldPosition();
		std::string Name = "MainCameraWorldPos : " + std::to_string(Pos.x) + " | " + std::to_string(Pos.y) + " | " + std::to_string(Pos.z);
		ImGui::Text(Name.c_str());
	}
	
	// 로드 버튼 클릭
	OnClickLoad();

	// 로드버튼 밑에 리스트
	ShowLoadedList();

	// 스폰 버튼 클릭
	OnClickSpawn();

	// 스폰한 엑터 리스트
	ShowSpawnedList();

	// 스폰한 엑터에 카메라
	FollowCameraToSpawned(_DeltaTime);

	LoadSave();
	ActorPicking();
}

void MapEditorGUI::ActorPicking()
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
			
			ImGui::InputFloat3("Position", Position);
			ImGui::InputFloat3("Rotation", Rotate);
			ImGui::InputFloat3("Scale", Scale);

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
					CurActor_->GetTransform().SetWorldPosition({ Position[0], Position[1], Position[2] });
					CurActor_->GetTransform().SetWorldRotation({ Rotate[0], Rotate[1], Rotate[2] });
					CurActor_->GetTransform().SetWorldScale({ Scale[0], Scale[1], Scale[2] });
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

	float4 Pos = CurActor_->GetTransform().GetWorldPosition();
	float4 Rot = CurActor_->GetTransform().GetLocalRotation();
	float4 Size = CurActor_->GetTransform().GetWorldScale();

	Position[0] = { Pos.x };
	Position[1] = { Pos.y };
	Position[2] = { Pos.z };

	Rotate[0] = { Rot.x };
	Rotate[1] = { Rot.y };
	Rotate[2] = { Rot.z };

	Scale[0] = { Size.x };
	Scale[1] = { Size.y };
	Scale[2] = { Size.z };


}

void MapEditorGUI::OnClickLoad()
{

	if (true == ImGui::Button("LoadFBXs"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Mesh");


		std::string Path = GameEngineGUI::OpenFolderDlg(GameEngineString::AnsiToUTF8Return("폴더 로드"), Dir.GetFullPath());
		if (0 == Path.compare(""))
		{
			return;
		}
		GameEngineDirectory FolderDir = Path.c_str();


		// 경로 새로받아오기
		Folders_.clear();
		FBXFiles_.clear();
		Folders_ = FolderDir.GetRecursiveAllDirectory();

		for (GameEngineDirectory& Folder : Folders_)
		{
			for (GameEngineFile& File : Folder.GetAllFile(".FBX"))
			{
				FBXFiles_.push_back(File);
			}
		}
	}
}

// 폴더의 FBX파일 리스트 출력
void MapEditorGUI::ShowLoadedList()
{

	ImGui::BeginChild("MeshLoad", ImVec2(200, 100), true);
	if (0 == FBXFiles_.size())
	{
		if (ImGui::Selectable("Null", FileIdx == 0))
		{
			FileIdx = 0;
		}
	}
	else
	{
		for (int i = 0; i < FBXFiles_.size(); ++i)
		{
			std::string FolderName = FBXFiles_[i].GetFileName();
			if (ImGui::Selectable(FolderName.c_str(), FileIdx == i))
			{
				FileIdx = i;
			}
		}
	}
	ImGui::EndChild();
}

// 선택한 FBX 스폰버튼
void MapEditorGUI::OnClickSpawn()
{
	if (true == ImGui::Button("SpawnFBX"))
	{
		if (FBXFiles_.size() == 0)
		{
			return;
		}
		SpawnedObject NewObj;
		std::string Extention = FBXFiles_[FileIdx].GetExtension();
		std::string Name = FBXFiles_[FileIdx].GetFileName();
		NewObj.Name_ = Name.substr(0, Name.size() - Extention.size());

		NewObj.Dir_ = FBXFiles_[FileIdx].GetFullPath();
		NewObj.Actor_ = ConnectedLevel->CreateActor<ColorBox>();

		NewObj.Actor_->GetTransform().SetWorldPosition({ 0, 0, 0 });

		SpawnedObjects_.push_back(NewObj);
		ActorPicker::SelectedActor = NewObj.Actor_;
	}
}

// 스폰된 FBX리스트
void MapEditorGUI::ShowSpawnedList()
{
	ImGui::BeginChild("Spawned", ImVec2(200, 100), true);
	if (0 == SpawnedObjects_.size())
	{
		if (ImGui::Selectable("Null", SpawnedIdx == 0))
		{
			SpawnedIdx = 0;
		}
	}
	else
	{
		for (int i = 0; i < SpawnedObjects_.size(); ++i)
		{
			std::string Name = SpawnedObjects_[i].Name_;

			if (ImGui::Selectable((std::to_string(i) + "_" + Name).c_str(), SpawnedIdx == i))
			{
				CamFollowMode_ = true;
				SpawnedIdx = i;
				ActorPicker::SelectedActor = SpawnedObjects_[i].Actor_;
			}
		}
	}
	ImGui::EndChild();
}

void MapEditorGUI::FollowCameraToSpawned(float _DeltaTime)
{
	if (SpawnedObjects_.size() == 0)
	{
		return;
	}
	
	if (false == CamFollowMode_)
	{
		return;
	}

	// 키보드로 카메라 움직이면 추적모드 취소
	if (true == WASDInputCheck())
	{
		CamFollowMode_ = false;
		return;
	}

	// 한번 클릭했을 때만 쫒아가야 한다
	float4 ObjPos = SpawnedObjects_[SpawnedIdx].Actor_->GetTransform().GetWorldPosition();
	ObjPos += float4(0, 400, -1000);

	float4 CamMovePos = float4::Lerp(ConnectedLevel->GetMainCameraActor()->GetTransform().GetWorldPosition(), ObjPos, _DeltaTime * 25.0f);
	ConnectedLevel->GetMainCameraActor()->GetTransform().SetWorldPosition(CamMovePos);
	ConnectedLevel->GetMainCameraActor()->GetTransform().SetLocalRotation({ 20, 0, 0 });
}

void MapEditorGUI::Load()
{	
}

void MapEditorGUI::Save()
{
}

bool MapEditorGUI::WASDInputCheck()
{
	if (GameEngineInput::GetInst()->IsDown("W"))
	{
		return true;
	}

	if (GameEngineInput::GetInst()->IsDown("A"))
	{
		return true;
	}

	if (GameEngineInput::GetInst()->IsDown("S"))
	{
		return true;
	}

	if (GameEngineInput::GetInst()->IsDown("D"))
	{
		return true;
	}
}