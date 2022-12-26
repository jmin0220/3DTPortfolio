#include "PreCompile.h"
#include "ShaderTutorialActor.h"
#include <GameEngineCore/CoreMinimal.h>

ShaderTutorialActor::ShaderTutorialActor() 
{
}

ShaderTutorialActor::~ShaderTutorialActor() 
{
}

void ShaderTutorialActor::Start()
{
	{
		std::shared_ptr <GameEngineDefaultRenderer> Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->SetMesh("Sphere");
		Renderer->SetMaterial("DeferredColor");
		Renderer->GetTransform().SetLocalScale({ 100.0f, 100.0f, 100.0f });

		if (true == Renderer->GetRenderUnit()->ShaderResources.IsConstantBuffer("ResultColor"))
		{
			Renderer->GetRenderUnit()->ShaderResources.SetConstantBufferNew("ResultColor", float4(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}





}

void ShaderTutorialActor::Update(float _DeltaTime)
{
}

void ShaderTutorialActor::End()
{
}
