#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include "PickableActor.h"
#include "HoopsStageObjects.h"


// Ό³Έν :
class TestGUI : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	TestGUI();
	~TestGUI();

	// delete Function
	TestGUI(const TestGUI& _Other) = delete;
	TestGUI(TestGUI&& _Other) noexcept = delete;
	TestGUI& operator=(const TestGUI& _Other) = delete;
	TestGUI& operator=(TestGUI&& _Other) noexcept = delete;

protected:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

public:
	void SetLight(std::shared_ptr<GameEngineLight> _Light)
	{
		Light_ = _Light;
	}
private:
	std::shared_ptr<GameEngineLight> Light_;
	GameEngineLevel* ConnectedLevel;
};

