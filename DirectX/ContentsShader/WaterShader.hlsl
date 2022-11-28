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

cbuffer PatternSmpData : register(b1)
{
    float2 SmpStartPos;
    float2 SmpScale;
};


// 그래픽카드에서 이뤄지는것.
Output WaterShader_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.Tex0 = _Input.Tex;
    
    NewOutPut.Tex1.x = (_Input.Tex.x * SmpStartPos.x) + SmpStartPos.x;
    NewOutPut.Tex1.y = (_Input.Tex.y * SmpScale.y) + SmpScale.y;
    
    return NewOutPut;
}

Texture2D WaterTex : register(t0);
Texture2D PatternTex : register(t1);
Texture2D NoiseTex : register(t2);
SamplerState LINEARMIRROR : register(s0);

#define TAU 6.28318530718
#define MAX_ITER 5

float4 WaterShader_PS(Output _Input) : SV_Target0
{
    float2 TexPos = _Input.Tex0.xy;
    float4 WaterColor = WaterTex.Sample(LINEARMIRROR, TexPos);
    
    float2 PatternPos = _Input.Tex1.xy;
    float4 PatternColor = PatternTex.Sample(LINEARMIRROR, PatternPos);

    if (PatternColor.a == 0)
    {
        return WaterColor;
    }
    else
    {
        WaterColor.rgb = WaterColor.rgb * 0.6 + PatternColor.rgb * 0.4;
        WaterColor.a = WaterColor.a * 0.6 + PatternColor.a * 0.4;
    }
    
  
    return WaterColor;
}