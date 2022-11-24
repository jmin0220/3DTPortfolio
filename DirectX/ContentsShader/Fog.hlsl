#include "RenderOption.fx"
#include "TransformHeader.fx"

struct Input
{
    float4 Pos : POSITION;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
};

Texture2D DiffuseTexture : register(t0);
SamplerState LINEARWRAP : register(s0);

Output Fog_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    
    return NewOutPut;
}

cbuffer FogData : register(b0)
{
    float4 FogBottomPos;
    float4 FogTopPos;
    float4 Color;
}


float4 Fog_PS(Output _Input) : SV_Target0
{
    float2 TexPos = _Input.Pos.xy;
    float3 Color = DiffuseTexture.Sample(LINEARWRAP, TexPos).rgb;

    
    return float4(Color.rgb, 0.8);

}

