#include "PreCompile.h"
#include "TestActor_FogBox.h"

TestActor_FogBox::TestActor_FogBox()
{
}

TestActor_FogBox::~TestActor_FogBox()
{
}

void TestActor_FogBox::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("ENV_S5_Background_FogPlane.fbx", "Fog");

	Renderer_->GetTransform().SetWorldScale({ 0.001f, 0.001f, 0.001f });
	Renderer_->GetTransform().SetWorldPosition({ 0, -2000, 0 });

	FogData_.Color_ = float4::WHITE;
	FogData_.FogBottomPos_ = GetTransform().GetWorldPosition();
	FogData_.FogTopPos_ = FogData_.FogBottomPos_.y + Renderer_->GetTransform().GetWorldScale().y;

	std::vector<std::vector<GameEngineRenderUnit>>& UnitSet = Renderer_->GetAllRenderUnit();
	for (std::vector<GameEngineRenderUnit>& Units : UnitSet)
	{
		for (GameEngineRenderUnit& Unit : Units)
		{
			if (true == Unit.ShaderResources.IsConstantBuffer("FogData"))
			{
				Unit.ShaderResources.SetConstantBufferLink("FogData", FogData_);
			}

			if (true == Unit.ShaderResources.IsTexture("DiffuseTexture"))
			{
				Unit.ShaderResources.SetTexture("DiffuseTexture", "VFX_NoiseFog.png");
			}
		}
	}

}

void TestActor_FogBox::Update(float _DeltaTime)
{
}

void TestActor_FogBox::End()
{
}
