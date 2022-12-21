// #include "myshader.hlsli"

// SV_POSITION �ø�ƽ
// �׷���ī�忡�� �̳༮�� �̷� �η��ϱ� �ϰ� �ڵ����� ó���ϴ� �༮�� ������ �ϰ�.

// t1

// Create("TransformData");
#include "TransformHeader.fx"
#include "LightHeader.fx"
#include "DeferredHeader.fx"

// cbuffer Color : 
// TestColor;
struct Input
{
    float4 Pos : POSITION;
    float4 Normal : NORMAL;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 ViewPos : POSITION;
    float4 ViewNormal : NORMAL;
    float4 Tex : TEXCOORD;
};


//cbuffer ResultColor : register(b2)
//{
//    float4 PlusColor;
//    float4 MultyplyColor;
//}



// 1000
// 0100
// 2010
// 0301

// 1020
// 0103
// 0010
// 0001

Output Color_VS(Input _Input)
{
    // ���̴��� ��쿡�� ��κ��� ��Ȳ���� ����ȯ�� �����ϴ�.
    Output NewOutPut = (Output)0;
    
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.ViewPos = mul(_Input.Pos, WorldView);
    NewOutPut.Tex = _Input.Tex;
    
    _Input.Normal.w = 0.0f;
    NewOutPut.ViewNormal = normalize(mul(_Input.Normal, WorldView));
    NewOutPut.ViewNormal.w = 0.0f;
    
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
DeferredOutPut Color_PS(Output _Input) : SV_Target0
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
    DeferredOutPut OutPut;
    
    OutPut.Dif = Result;
    OutPut.Pos = _Input.ViewPos;
    OutPut.Nor = _Input.ViewNormal;
   // OutPut.Tex = DiffuseTexture.Sample(LINEARWRAP, _Input.Tex.xy);
    OutPut.Nor.w = 1.0f;
    
    
    return OutPut;
}
