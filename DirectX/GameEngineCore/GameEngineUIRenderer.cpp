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
	// 22.11.27(��) �輺�� : ���� ���� �κ�
	// GameEngineUIRenderer�� �������� Unit�� ����Ʈ������ �ʱ�ȭ�� �������.
	std::shared_ptr<GameEngineRenderUnit>& Unit = GetRenderUnit();
	Unit = std::make_shared<GameEngineRenderUnit>();

	PushRendererToUICamera();

	SetTextureRendererSetting();
}