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
    float4 Tex : TEXCOORD;
};


// 그래픽카드에서 이뤄지는것.
Output TextureCustom_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;

    return NewOutPut;
}

Texture2D Tex : register(t0);
SamplerState LINEARWRAP : register(s0);

float4 TextureCustom_PS(Output _Input) : SV_Target0
{
    float2 TexPos = _Input.Tex.xy;
    
    TexPos.y -= SumDeltaTime * 0.3f;//sum델타에 따라 움직인다(미러 적용되 있음)
    TexPos.x += SumDeltaTime * 0.3f;;

    float4 Color = Tex.Sample(LINEARWRAP, TexPos); 

    return Color;
}