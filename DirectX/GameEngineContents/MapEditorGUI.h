#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include "PickableActor.h"

struct SpawnedObject
{
	std::string Name_;
	std::string Dir_;
	std::weak_ptr<PickableActor> Actor_;
};

enum class MeshEnum
{
	START,	// 가장 시작
	// STAGE01
	// STAGE02
	JumpClubMap,
	// STAGE03
	// STAGE04
	HexAGoneMap,
	HexTile,
	HexProPeller,
	JumboTronProPeller,
	JumboTron1,
	JumboTron2,
	JumboTron3,
	JumboTron4,
	JumboTron5,
	JumboTron6,
	JumboTron7,
	// STAGE05
	HoopsBackGround,
	HoopsFloor,
	HoopsObjectPlatform,
	HoopsObjectWall,
	WoodPlank,
	// TEST
	Rainbow,
	TestMap,
	DoorDashCollisionMesh,
	DoodrDashEnv,
	DoorBlock,
	MovingBar,
	Chevron,
	// COLLISION
	Col_StartPos,
	Col_CheckPoint,
	Col_Trigger,
	Col_Goal,
	END, // 가장 마지막
};

// 설명 :
class MapEditorGUI : public GameEngineGUIWindow
{
public:
	void ReleaseResources()
	{
		SpawnedObjects_.clear();
	}

public:
	// constrcuter destructer
	MapEditorGUI();
	~MapEditorGUI();

	// delete Function
	MapEditorGUI(const MapEditorGUI& _Other) = delete;
	MapEditorGUI(MapEditorGUI&& _Other) noexcept = delete;
	MapEditorGUI& operator=(const MapEditorGUI& _Other) = delete;
	MapEditorGUI& operator=(MapEditorGUI&& _Other) noexcept = delete;

protected:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

private:
	void ActorPicking();
	void LoadSave();
	void UpdateData();

	void OnClickLoad();
	void ShowLoadedList();
	void OnClickSpawn();
	void ShowSpawnedList();
	void FollowCameraToSpawned(float _DeltaTime);
	bool WASDInputCheck();
	
	void Load();
	void Save();
	
	void LoadData(const std::string& _FilePath, const std::string& _FileName);
	void SaveData(const std::string& _FilePath, const std::string& _FileName);
	void CreateFBXMesh();

	bool IsChange_;
	bool CamFollowMode_;
	bool IsFileExist_;

	GameEngineLevel* ConnectedLevel;
	std::weak_ptr<GameEngineActor> CurActor_;

	SpawnedObject NewObj;
	MeshEnum CurMesh;

	std::string SelectFolderTexture_;

	float Position[3];
	float Rotate[3];
	float Scale[3];

	// ResLoad클릭시 폴더리스트
	std::vector<GameEngineDirectory> Folders_;

	// 폴더안 FBX들
	std::vector<GameEngineFile> FBXFiles_;

	// 소환 된 액터
	std::vector<SpawnedObject> SpawnedObjects_;
};

