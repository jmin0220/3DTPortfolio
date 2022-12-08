#include "PreCompile.h"
#include "UISkyBoxActor.h"

UISkyBoxActor::UISkyBoxActor() 
{
}

UISkyBoxActor::~UISkyBoxActor() 
{
}

void UISkyBoxActor::Start()
{
	StaticRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	StaticRenderer_->SetFBXMesh("Skybox.fbx", "Texture");

	// �ؽ��� �����ֱ�
	std::vector<std::vector<GameEngineRenderUnit>>& UnitSet = StaticRenderer_->GetAllRenderUnit();
	for (std::vector<GameEngineRenderUnit>& Units : UnitSet)
	{
		for (GameEngineRenderUnit& Unit : Units)
		{
			if (true == Unit.ShaderResources.IsTexture("DiffuseTexture"))
			{
				Unit.ShaderResources.SetTexture("DiffuseTexture", "Respawn_SkyBox.png");
			}
		}
	}

	// ũ��� �Ǻ� ����
	StaticRenderer_->GetTransform().SetWorldScale({ 100, 100, 100 });
}

void UISkyBoxActor::Update(float _DeltaTime)
{
	GetTransform().SetWorldPosition(GetLevel()->GetMainCameraActorTransform().GetWorldPosition());
}

