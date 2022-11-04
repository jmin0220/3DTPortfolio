#pragma once
#include <GameEngineCore/GameEngineGUI.h>

struct SpawnedObject
{
	std::string Name_;
	std::string Dir_;
	GameEngineActor* Actor_;
};

// ���� :
class MapEditorGUI : public GameEngineGUIWindow
{
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

	
	void Load();
	void Save();
	
	bool IsChange_;

	GameEngineLevel* ConnectedLevel;
	GameEngineActor* CurActor_;

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

