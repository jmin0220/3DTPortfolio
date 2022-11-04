#include "TransformHeader.fx"

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


// 그래픽카드에서 이뤄지는것.
Output TextureCustom_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    
    return NewOutPut;
}

cbuffer TexPivot : register(b0)
{
    float4 Pivot;
}

Texture2D DiffuseTexture : register(t0);
SamplerState LINEARWRAP : register(s0);

float4 TextureCustom_PS(Output _Input) : SV_Target0
{
    float2 TexPos = _Input.Tex.xy;
    TexPos.xy += Pivot.xy;
    
    float4 Color = DiffuseTexture.Sample(LINEARWRAP, TexPos);
    
    
    return Color;
}