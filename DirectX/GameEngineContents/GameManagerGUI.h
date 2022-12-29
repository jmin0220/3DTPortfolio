#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class GameManagerGUI : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	GameManagerGUI();
	~GameManagerGUI();

	// delete Function
	GameManagerGUI(const GameManagerGUI& _Other) = delete;
	GameManagerGUI(GameManagerGUI&& _Other) noexcept = delete;
	GameManagerGUI& operator=(const GameManagerGUI& _Other) = delete;
	GameManagerGUI& operator=(GameManagerGUI&& _Other) noexcept = delete;

protected:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

private:

};

