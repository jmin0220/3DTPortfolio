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

	// �ؽ��� �����ֱ�
	//std::vector<std::vector<GameEngineRenderUnit>>& UnitSet = StaticRenderer_->GetAllRenderUnit();
	std::vector<std::vector< std::shared_ptr<GameEngineRenderUnit>>>& UnitSet = StaticRenderer_->GetAllRenderUnit();
	for (std::vector< std::shared_ptr<GameEngineRenderUnit>>& Units : UnitSet)
	{
		for (std::shared_ptr<GameEngineRenderUnit>& Unit : Units)
		{
			if (true == Unit->ShaderResources.IsTexture("DiffuseTexture"))
			{
				Unit->ShaderResources.SetTexture("DiffuseTexture", "S4_SkyBox.png");
			}
		}
	}


	// ũ��� �Ǻ� ����
	StaticRenderer_->GetTransform().SetWorldScale({ 100, 100, 100 });

}

void SkyboxActor::Update(float _DeltaTime)
{
	GetTransform().SetWorldPosition(GetLevel()->GetMainCameraActorTransform().GetWorldPosition());
}

