#include "PreCompile.h"
#include "VFXWaterActor.h"

VFXWaterActor::VFXWaterActor() 
{
}

VFXWaterActor::~VFXWaterActor() 
{
}

void VFXWaterActor::Start()
{
	std::shared_ptr<GameEngineFBXStaticRenderer> Renderer = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer->SetFBXMesh("Water.FBX", "Water");
	std::vector<std::vector<GameEngineRenderUnit>>& UnitSets = Renderer->GetAllRenderUnit();

	//WaterData_.WaterColor = float4::RED;
	WaterData_.WaterColor = float4{0.9f,0.4f,0.7f};

	for (std::vector<GameEngineRenderUnit>& Units : UnitSets)
	{
		for (GameEngineRenderUnit& Unit : Units)
		{
			Unit.ShaderResources.SetConstantBufferLink("WaterData", WaterData_);

			if ( true == Unit.ShaderResources.IsTexture("Tex"))
			{
				Unit.ShaderResources.SetTexture("Tex", "VFX_Noise02.png");
			}
		}
	}
}

void VFXWaterActor::Update(float _DeltaTime)
{
}

