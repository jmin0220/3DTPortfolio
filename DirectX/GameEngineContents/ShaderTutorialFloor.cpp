#include "PreCompile.h"
#include "ShaderTutorialFloor.h"
#include <GameEngineCore/CoreMinimal.h>

ShaderTutorialFloor::ShaderTutorialFloor() 
{
}

ShaderTutorialFloor::~ShaderTutorialFloor() 
{
}

void ShaderTutorialFloor::Start()
{
	

	//{
	//	std::shared_ptr <GameEngineDefaultRenderer> Renderer = CreateComponent<GameEngineDefaultRenderer>();
	//	Renderer->SetMesh("Box");
	//	Renderer->SetMaterial("DeferredColor");
	//	Renderer->GetTransform().SetLocalScale({ 2000.0f, 50.0f, 2000.0f });

	//	if (true == Renderer->GetRenderUnit()->ShaderResources.IsConstantBuffer("ResultColor"))
	//	{
	//		Renderer->GetRenderUnit()->ShaderResources.SetConstantBufferNew("ResultColor", float4(1.0f, 0.0f, 0.0f, 1.0f));
	//	}
	//}


	PlatformRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	PlatformRenderer_->SetFBXMesh("DoorDashPlatformCollisionMesh.FBX", "CustomDefferedColor");

	WallRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	WallRenderer_->SetFBXMesh("DoorDashWallCollisionMesh.FBX", "CustomDefferedColor");

	GetTransform().SetLocalScale({ 4, 4, 4 });
}

void ShaderTutorialFloor::Update(float _DeltaTime)
{
}

void ShaderTutorialFloor::End()
{
}
