#include "PreCompile.h"
#include "AxisActor.h"

#include "XAxis.h"
#include "YAxis.h"
#include "ZAxis.h"


AxisActor::AxisActor() 
{
}

AxisActor::~AxisActor() 
{
}

void AxisActor::Start()
{
	{
		XRenderer = CreateComponent<GameEngineTextureRenderer>();
		XRenderer->GetTransform().SetWorldScale({ 125.0f,25.0f,25.0f });
		XRenderer->GetTransform().SetWorldPosition({ 50.0f,0,0 });
		XRenderer->SetPipeLine("CustomColor");
		XRenderer->SetMesh("Box");

		XAxisOption.Color = float4(1.0f, 0.0f, 0.0f, 0.5f);
		XRenderer->GetShaderResources().SetConstantBufferLink("AxisData", XAxisOption);
	}

	{
		YRenderer = CreateComponent<GameEngineTextureRenderer>();
		YRenderer->GetTransform().SetWorldScale({ 25.0f,125.0f,25.0f });
		YRenderer->GetTransform().SetWorldPosition({ 0.0f,50.0f,0 });
		YRenderer->SetPipeLine("CustomColor");
		YRenderer->SetMesh("Box");

		YAxisOption.Color = float4(0.0f, 1.0f, 0.0f, 0.5f);
		YRenderer->GetShaderResources().SetConstantBufferLink("AxisData", YAxisOption);
	}

	{
		ZRenderer = CreateComponent<GameEngineTextureRenderer>();
		ZRenderer->GetTransform().SetWorldScale({ 25.0f,25.0f,125.0f });
		ZRenderer->GetTransform().SetWorldPosition({ 0.0f,0,-50.0f });
		ZRenderer->SetPipeLine("CustomColor");
		ZRenderer->SetMesh("Box");

		ZAxisOption.Color = float4(0.0f, 0.0f, 1.0f, 0.5f);
		ZRenderer->GetShaderResources().SetConstantBufferLink("AxisData", ZAxisOption);
	}
	//GetTransform().SetWorldRotation({ -10.0f, 20.0f, 0.0f });


	XAxis_ = GetLevel()->CreateActor<XAxis>();
	YAxis_ = GetLevel()->CreateActor<YAxis>();
	ZAxis_ = GetLevel()->CreateActor<ZAxis>();

	XAxis_->SetParent(this);
	YAxis_->SetParent(this);
	ZAxis_->SetParent(this);
}

void AxisActor::Update(float _DeltaTime)
{
	//CheckPickingRay();

	//메쉬의 포지션 
	//GetTransform().SetWorldPosition({ XAxis_->GetTransform().GetWorldPosition().x,
	//								  YAxis_->GetTransform().GetWorldPosition().y,
	//								  ZAxis_->GetTransform().GetWorldPosition().z });


	//XAxis_->GetTransform().SetWorldPosition({ XAxis_->GetTransform().GetWorldPosition().x,
	//										  YAxis_->GetTransform().GetWorldPosition().y,
	//										  ZAxis_->GetTransform().GetWorldPosition().z });

	//YAxis_->GetTransform().SetWorldPosition({ XAxis_->GetTransform().GetWorldPosition().x,
	//										  YAxis_->GetTransform().GetWorldPosition().y,
	//										  ZAxis_->GetTransform().GetWorldPosition().z });

	//ZAxis_->GetTransform().SetWorldPosition({ XAxis_->GetTransform().GetWorldPosition().x,
	//										  YAxis_->GetTransform().GetWorldPosition().y,
	//										  ZAxis_->GetTransform().GetWorldPosition().z });
}

void AxisActor::SetPosition()
{
	XAxis_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	YAxis_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	ZAxis_->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
}
