#include "PreCompile.h"
#include "SkyboxActor.h"

SkyboxActor::SkyboxActor()
{
}

SkyboxActor::~SkyboxActor()
{
}

void SkyboxActor::Start()
{
	StaticRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	StaticRenderer_->SetFBXMesh("Skybox_S5.fbx", "Texture");


	// 텍스쳐 씌워주기
	std::vector<std::vector<GameEngineRenderUnit>>& UnitSet = StaticRenderer_->GetAllRenderUnit();
	for (std::vector<GameEngineRenderUnit>& Units : UnitSet)
	{
		for (GameEngineRenderUnit& Unit : Units)
		{
			if (true == Unit.ShaderResources.IsTexture("DiffuseTexture"))
			{
				Unit.ShaderResources.SetTexture("DiffuseTexture", "S4_SkyBox.png");
			}
		}
	}


	StaticRenderer_->GetTransform().SetLocalPosition(float4(0, -50, 0));

}

void SkyboxActor::Update(float _DeltaTime)
{
	GetTransform().SetWorldPosition(GetLevel()->GetMainCameraActorTransform().GetWorldPosition());
}

