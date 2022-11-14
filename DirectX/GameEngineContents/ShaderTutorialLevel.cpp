#include "PreCompile.h"
#include "ShaderTutorialLevel.h"
#include "TestActor_WaterPlane.h"

ShaderTutorialLevel::ShaderTutorialLevel() 
{
}

ShaderTutorialLevel::~ShaderTutorialLevel() 
{
}

void ShaderTutorialLevel::Start()
{
	// ���̴� Ʃ�丮�� //
	

}

void ShaderTutorialLevel::Update(float _DeltaTime)
{
}

void ShaderTutorialLevel::LevelStartEvent()
{
	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	std::shared_ptr<GameEngineActor> WaterPlane = CreateActor<TestActor_WaterPlane>();
	
}

void ShaderTutorialLevel::LevelEndEvent()
{
}
