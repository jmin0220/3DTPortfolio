#pragma once
#include <GameEngineCore/GameEngineGUI.h>
// Ό³Έν :
class CustomableGUI : public GameEngineGUIWindow
{
public:
	void SetGUIDebugFunc(std::function<void()> _Func);

public:
	// constrcuter destructer
	CustomableGUI();
	~CustomableGUI();

	// delete Function
	CustomableGUI(const CustomableGUI& _Other) = delete;
	CustomableGUI(CustomableGUI&& _Other) noexcept = delete;
	CustomableGUI& operator=(const CustomableGUI& _Other) = delete;
	CustomableGUI& operator=(CustomableGUI&& _Other) noexcept = delete;

protected:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
private:
	std::function<void()> OutputFunc_;
};

