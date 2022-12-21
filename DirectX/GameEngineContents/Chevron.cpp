#include "PreCompile.h"
#include "Chevron.h"

int Chevron::Num = 0;

Chevron::Chevron() :
	RotY(420.0f)
{

	Num++;
	MyNum = Num;
}

Chevron::~Chevron() 
{
}

void Chevron::Start()
{
	ChevronRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	ChevronRenderer_->SetFBXMesh("Chevron.FBX","CustomDefferedColor");

	PropellerRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	PropellerRenderer_->SetFBXMesh("Propeller.FBX", "CustomDefferedColor");
	PropellerRenderer_->GetTransform().SetLocalScale({ 3,3,3  });
	PropellerRenderer_->GetTransform().SetLocalPosition({ 0,-2.5f,0 });

}

void Chevron::Update(float _DeltaTime)
{
	if (MyNum >= 7)
	{
		PropellerRenderer_->GetTransform().SetLocalRotate({ 0,RotY * -_DeltaTime ,0 });
	}
	else
	{
		PropellerRenderer_->GetTransform().SetLocalRotate({ 0,RotY * _DeltaTime ,0 });
	}
}

