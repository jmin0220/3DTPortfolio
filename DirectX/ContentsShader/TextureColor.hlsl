// #include "myshader.hlsli"

// SV_POSITION �ø�ƽ
// �׷���ī�忡�� �̳༮�� �̷� �η��ϱ� �ϰ� �ڵ����� ó���ϴ� �༮�� ������ �ϰ�.

#include "TransformHeader.fx"

// 0                                                                                                1 
// 0�������������������������������������������������������������������������������������������������1

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
    float4 Tex : TEXCOORD;
};

// 1000
// 0100
// 2010
// 0301

// 1020
// 0103
// 0010
// 0001


// �׷���ī�忡�� �̷����°�.
Output Texture_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    
    return NewOutPut;
}

cbuffer MeshPixelData : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
    float4 Slice;
}

Texture2D DiffuseTexture : register(t0);
SamplerState LINEARWRAP : register(s0);

float4 Texture_PS(Output _Input) : SV_Target0
{
    float4 Color = DiffuseTexture.Sample(LINEARWRAP, _Input.Tex.xy);
    
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    if (_Input.Tex.x < Slice.x)
    {
        clip(-1);
    }
    
    if (_Input.Tex.y < Slice.y)
    {
        clip(-1);
    }
    

    float4 Result = (DiffuseTexture.Sample(LINEARWRAP, _Input.Tex.xy) * MulColor) + PlusColor;
    
    if (1 <= Result.a)
    {
        Result.a = 1.0f;

    }
    
    // Result.a = 1.0f;
    
    return Result;
   // return Color;
}