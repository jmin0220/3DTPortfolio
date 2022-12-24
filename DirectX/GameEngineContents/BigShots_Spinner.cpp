#include "PreCompile.h"
#include "BigShots_Spinner.h"

BigShots_Spinner::BigShots_Spinner() 
{
}

BigShots_Spinner::~BigShots_Spinner() 
{
}

void BigShots_Spinner::Start()
{
	FBXRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	FBXRenderer_->SetFBXMesh("S04Chevron_low1_TopRotater_low_MainTriRotater2_low.FBX", "CustomDefferedColor");
}

void BigShots_Spinner::Update(float _DeltaTime)
{
	FBXRenderer_->GetTransform().SetLocalRotate({ 0,60.0f * _DeltaTime ,0 });
}

