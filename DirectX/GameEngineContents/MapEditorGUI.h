#pragma once
#include <GameEngineCore/GameEngineGUI.h>

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
	void DebugPicking();

	GameEngineLevel* ConnectedLevel;
	GameEngineActor* CurActor_;

	float Scale[3];
	float Rotate[3];
	float Position[3];

	// 현재 액터
};

