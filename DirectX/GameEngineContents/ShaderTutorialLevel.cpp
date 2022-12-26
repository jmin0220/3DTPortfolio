#include "PreCompile.h"
#include "ShaderTutorialLevel.h"
#include "TestActor_WaterPlane.h"

#include "ShaderTutorialActor.h"
#include "ShaderTutorialFloor.h"

ShaderTutorialLevel::ShaderTutorialLevel() 
{
}

ShaderTutorialLevel::~ShaderTutorialLevel() 
{
}

void ShaderTutorialLevel::Start()
{
	GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	// ��
	{
		LightObject = CreateActor<GameEngineLight>();
		LightObject->GetTransform().SetWorldPosition({ 0.0f, 0.0f, 0.0f });
		LightObject->GetTransform().SetWorldScale({ 7000.0f, 7000.0f, 7000.0f });
		LightObject->GetTransform().SetWorldRotation({ 90.0f + 10, 0.0f, 0.0f });
		GetMainCamera()->PushLight(LightObject);
		LightObject->GetLightData().LightType = 0;
		LightObject->GetLightData().PointLightRange = 1000.0f;
	}
}

void ShaderTutorialLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsPress(KEY_SPACEBAR))
	{
		LightObject->GetTransform().SetAddWorldRotation({ _DeltaTime * 360, 0, 0 });
	}
}

void ShaderTutorialLevel::LevelStartEvent()
{
	ContentsCore::GetInst()->LoadLevelResource(LEVELS::STAGE01_DOORDASH);

	std::shared_ptr<ShaderTutorialActor> Player = CreateActor<ShaderTutorialActor>();
	Player->GetTransform().SetWorldMove({ 0, 100, 0 });


	std::shared_ptr<ShaderTutorialFloor> Floor = CreateActor<ShaderTutorialFloor>();
	Floor->GetTransform().SetWorldMove({ 0, -500, 0 });
}

void ShaderTutorialLevel::LevelEndEvent()
{
}

//////////////////////////////////////////
//	���̴� Ʃ�丮��
//////////////////////////////////////////

/*
�غ� : ������, ���׸���(����������), ���̴�(.hlsl)

������ ���
- SetMesh > SetMaterial > SetConstantBuffer

1. �������� �޽��� �����ϰ�
	- Rect, Cube, 3DMesh ���
2. ������������ ���� VertexShader �� PixelShader�� ����, ���̴� �ȿ� �����Ǿ� ����
	- VertexShader
	-- ��1���� ��� ��ȯ���� (WVP������ Local->World��ȯ, UI�� WVP�ʿ���� ���)
	
	- VertexShader > *Rasteriser > PixelShader
	-- *Rasterizer �� �����ִµ� ���α׷��� �� �� �ִ� �κ� �ƴ�
	-- ViewPort��ȯ �����Ͷ��������� �Ͼ
	
	- PixelShader
	-- ��1���� ��� �������
	-- �ð����� ȿ�� �����ϴ� �κ�

3. ���̴� ���� ������۸� �̿��Ͽ� CPU�� �����͸� GPU������ ��ȯ


*/
