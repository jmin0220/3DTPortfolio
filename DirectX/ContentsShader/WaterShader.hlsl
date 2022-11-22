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
Output WaterShader_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.Tex = _Input.Tex;
    
    return NewOutPut;
}

cbuffer WaterData : register(b0)
{
    float4 WaterColor;
}

Texture2D Tex : register(t0);
SamplerState POINTWRAP : register(s0);

#define TAU 6.28318530718
#define MAX_ITER 5

float4 WaterShader_PS(Output _Input) : SV_Target0
{
    float2 TexPos = _Input.Tex.xy;

    // 물결 빠르기(값이 클수록 빠름)
    float Time = SumDeltaTime * .1 + 23.0;
    
#ifdef SHOW_TILING
	vec2 p = fmod(TexPos*TAU*2.0, TAU)-250.0;
#else
    float2 p = fmod(TexPos * TAU, TAU) - 250.0;
#endif
    float2 i = float2(p.x, p.y);
    // 값이 클수록 눈부심이 덜한걸로 추측
    float c = 1.8;
    float inten = .005;

    for (int n = 0; n < MAX_ITER; n++)
    {
        float t = Time * (1.0 - (3.5 / float(n + 1)));
        i = p + float2(cos(t - i.x) + sin(t + i.y), sin(t - i.y) + cos(t + i.x));
        c += 1.0 / length(float2(p.x / (sin(i.x + t) / inten), p.y / (cos(i.y + t) / inten)));
    }
    c /= float(MAX_ITER);
    c = 1.17 - pow(c, 1.4);
    
    float d = pow(abs(c), 8.0);
    float3 colour = float3(d, d, d);
    colour = clamp(colour + float3(WaterColor.r, WaterColor.g, WaterColor.b), 0.0, 1.0);

#ifdef SHOW_TILING
	// Flash tile borders...
	vec2 pixel = 2.0 / iResolution.xy;
	uv *= 2.0;
	float f = floor(mod(iTime*.5, 2.0)); 	// Flash value.
	vec2 first = step(pixel, uv) * f;		   	// Rule out first screen pixels and flash.
	uv  = step(fract(uv), pixel);				// Add one line of pixels per tile.
	colour = mix(colour, vec3(1.0, 1.0, 0.0), (uv.x + uv.y) * first.x * first.y); // Yellow line
#endif
    
    
    float4 Color; //= Tex.Sample(POINTWRAP, TexPos);
    Color = float4(colour.rgb, 1.0);
    return Color;
}
