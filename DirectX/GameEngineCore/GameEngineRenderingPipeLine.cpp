#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"

#include "GameEngineInputLayOut.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineInstancingBuffer.h"
#include "GameEngineBlend.h"


GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
	: // InputLayOut(nullptr)
	// , VertexBuffer(nullptr)
	VertexShader(nullptr)
	// , IndexBuffer(nullptr)
	, Rasterizer(nullptr)
	, PixelShader(nullptr)
	, DepthStencil(nullptr)
	, Blend(nullptr)
{

	Rasterizer = GameEngineRasterizer::Find("EngineRasterizer");
	Blend = GameEngineBlend::Find("AlphaBlend");
	DepthStencil = GameEngineDepthStencil::Find("EngineBaseDepth");
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine()
{
}

//
//void GameEngineRenderingPipeLine::SetInputAssembler1InputLayOutSetting(const std::string& _Name)
//{
//	InputLayOut = GameEngineInputLayOut::Find(_Name);
//
//	if (nullptr == InputLayOut)
//	{
//		MsgBoxAssert("�������� �ʴ� ��ǲ���̾ƿ��� �����Ϸ��� �߽��ϴ�.");
//		return;
//	}
//}

void GameEngineRenderingPipeLine::AllShaderReset()
{
	GameEngineDevice::GetContext()->VSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->GSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->DSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->HSSetShader(nullptr, nullptr, 0);
	GameEngineDevice::GetContext()->PSSetShader(nullptr, nullptr, 0);
}

GameEngineRenderingPipeLine* GameEngineRenderingPipeLine::Create()
{
	return CreateResUnName();
}

GameEngineRenderingPipeLine* GameEngineRenderingPipeLine::Create(const std::string& _Name)
{
	return CreateResName(_Name);
}

void GameEngineRenderingPipeLine::SetVertexShader(const std::string& _Name)
{
	VertexShader = GameEngineVertexShader::Find(_Name);

	if (nullptr == VertexShader)
	{
		MsgBoxAssert("�������� �ʴ� ���ؽ� ���̴��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	//// ��ǲ���̾ƿ��� ��������� �ʾҴµ�.
	//if (nullptr == InputLayOut && nullptr != VertexBuffer)
	//{
	//	InputLayOut = GameEngineInputLayOut::Create(*VertexBuffer->GetLayOutDesc(), VertexShader);
	//}
}

void GameEngineRenderingPipeLine::SetVertexShader(GameEngineVertexShader* _Shader)
{
	VertexShader = _Shader;

	// ��ǲ���̾ƿ��� ��������� �ʾҴµ�.
	// �ν��Ͻ̶� �����ɼ� �ִ�.
	//if (nullptr == InputLayOut && nullptr != VertexBuffer)
	//{
	//	InputLayOut = GameEngineInputLayOut::Create(*VertexBuffer->GetLayOutDesc(), VertexShader);
	//}

}


void GameEngineRenderingPipeLine::SetRasterizer(const std::string& _Name)
{
	Rasterizer = GameEngineRasterizer::Find(_Name);

	if (nullptr == Rasterizer)
	{
		MsgBoxAssert("�������� �ʴ� �����Ͷ����� ���ø� �����Ϸ��� �߽��ϴ�.");
		return;
	}

}


void GameEngineRenderingPipeLine::SetPixelShader(const std::string& _Name)
{
	PixelShader = GameEnginePixelShader::Find(_Name);

	if (nullptr == PixelShader)
	{
		MsgBoxAssert("�������� �ʴ� �ȼ����̴��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

}



void GameEngineRenderingPipeLine::SetOutputMergerDepthStencil(const std::string& _Name)
{
	DepthStencil = GameEngineDepthStencil::Find(_Name);

	if (nullptr == DepthStencil)
	{
		MsgBoxAssert("�������� �ʴ� ���̽��ٽǸ� �����Ϸ��� �߽��ϴ�.");
		return;
	}

}


void GameEngineRenderingPipeLine::SetOutputMergerBlend(const std::string& _Name)
{
	Blend = GameEngineBlend::Find(_Name);

	if (nullptr == Blend)
	{
		MsgBoxAssert("�������� �ʴ� �������� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::Setting()
{
	// InputAssembler1VertexBufferSetting();

	VertexShaderSetting();

	// InputAssembler2IndexBufferSetting();

	RasterizerSetting();

	PixelShaderSetting();

	OutputMergerBlendSetting();

	OutputMergerDepthStencilSetting();

	// Draw();

}

void GameEngineRenderingPipeLine::RenderingInstancing(int _RenderingCount, class GameEngineInstancingBuffer* _Buffer)
{
	InputAssembler1InstancingVertexBufferSetting(_Buffer);

	VertexShaderSetting();

	// InputAssembler2IndexBufferSetting();

	RasterizerSetting();

	PixelShaderSetting();

	OutputMergerBlendSetting();

	OutputMergerDepthStencilSetting();

	InstancingDraw(_RenderingCount);

}

void GameEngineRenderingPipeLine::InstancingDataCollect()
{
	// InstancingDraw();
}

// ���������� ������ ������ �״��� �߿����� �ʴ�.

void GameEngineRenderingPipeLine::InputAssembler1InstancingVertexBufferSetting(GameEngineInstancingBuffer* _Buffer)
{
	// �׷��ȸ��ҽ��� Setting�̶�� �Լ��� �����Ѵٸ�
// �װ� �������� �� �������� ������ ������������ ���ư��� �ȴٴ� ���� �˴ϴ�.
	// InputLayOut->Setting();
	// ���ؽ� ���۴� �����Ұ� ����.
	// VertexBuffer->Setting();

	// 2��°�� �ν��Ͻ� ������ 

	// GameEngineVertexBuffer* InstancingBuffer;

	//ID3D11Buffer* ArrBuffer[2] = { VertexBuffer->GetBuffer(), _Buffer->GetBuffer() };
	//UINT ArrVertexSize[2] = { VertexBuffer->GetVertexSize(), _Buffer->GetDataSize()};
	//UINT ArrOffset[2] = { 0, 0 };

	//GameEngineDevice::GetContext()->IASetVertexBuffers(
	//	0, // ���ؽ� ���۸� ���������ͷ� �������������� ������ �ε���
	//	2, ArrBuffer, ArrVertexSize, ArrOffset);
}

void GameEngineRenderingPipeLine::VertexShaderSetting()
{
	VertexShader->Setting();
	// ��ġ 
	// D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}


void GameEngineRenderingPipeLine::RasterizerSetting()
{
	Rasterizer->Setting();
}

void GameEngineRenderingPipeLine::PixelShaderSetting()
{
	PixelShader->Setting();
}

void GameEngineRenderingPipeLine::OutputMergerBlendSetting()
{
	Blend->Setting();
}

void GameEngineRenderingPipeLine::OutputMergerDepthStencilSetting()
{
	DepthStencil->Setting();
}


//void GameEngineRenderingPipeLine::Draw(GameEngineMesh* _Mesh)
//{
//	GameEngineDevice::GetContext()->DrawIndexed(IndexBuffer->GetIndexCount(), 0, 0);
//}

void GameEngineRenderingPipeLine::InstancingDraw(int _RenderingCount)
{
	//[in] IndexCountPerInstance ���� : UINT
	//�� �ν��Ͻ��� ���� �ε��� ���ۿ��� ���� �ε��� ���Դϴ�.
	//

	//[in] InstanceCount ���� : UINT
	//�׸� �ν��Ͻ� ���Դϴ�.

	//[in] StartIndexLocation
	//���� : UINT GPU�� �ε��� ���ۿ��� ���� ù ��° �ε����� ��ġ�Դϴ�.

	//[in] BaseVertexLocation ���� : ����
	//���� ���ۿ��� ������ �б� ���� �� �ε����� �߰��� ���Դϴ�.

	//[in] StartInstanceLocation ���� : UINT
	//���� ���ۿ��� �ν��Ͻ��� �����͸� �б� ���� �� �ε����� �߰��� ���Դϴ�.

	// �׳� 4�� ����.
	// GameEngineDevice::GetContext()->DrawIndexedInstanced(IndexBuffer->GetIndexCount(), _RenderingCount, 0, 0, 0);
}

void GameEngineRenderingPipeLine::Copy(GameEngineRenderingPipeLine* _Original)
{
	// InputLayOut			= _Original->InputLayOut;
	// VertexBuffer			= _Original->VertexBuffer;
	VertexShader = _Original->VertexShader;
	// IndexBuffer			= _Original->IndexBuffer;
	// Topology				= _Original->Topology;
	Rasterizer = _Original->Rasterizer;
	PixelShader = _Original->PixelShader;
	DepthStencil = _Original->DepthStencil;
	Blend = _Original->Blend;
}