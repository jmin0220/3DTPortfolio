#include "PreCompile.h"
#include "MapEditorGUI.h"
#include <GameEngineCore/CoreMinimal.h>
#include <iostream>
#include <fstream>
#include <GameEngineCore/ThirdParty/inc/json.h>

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

	//// Ű�� ���� ��������
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
	
	// �ε� ��ư Ŭ��
	OnClickLoad();

	// �ε��ư �ؿ� ����Ʈ
	ShowLoadedList();

	// ���� ��ư Ŭ��
	OnClickSpawn();

	// ������ ���� ����Ʈ
	ShowSpawnedList();

	// ������ ���Ϳ� ī�޶�
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
		// ���� ���콺 ��ġ�� ���� = Ŭ���ϸ� ���õ� ������ ����
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
		// Ŭ���ؼ� ���� ���õ� ����
		if (CurActor_ != ActorPicker::SelectedActor)
		{
			CurActor_ = ActorPicker::SelectedActor;

			// TODO::Root�� �����ϴ� ��쿡�� ��ȿ
			UpdateData();
		}
		// ���� ������ ���
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
		jsonRead();
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Save"))
	{
		Save();
		jsonWrite();
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


		std::string Path = GameEngineGUI::OpenFolderDlg(GameEngineString::AnsiToUTF8Return("���� �ε�"), Dir.GetFullPath());
		if (0 == Path.compare(""))
		{
			return;
		}
		GameEngineDirectory FolderDir = Path.c_str();


		// ��� ���ι޾ƿ���
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

// ������ FBX���� ����Ʈ ���
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

// ������ FBX ������ư
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

// ������ FBX����Ʈ
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

	// Ű����� ī�޶� �����̸� ������� ���
	if (true == WASDInputCheck())
	{
		CamFollowMode_ = false;
		return;
	}

	// �ѹ� Ŭ������ ���� �i�ư��� �Ѵ�
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

// JSON���� �ڵ�
using namespace std;
// MeshDataSave
void MapEditorGUI::jsonWrite() {
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("Resources");
	Dir.Move("Resources");
	Dir.Move("Mesh");
	
	ofstream json_file;
	json_file.open(Dir.GetFullPath() + "\\jsontest.json");

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
		// ���ĺ� ������ write �ȴ�.
		//writer->write(MeshData, &cout);
		writer->write(Object, &json_file);
		cout << endl;  // add lf and flush
	json_file.close();
}

// MeshDataLoad
void MapEditorGUI::jsonRead() {
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("Resources");
	Dir.Move("Resources");
	Dir.Move("Mesh");

	ifstream json_dir(Dir.GetFullPath() + "\\jsontest.json");
	
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

		/*GameEngineDebug::OutPutString("Name: " + Mesh["Name"].toStyledString());
		GameEngineDebug::OutPutString("Pos: " + Mesh["Transform"]["Pos"][0].toStyledString());
		GameEngineDebug::OutPutString("Size: " + Mesh["Transform"]["Size"].toStyledString());
		GameEngineDebug::OutPutString("Rot: " + Mesh["Transform"]["Rot"].toStyledString());*/

		float4 Pos = { Mesh["Transform"]["Pos"][0].asFloat() , Mesh["Transform"]["Pos"][1].asFloat() , Mesh["Transform"]["Pos"][2].asFloat(), Mesh["Transform"]["Pos"][3].asFloat() };
		float4 Size = { Mesh["Transform"]["Size"][0].asFloat() , Mesh["Transform"]["Size"][1].asFloat() , Mesh["Transform"]["Size"][2].asFloat(), Mesh["Transform"]["Size"][3].asFloat() };
		float4 Rot = { Mesh["Transform"]["Rot"][0].asFloat() , Mesh["Transform"]["Rot"][1].asFloat() , Mesh["Transform"]["Rot"][2].asFloat(), Mesh["Transform"]["Rot"][3].asFloat() };
		
		SpawnedObject NewObj;
		NewObj.Name_ = Mesh["Name"].toStyledString();

		//NewObj.Dir_ = FBXFiles_[FileIdx].GetFullPath();
		NewObj.Actor_ = ConnectedLevel->CreateActor<ColorBox>();

		NewObj.Actor_->GetTransform().SetWorldPosition(Pos);
		NewObj.Actor_->GetTransform().SetWorldScale(Size);
		NewObj.Actor_->GetTransform().SetLocalRotation(Rot);

		SpawnedObjects_.push_back(NewObj);
		ActorPicker::SelectedActor = NewObj.Actor_;

		j++;
	}
}