#include "PreCompile.h"
#include "PhysXTestStackBox.h"

PhysXTestStackBox::PhysXTestStackBox() 
{
}

PhysXTestStackBox::~PhysXTestStackBox() 
{
}

void PhysXTestStackBox::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physicXStackComponent_->CreatePhysXActors(_Scene, _physics);
}

void PhysXTestStackBox::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->SetMaterial("Color");
	Renderer->SetMesh("Box");

	ResultColor = float4(1.0f, 0.5f, 0.0f, 1.0f);
	Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", ResultColor);

	physicXStackComponent_ = CreateComponent<PhysicXStackComponent>();
}

