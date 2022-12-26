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

	// 빛
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
//	쉐이더 튜토리얼
//////////////////////////////////////////

/*
준비 : 렌더러, 메테리얼(파이프라인), 쉐이더(.hlsl)

렌더러 기능
- SetMesh > SetMaterial > SetConstantBuffer

1. 렌더러의 메쉬를 설정하고
	- Rect, Cube, 3DMesh 등등
2. 파이프라인을 통해 VertexShader 와 PixelShader를 설정, 쉐이더 안에 서술되어 있음
	- VertexShader
	-- 점1개를 어떻게 변환할지 (WVP를통한 Local->World변환, UI는 WVP필요없음 등등)
	
	- VertexShader > *Rasteriser > PixelShader
	-- *Rasterizer 가 끼어있는데 프로그래밍 할 수 있는 부분 아님
	-- ViewPort변환 레스터라이저에서 일어남
	
	- PixelShader
	-- 점1개를 어떻게 출력할지
	-- 시각적인 효과 적용하는 부분

3. 쉐이더 안의 상수버퍼를 이용하여 CPU쪽 데이터를 GPU쪽으로 변환


*/
