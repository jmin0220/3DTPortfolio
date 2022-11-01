#include "PreCompile.h"
#include "CameraTestLevel.h"

#include "TestActor_WaterPlane.h"
#include "TestActor_Character.h"

CameraTestLevel::CameraTestLevel() 
{
}

CameraTestLevel::~CameraTestLevel() 
{
}

void CameraTestLevel::Start()
{
	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
		GetMainCameraActor()->GetTransform().SetWorldMove({ 0, 200, -3000 });
	}


	TestActor_WaterPlane* Floor = CreateActor<TestActor_WaterPlane>();

	Player_ = CreateActor<TestActor_Character>();
	Player_->GetTransform().SetWorldPosition({ 0, 300, 0 });
}

void CameraTestLevel::Update(float _DeltaTime)
{

}

void CameraTestLevel::End()
{
}
