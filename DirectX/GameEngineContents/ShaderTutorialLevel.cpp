#include "PreCompile.h"
#include "ShaderTutorialLevel.h"
#include "TestActor_WaterPlane.h"

ShaderTutorialLevel::ShaderTutorialLevel() 
{
}

ShaderTutorialLevel::~ShaderTutorialLevel() 
{
}

void ShaderTutorialLevel::Start()
{

}

void ShaderTutorialLevel::Update(float _DeltaTime)
{
}

void ShaderTutorialLevel::LevelStartEvent()
{
	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	std::shared_ptr<GameEngineActor> WaterPlane = CreateActor<TestActor_WaterPlane>();
	
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
- SetMesh > SetPipeline > SetConstantBuffer

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
