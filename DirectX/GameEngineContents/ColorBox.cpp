#include "PreCompile.h"
#include "ColorBox.h"
#include <GameEngineCore/CoreMinimal.h>

ColorBox::ColorBox() 
{
}

ColorBox::~ColorBox() 
{
}

void ColorBox::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->SetPipeLine("Color");
	Renderer->SetMesh("Box");

	ResultColor = float4(0.0f, 0.5f, 0.0f, 1.0f);
	Renderer->GetShaderResources().SetConstantBufferLink("ResultColor", ResultColor);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 1, 1, 1 });
	Collision->ChangeOrder(CollisionGroup::Map);
	Collision->SetDebugSetting(CollisionType::CT_OBB, float4(0.0f, 1.0f, 0.0f, 0.5f));

	GetTransform().SetWorldScale({ 100, 100, 100 });

	// 마우스 피킹
	CreatePickingCollision(Collision->GetTransform().GetWorldScale(), Collision->GetTransform().GetWorldPosition());
}

void ColorBox::Update(float _DeltaTime)
{

	// 마우스 피킹
	CheckPickingRay();
}

void ColorBox::End()
{
}
