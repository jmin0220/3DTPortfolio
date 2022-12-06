#include "PreCompile.h"
#include "PhysXTestBox.h"

PhysXTestBox::PhysXTestBox() 
{
}

PhysXTestBox::~PhysXTestBox() 
{
}

// TODO::�������� Component�� ����?
void PhysXTestBox::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physicXComponent_->CreatePhysXActors(_Scene, _physics);
}

void PhysXTestBox::Start()
{	
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->SetMaterial("Color");
	Renderer->SetMesh("Box");

	ResultColor = float4(1.0f, 0.5f, 0.0f, 1.0f);
	Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", ResultColor);

	physicXComponent_ = CreateComponent<PhysicXComponent>();
}