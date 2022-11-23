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
	START,	// ���� ����
	// STAGE01
	// STAGE02
	JumpClubMap,
	// STAGE03
	// STAGE04
	HexAGoneMap,
	HexTile,
	// TEST
	Rainbow,
	TestMap,
	DoorDashCollisionMesh,
	DoodrDashEnv,
	DoorBlock,
	// COLLISION
	Col_StartPos,
	Col_Goal,
	END, // ���� ������
};

// ���� :
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

	// ResLoadŬ���� ��������Ʈ
	std::vector<GameEngineDirectory> Folders_;

	// ������ FBX��
	std::vector<GameEngineFile> FBXFiles_;

	// ��ȯ �� ����
	std::vector<SpawnedObject> SpawnedObjects_;
};

