// #include "myshader.hlsli"

// SV_POSITION 시맨틱
// 그래픽카드에게 이녀석은 이런 부류니까 니가 자동으로 처리하는 녀석이 있으면 하고.

#include "TransformHeader.fx"

// 0                                                                                                1 
// 0□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□1

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


// 그래픽카드에서 이뤄지는것.
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
