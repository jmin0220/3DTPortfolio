#include "PreCompile.h"
#include "Hex_BackGroundObject.h"

Hex_BackGroundObject::Hex_BackGroundObject() 
{
}

Hex_BackGroundObject::~Hex_BackGroundObject() 
{
}

void Hex_BackGroundObject::Start()
{
	{
		Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
		Renderer_->SetFBXMesh("HexAGoneMap.FBX", "CustomDefferedColor");



		Renderer2_ = CreateComponent<GameEngineFBXStaticRenderer>();
		Renderer2_->SetFBXMesh("HexAGoneMountain.FBX", "CustomDefferedColor");


		std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSet = Renderer_->GetAllRenderUnit();
		for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSet)
		{
			for (std::shared_ptr<GameEngineRenderUnit> Unit : Units)
			{
				Unit->GetRenderer()->RenderOptionInst.IsNormal = 0;
			}
		}

		//Renderer->GetTransform().SetWorldScale({ 50.0f,50.0f, 50.0f });
	}

}

void Hex_BackGroundObject::Update(float _DeltaTime)
{
}

