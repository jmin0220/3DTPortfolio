#include "PreCompile.h"
#include "CustomableGUI.h"
#include <GameEngineCore/CoreMinimal.h>


CustomableGUI::CustomableGUI()
{
}

CustomableGUI::~CustomableGUI() 
{
}

void CustomableGUI::Initialize(GameEngineLevel* _Level)
{
}

void CustomableGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	OutputFunc_();
}

void CustomableGUI::SetGUIDebugFunc(std::function<void()> _Func)
{
	OutputFunc_ = _Func;
}