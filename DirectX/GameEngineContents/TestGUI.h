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

	inline void SetObj(std::shared_ptr<HoopsStageObjects> _Obj)
	{
		Obj = _Obj;
	}

private:
	std::shared_ptr<HoopsStageObjects> Obj;
	GameEngineLevel* ConnectedLevel;
};

