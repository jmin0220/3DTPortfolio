#include "PreCompile.h"
#include "Chevron.h"

Chevron::Chevron() :
	RotY(420.0f)
{
}

Chevron::~Chevron() 
{
}

void Chevron::Start()
{
	ChevronRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	ChevronRenderer_->SetFBXMesh("Chevron.FBX","Texture");

	PropellerRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	PropellerRenderer_->SetFBXMesh("Propeller.FBX", "Texture");
	PropellerRenderer_->GetTransform().SetLocalScale({ 3,3,3  });
	PropellerRenderer_->GetTransform().SetLocalPosition({ 0,-2.5f,0 });

}

void Chevron::Update(float _DeltaTime)
{

	PropellerRenderer_->GetTransform().SetLocalRotate({ 0,RotY * _DeltaTime ,0 });
}

