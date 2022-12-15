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
	std::shared_ptr<GameEngineRenderUnit>& Unit = GetRenderUnit();
	Unit = CreateRenderUnit();

	PushRendererToUICamera();

	SetTextureRendererSetting();
}