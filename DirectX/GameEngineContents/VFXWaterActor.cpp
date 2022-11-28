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
	//WaterData_.WaterColor = float4{0.99f,0.63f,0.79f};

	for (std::vector<GameEngineRenderUnit>& Units : UnitSets)
	{
		for (GameEngineRenderUnit& Unit : Units)
		{

			if ( true == Unit.ShaderResources.IsTexture("WaterTex"))
			{
				Unit.ShaderResources.SetTexture("WaterTex", "WaterColor.png");
			}

			if (true == Unit.ShaderResources.IsTexture("PatternTex"))
			{
				Unit.ShaderResources.SetTexture("PatternTex", "ENV_WaterPattern.png");
			}

			if (true == Unit.ShaderResources.IsTexture("NoiseTex"))
			{
				Unit.ShaderResources.SetTexture("NoiseTex", "VFX_Noise02.png");
			}
		}
	}
}

void VFXWaterActor::Update(float _DeltaTime)
{
}

