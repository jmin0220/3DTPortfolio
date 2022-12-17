#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class GameServerGUI : public GameEngineGUIWindow
{
public:
	static bool GameStart_;

public:
	// constrcuter destructer
	GameServerGUI();
	~GameServerGUI();

	// delete Function
	GameServerGUI(const GameServerGUI& _Other) = delete;
	GameServerGUI(GameServerGUI&& _Other) noexcept = delete;
	GameServerGUI& operator=(const GameServerGUI& _Other) = delete;
	GameServerGUI& operator=(GameServerGUI&& _Other) noexcept = delete;

protected:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

private:
	void LobbyGUI();
	void InGameGUI();

private:
	class GameEngineLevel* LobbyLevel_;

};

