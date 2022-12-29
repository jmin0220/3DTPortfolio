#include "PreCompile.h"
#include "JumboTron.h"

JumboTron::JumboTron() 
{
}

JumboTron::~JumboTron() 
{
}

void JumboTron::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();

	std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSet = Renderer_->GetAllRenderUnit();
	for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSet)
	{
		for (std::shared_ptr<GameEngineRenderUnit> Unit : Units)
		{
			Unit->GetRenderer()->RenderOptionInst.IsNormal = 0;
		}
	}
}

void JumboTron::Update(float _DeltaTime)
{
}

