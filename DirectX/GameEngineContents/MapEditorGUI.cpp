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
static int CollisionIdx = 0;


MapEditorGUI::MapEditorGUI()
	: IsChange_(false)
	, IsFileExist_(false)
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
		std::weak_ptr<GameEngineActor> Actor = ActorPicker::PickedActor;
		if (nullptr == Actor.lock())
		{
			ImGui::Text("There is no Picked Actor");
		}
		else
		{
			float4 Pos = Actor.lock()->GetTransform().GetWorldPosition();
			std::string Name = "PickedActor : " + std::to_string(Pos.x) + " | " + std::to_string(Pos.y) + " | " + std::to_string(Pos.z);
			ImGui::Text(Name.c_str());
		}
	}

	{
		std::weak_ptr<GameEngineActor> Actor = ActorPicker::ClickedActor;
		if (nullptr == Actor.lock())
		{
			ImGui::Text("There is no Clicked Actor");
		}
		else
		{
			float4 Pos = Actor.lock()->GetTransform().GetWorldPosition();
			std::string Name = "ClickedActor : " + std::to_string(Pos.x) + " | " + std::to_string(Pos.y) + " | " + std::to_string(Pos.z);
			ImGui::Text(Name.c_str());
		}
	}

	{
		// 클릭해서 현재 선택된 액터
		if (nullptr != ActorPicker::SelectedActor)
		{
			CurActor_ = ActorPicker::SelectedActor;

			// TODO::Root를 수정하는 경우에만 유효
			UpdateData();
		}
		else
		{
			CurActor_.reset();
		}




		if (nullptr == CurActor_.lock())
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
				CurActor_.lock()->GetTransform().SetWorldRotation({ Rotate[0], Rotate[1], Rotate[2] });
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
					CurActor_.lock()->GetTransform().SetWorldPosition({Position[0], Position[1], Position[2]});
					CurActor_.lock()->GetTransform().SetWorldRotation({ Rotate[0], Rotate[1], Rotate[2] });
					CurActor_.lock()->GetTransform().SetWorldScale({ Scale[0], Scale[1], Scale[2] });
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
	if (nullptr == CurActor_.lock() || true == IsChange_)
	{
		return;
	}

	float4 Pos = CurActor_.lock()->GetTransform().GetWorldPosition();
	float4 Rot = CurActor_.lock()->GetTransform().GetLocalRotation();
	float4 Size = CurActor_.lock()->GetTransform().GetWorldScale();

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
		IsFileExist_ = false;
		
		if (ImGui::Selectable("Null", FileIdx == 0))
		{
			FileIdx = 0;
		}
	}
	else
	{
		IsFileExist_ = true;

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

	if (true == IsFileExist_)
	{
		ImGui::SameLine();

		ImGui::BeginChild("CollisionList", ImVec2(200, 100), true);
		MeshEnum ColEnum = MeshEnum::Col_StartPos;
		for (int i = static_cast<int>(MeshEnum::Col_StartPos); i < static_cast<int>(MeshEnum::END); i++)
		{
			std::string CollisionTypeName = magic_enum::enum_name(ColEnum).data();
			if (ImGui::Selectable(CollisionTypeName.c_str(), CollisionIdx == i))
			{
				CollisionIdx = i;
			}
			ColEnum = (MeshEnum)((int)ColEnum + 1);
		}
		ImGui::EndChild();
	}
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
		//SpawnedObject NewObj;
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

		// 1. PickableActor 소환 후
		NewObj.Actor_ = ConnectedLevel->CreateActor<PickableActor>();
		
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
		case MeshEnum::START:
		{
			int a = 0;
			break;
		}
		case MeshEnum::JumpClubMap:
		{
			NewObj.Actor_.lock()->SetStaticMesh("JumpClubMap.FBX");
			break;
		}
		case MeshEnum::HexAGoneMap:
		{
			NewObj.Actor_.lock()->SetStaticMesh("HexAGoneMap.FBX");
			break;
		}
		case MeshEnum::HexTile:
		{
			NewObj.Actor_.lock()->SetStaticMesh("HexTile.FBX");
			break;
		}
		case MeshEnum::Rainbow:
		{
			// 2. 메쉬 세팅해준다
			NewObj.Actor_.lock()->SetStaticMesh("Rainbow.FBX");
			break;
		}
		case MeshEnum::TestMap:
		{
			NewObj.Actor_.lock()->SetStaticMesh("TestMap.FBX");
			break;
		}
		case MeshEnum::END:
		{
			int a = 0;
			break;
		}
		default:
		{
			int a = 0;
			break;
		}
		}
		
		NewObj.Actor_.lock()->GetTransform().SetWorldPosition({ 0, 0, 0 });

		SpawnedObjects_.push_back(NewObj);
		ActorPicker::SelectedActor = NewObj.Actor_.lock();
	}

	if (true == IsFileExist_)
	{
		ImGui::SameLine();

		if (true == ImGui::Button("SpawnCollision"))
		{
			MeshEnum ColEnum = (MeshEnum)((int)CollisionIdx);
			NewObj.Name_ = magic_enum::enum_name(ColEnum).data();

			NewObj.Actor_ = ConnectedLevel->CreateActor<PickableActor>();

			std::map<std::string, MeshEnum> CollisionEnumMap_;
			MeshEnum tmpEnum = MeshEnum::Col_StartPos;

			for (int i = static_cast<int>(MeshEnum::Col_StartPos); i < static_cast<int>(MeshEnum::END); i++)
			{
				std::string tmp = magic_enum::enum_name(tmpEnum).data();
				CollisionEnumMap_[tmp] = (MeshEnum)i;
				tmpEnum = (MeshEnum)((int)tmpEnum + 1);
			}

			switch ((*CollisionEnumMap_.find(NewObj.Name_)).second)
			{
			case MeshEnum::Col_StartPos:
				NewObj.Actor_.lock()->SetCollisionOnly(float4(1, 1, 1));
				break;
			case MeshEnum::Col_Goal:
				NewObj.Actor_.lock()->SetCollisionOnly(float4(1, 1, 1));
				break;
			default:
				break;
			}

			NewObj.Actor_.lock()->GetTransform().SetWorldPosition({ 0, 0, 0 });

			SpawnedObjects_.push_back(NewObj);
			ActorPicker::SelectedActor = NewObj.Actor_.lock();
		}
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
				ActorPicker::SelectedActor = SpawnedObjects_[i].Actor_.lock();
			}
		}
	}
	ImGui::EndChild();

	ImGui::SameLine();
	bool PushRemove = ImGui::Button("Remove");
	if (true == PushRemove && 0 != SpawnedObjects_.size())
	{
		SpawnedObjects_[SpawnedIdx].Actor_.lock()->Death();
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
	float4 ObjPos = SpawnedObjects_[SpawnedIdx].Actor_.lock()->GetTransform().GetWorldPosition();
	ObjPos += float4(0, 200, -500);

	float4 CamMovePos = float4::Lerp(ConnectedLevel->GetMainCameraActor()->GetTransform().GetWorldPosition(), ObjPos, _DeltaTime * 25.0f);
	ConnectedLevel->GetMainCameraActor()->GetTransform().SetWorldPosition(CamMovePos);
	ConnectedLevel->GetMainCameraActor()->GetTransform().SetLocalRotation({ 20, 0, 0 });
}

void MapEditorGUI::Load()
{	
	GameEngineDirectory LoadDir;
	LoadDir.MoveParentToExitsChildDirectory(DIR_RESOURCES);
	LoadDir.Move(DIR_RESOURCES);
	LoadDir.Move(DIR_JSONTEST);
	
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GameEngineWindow::GetHWND();
	wchar_t szName[256] = {};
	std::string LoadPath(LoadDir.GetFullPath());

#if _DEBUG
	ofn.lpstrFile = (LPSTR)szName;
	ofn.lpstrInitialDir = (LPCSTR)LoadPath.c_str();
#else
	ofn.lpstrFile = (LPWSTR)szName;
	ofn.lpstrInitialDir = (LPCWSTR)LoadPath.c_str();
#endif

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
	SaveDir.Move(DIR_JSONTEST);
	
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GameEngineWindow::GetHWND();
	wchar_t szName[256] = {};
	std::string SavePath(SaveDir.GetFullPath());

#if _DEBUG
	ofn.lpstrFile = (LPSTR)szName;
	ofn.lpstrInitialDir = (LPCSTR)SavePath.c_str();
#else
	ofn.lpstrFile = (LPWSTR)szName;
	ofn.lpstrInitialDir = (LPCWSTR)SavePath.c_str();
#endif

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
		PosData.append(Mesh.Actor_.lock()->GetTransform().GetWorldPosition().x);
		PosData.append(Mesh.Actor_.lock()->GetTransform().GetWorldPosition().y);
		PosData.append(Mesh.Actor_.lock()->GetTransform().GetWorldPosition().z);

		Json::Value SizeData;
		SizeData.append(Mesh.Actor_.lock()->GetTransform().GetWorldScale().x);
		SizeData.append(Mesh.Actor_.lock()->GetTransform().GetWorldScale().y);
		SizeData.append(Mesh.Actor_.lock()->GetTransform().GetWorldScale().z);

		Json::Value RotData;
		RotData.append(Mesh.Actor_.lock()->GetTransform().GetLocalRotation().x);
		RotData.append(Mesh.Actor_.lock()->GetTransform().GetLocalRotation().y);
		RotData.append(Mesh.Actor_.lock()->GetTransform().GetLocalRotation().z);

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
		NewObj.Actor_ = ConnectedLevel->CreateActor<PickableActor>();

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
		case MeshEnum::START:
		{
			int a = 0;
			break;
		}
		case MeshEnum::JumpClubMap:
		{
			NewObj.Actor_.lock()->SetStaticMesh("JumpClubMap.FBX");
			break;
		}
		case MeshEnum::HexAGoneMap:
		{
			NewObj.Actor_.lock()->SetStaticMesh("HexAGoneMap.FBX");
			break;
		}
		case MeshEnum::HexTile:
		{
			NewObj.Actor_.lock()->SetStaticMesh("HexTile.FBX");
			break;
		}
		case MeshEnum::Rainbow:
		{
			// 2. 메쉬 세팅해준다
			NewObj.Actor_.lock()->SetStaticMesh("Rainbow.FBX");
			break;
		}
		case MeshEnum::TestMap:
		{
			NewObj.Actor_.lock()->SetStaticMesh("TestMap.FBX");
			break;
		}
		case MeshEnum::Col_StartPos:
		{
			NewObj.Actor_.lock()->SetCollisionOnly(Size);
			break;
		}
		case MeshEnum::Col_Goal:
		{
			NewObj.Actor_.lock()->SetCollisionOnly(Size);
			break;
		}
		case MeshEnum::END:
		{
			int a = 0;
			break;
		}
		default:
		{
			int a = 0;
			break;
		}
		}

		NewObj.Actor_.lock()->GetTransform().SetWorldPosition(Pos);
		NewObj.Actor_.lock()->GetTransform().SetWorldScale(Size);
		NewObj.Actor_.lock()->GetTransform().SetLocalRotation(Rot);

		SpawnedObjects_.push_back(NewObj);
		ActorPicker::SelectedActor = NewObj.Actor_.lock();

		j++;
	}
}
