#include "PreCompile.h"
#include "PhysXTestBox.h"

PhysXTestBox::PhysXTestBox() 
{
}

PhysXTestBox::~PhysXTestBox() 
{
}

void PhysXTestBox::Start()
{	
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->SetPipeLine("Color");
	Renderer->SetMesh("Box");

	ResultColor = float4(1.0f, 0.5f, 0.0f, 1.0f);
	Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", ResultColor);
}

void PhysXTestBox::Update(float _DeltaTime)
{
}

