#pragma once
#include <GameEngineCore/GameEngineGUI.h>

struct SpawnedObject
{
	std::string Name_;
	std::string Dir_;
	GameEngineActor* Actor_;
};

// 설명 :
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
	
	void Load();
	void Save();
	
	bool IsChange_;

	GameEngineLevel* ConnectedLevel;
	GameEngineActor* CurActor_;

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

