#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
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
	void DebugPicking();
	void LoadSave();
	void UpdateData();
	
	void Load();
	void Save();
	
	bool IsChange_;

	GameEngineLevel* ConnectedLevel;
	GameEngineActor* CurActor_;
	std::vector<GameEngineActor*> ActorVector_;

	float Scale[3];
	float Rotate[3];
	float Position[3];
};

