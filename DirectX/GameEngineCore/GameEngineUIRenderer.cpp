#include "PreCompile.h"
#include "GameEngineUIRenderer.h"

GameEngineUIRenderer::GameEngineUIRenderer() 
{
}

GameEngineUIRenderer::~GameEngineUIRenderer() 
{
}

void GameEngineUIRenderer::Start() 
{
	// 22.11.27(일) 김성훈 : 엔진 수정 부분
	// GameEngineUIRenderer는 렌더러의 Unit의 스마트포인터 초기화를 안해줬다.
	std::shared_ptr<GameEngineRenderUnit>& Unit = GetRenderUnit();
	Unit = std::make_shared<GameEngineRenderUnit>();

	PushRendererToUICamera();

	SetTextureRendererSetting();
}