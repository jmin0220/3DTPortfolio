#include "TransformHeader.fx"
#include "RenderOption.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
    float4 Tex0 : TEXCOORD0;
    float4 Tex1 : TEXCOORD1;
};

cbuffer MaskingData : register(b1)
{
    float2 MaskTexPos;
    float2 MaskTexScale;
}

// 그래픽카드에서 이뤄지는것.
Output MaskShader_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.Tex0 = _Input.Tex;
    
    NewOutPut.Tex1.x = (_Input.Tex.x * MaskTexPos.x) + MaskTexPos.x;
    NewOutPut.Tex1.y = (_Input.Tex.y * MaskTexScale.y) + MaskTexScale.y;
    
    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
Texture2D MaskTexture : register(t1);

SamplerState LINEARWRAP : register(s0);


float4 MaskShader_PS(Output _Input) : SV_Target0
{
    float2 TexPos = _Input.Tex0.xy;
    float2 MaskPos = _Input.Tex1.xy;
    
    float4 Color = DiffuseTexture.Sample(LINEARWRAP, TexPos);
    float4 MaskColor = MaskTexture.Sample(LINEARWRAP, MaskPos);
    
    if (MaskColor.a > 0.0f && MaskColor.r > 0.5f)
    {
        Color.rgb = Color.rgb * 0.5f + MaskColor.rgb * 0.5f;
    }
    
    return Color;
}