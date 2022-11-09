#include "PreCompile.h"
#include "MapEditorGUI.h"
#include <GameEngineCore/CoreMinimal.h>
#include <iostream>
#include <fstream>
#include <GameEngineCore/ThirdParty/inc/json.h>
#include <GameEngineBase/magic_enum.hpp>

#include "ActorPicker.h"
#include "ColorBox.h"
#include "TestRainBow.h"
#include "AxisActor.h"
#include "TestActor_Character.h"

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

	//// 키와 값을 가져오기
	//for (auto const& tmpactor : ActorMap_)
	//{
	//	std::string a = tmpactor.first;
	//	GameEngineActor* b = tmpactor.second;
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
	
	// 로드 버튼 클릭
	OnClickLoad();

	// 로드버튼 밑에 리스트
	ShowLoadedList();

	// 스폰 버튼 클릭
	OnClickSpawn();

	// 스폰한 엑터에 카메라
	FollowCameraToSpawned(_DeltaTime);

	// 스폰한 엑터 리스트
	ShowSpawnedList();


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

			//회전 슬라이더 추가 * 실시간 회전
			{
				ImGui::SliderFloat3("RotRealTime", Rotate, -360.0f, 360.0f);
				CurActor_->GetTransform().SetWorldRotation({ Rotate[0], Rotate[1], Rotate[2] });
			}

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
		Dir.MoveParentToExitsChildDirectory(DIR_RESOURCES);
		Dir.Move(DIR_RESOURCES);
		Dir.Move(DIR_LEVELS);
		Dir.Move(DIR_TESTLEVEL);
		//Dir.Move(DIR_MESH);


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
		
		//NewObj.Actor_ = ConnectedLevel->CreateActor<ColorBox>();

		//CurMesh = MeshEnum::Rainbow;
		//std::string_view Meshname = magic_enum::enum_name(CurMesh);
		//if (Meshname == NewObj.Name_)
		//{

		//	int a = 0;
		//}
		
		std::map<std::string, MeshEnum> MeshEnumMap_;
		MeshEnum tmpEnum = MeshEnum::START;

		for (int i = 0; i < static_cast<int>(MeshEnum::END); i++)
		{
			std::string tmp = magic_enum::enum_name(tmpEnum).data();
			MeshEnumMap_[tmp] = (MeshEnum)i;
			tmpEnum = (MeshEnum)((int)tmpEnum + 1);
		}

		switch ((*MeshEnumMap_.find(NewObj.Name_)).second)
		{
		case MeshEnum::axis:
		{
			NewObj.Actor_ = ConnectedLevel->CreateActor<AxisActor>();
		}
			break;
		case MeshEnum::Character:
		{
			NewObj.Actor_ = ConnectedLevel->CreateActor<TestActor_Character>();
		}
			break;
		case MeshEnum::Rainbow:
		{
			NewObj.Actor_ = ConnectedLevel->CreateActor<TestRainBow>();
		}
			break;
		case MeshEnum::TestMap:
		{
			int a = 0;
		}
			break;
		default:
		{
			int a = 0;
		}
			break;
		}

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

	ImGui::SameLine();
	bool PushRemove = ImGui::Button("Remove");
	if (true == PushRemove && 0 != SpawnedObjects_.size())
	{
		SpawnedObjects_[SpawnedIdx].Actor_->Death();
		SpawnedObjects_.erase(SpawnedObjects_.begin() + SpawnedIdx);
		
		if (SpawnedIdx != 0)
		{
			SpawnedIdx--;
		}
	}
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
	GameEngineDirectory LoadDir;
	LoadDir.MoveParentToExitsChildDirectory(DIR_RESOURCES);
	LoadDir.Move(DIR_RESOURCES);
	LoadDir.Move(DIR_MESH);
	
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GameEngineWindow::GetHWND();
	wchar_t szName[256] = {};
	std::string LoadPath(LoadDir.GetFullPath());
	ofn.lpstrFile = (LPWSTR)szName;
	ofn.lpstrInitialDir = (LPCWSTR)LoadPath.c_str();

	ofn.nMaxFile = sizeof(szName);
	//ofn.lpstrFilter = "ALL\0*.*\0json\0*.json"; 
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (TRUE == GetSaveFileName(&ofn))
	{
		std::filesystem::path p(ofn.lpstrFile);
		LoadData(LoadPath, p.filename().string());
	}
}

void MapEditorGUI::Save()
{
	GameEngineDirectory SaveDir;
	SaveDir.MoveParentToExitsChildDirectory(DIR_RESOURCES);
	SaveDir.Move(DIR_RESOURCES);
	SaveDir.Move(DIR_MESH);
	
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GameEngineWindow::GetHWND();
	wchar_t szName[256] = {};
	std::string SavePath(SaveDir.GetFullPath());
	ofn.lpstrFile = (LPWSTR)szName;
	ofn.lpstrInitialDir = (LPCWSTR)SavePath.c_str();

	ofn.nMaxFile = sizeof(szName);
	//ofn.lpstrFilter = "ALL\0*.*\0json\0*.json";
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (TRUE == GetSaveFileName(&ofn))
	{
		std::filesystem::path p(ofn.lpstrFile);
		SaveData(SavePath, p.filename().string() + ".json");
	}
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

	return false;
}

// JSON생성 코드
using namespace std;
// MeshDataSave
void MapEditorGUI::SaveData(const std::string& _FilePath, const std::string& _FileName)
{
	ofstream json_file;
	json_file.open(_FilePath + "\\" + _FileName);

	Json::Value Object;

	for (auto& Mesh : SpawnedObjects_)
	{
		Json::Value MeshData;
		MeshData["Mesh"]["Name"] = Mesh.Name_;

		Json::Value PosData;
		PosData.append(Mesh.Actor_->GetTransform().GetWorldPosition().x);
		PosData.append(Mesh.Actor_->GetTransform().GetWorldPosition().y);
		PosData.append(Mesh.Actor_->GetTransform().GetWorldPosition().z);

		Json::Value SizeData;
		SizeData.append(Mesh.Actor_->GetTransform().GetWorldScale().x);
		SizeData.append(Mesh.Actor_->GetTransform().GetWorldScale().y);
		SizeData.append(Mesh.Actor_->GetTransform().GetWorldScale().z);

		Json::Value RotData;
		RotData.append(Mesh.Actor_->GetTransform().GetLocalRotation().x);
		RotData.append(Mesh.Actor_->GetTransform().GetLocalRotation().y);
		RotData.append(Mesh.Actor_->GetTransform().GetLocalRotation().z);

		Json::Value NameTransform;
		NameTransform["Pos"] = PosData;
		NameTransform["Size"] = SizeData;
		NameTransform["Rot"] = RotData;

		MeshData["Mesh"]["Transform"] = NameTransform;


		static int j = 0;
		Object["Object" + std::to_string(j++)] = MeshData;

	}
		Json::StreamWriterBuilder builder;
		builder["commentStyle"] = "None";
		builder["indentation"] = "    ";  // Tab

		unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
		// 알파벳 순으로 write 된다.
		//writer->write(MeshData, &cout);
		writer->write(Object, &json_file);
		cout << endl;  // add lf and flush
	json_file.close();
}

// MeshDataLoad
void MapEditorGUI::LoadData(const std::string& _FilePath, const std::string& _FileName)
{
	ifstream json_dir(_FilePath + "\\" + _FileName);
	
	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	Json::Value value;

	JSONCPP_STRING errs;
	bool ok = parseFromStream(builder, json_dir, &value, &errs);
	if (ok == false)
	{
		return;
	}
	
	int j = 0;
	while (Json::nullValue != value["Object" + std::to_string(j)])
	{
		Json::Value Mesh = value["Object" + std::to_string(j)]["Mesh"];

		float4 Pos = { Mesh["Transform"]["Pos"][0].asFloat() , Mesh["Transform"]["Pos"][1].asFloat() , Mesh["Transform"]["Pos"][2].asFloat(), Mesh["Transform"]["Pos"][3].asFloat() };
		float4 Size = { Mesh["Transform"]["Size"][0].asFloat() , Mesh["Transform"]["Size"][1].asFloat() , Mesh["Transform"]["Size"][2].asFloat(), Mesh["Transform"]["Size"][3].asFloat() };
		float4 Rot = { Mesh["Transform"]["Rot"][0].asFloat() , Mesh["Transform"]["Rot"][1].asFloat() , Mesh["Transform"]["Rot"][2].asFloat(), Mesh["Transform"]["Rot"][3].asFloat() };
		
		SpawnedObject NewObj;
		NewObj.Name_ = Mesh["Name"].asCString();

		//NewObj.Dir_ = FBXFiles_[FileIdx].GetFullPath();
		//NewObj.Actor_ = ConnectedLevel->CreateActor<ColorBox>();

		std::map<std::string, MeshEnum> MeshEnumMap_;
		MeshEnum tmpEnum = MeshEnum::START;

		for (int i = 0; i < static_cast<int>(MeshEnum::END); i++)
		{
			std::string tmp = magic_enum::enum_name(tmpEnum).data();
			MeshEnumMap_[tmp] = (MeshEnum)i;
			tmpEnum = (MeshEnum)((int)tmpEnum + 1);
		}

		switch ((*MeshEnumMap_.find(NewObj.Name_)).second)
		{
		case MeshEnum::axis:
		{
			NewObj.Actor_ = ConnectedLevel->CreateActor<AxisActor>();
		}
		break;
		case MeshEnum::Character:
		{
			NewObj.Actor_ = ConnectedLevel->CreateActor<TestActor_Character>();
		}
		break;
		case MeshEnum::Rainbow:
		{
			NewObj.Actor_ = ConnectedLevel->CreateActor<TestRainBow>();
		}
		break;
		case MeshEnum::TestMap:
		{
			int a = 0;
		}
		break;
		default:
		{
			int a = 0;
		}
		break;
		}

		NewObj.Actor_->GetTransform().SetWorldPosition(Pos);
		NewObj.Actor_->GetTransform().SetWorldScale(Size);
		NewObj.Actor_->GetTransform().SetLocalRotation(Rot);

		SpawnedObjects_.push_back(NewObj);
		ActorPicker::SelectedActor = NewObj.Actor_;

		j++;
	}
}