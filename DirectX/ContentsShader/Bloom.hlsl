struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};


struct Output
{
    float4 Pos : SV_POSITION;
    float4 Tex : TEXCOORD;
};


Output Bloom_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}

#define ColorRange 2.5 // -> 상수버퍼로 하는게 좋을거같음

Texture2D Tex : register(t0);
SamplerState POINTWRAP : register(s0);

float3 JodieReinhardTonemap(float3 c)
{
    float l = dot(c, float3(0.2126, 0.7152, 0.0722));
    float3 tc = c / (c + 1.0);

    return lerp(c / (l + 1.0), tc, tc);
}

float3 BloomTile(float lod, float2 offset, float2 uv)
{
    return Tex.Sample(POINTWRAP, uv * exp2(-lod) + offset).rgb;
}

float3 GetBloom(float2 uv)
{
    float3 blur = float3(0.0, 0.0, 0.0);
    
    blur = pow(BloomTile(2.0, float2(0.0, 0.0), uv), float3(2.2, 2.2, 2.2)) + blur;
    blur = pow(BloomTile(3.0, float2(0.3, 0.0), uv), float3(2.2, 2.2, 2.2)) * 1.3 + blur;
    blur = pow(BloomTile(4.0, float2(0.0, 0.3), uv), float3(2.2, 2.2, 2.2)) * 1.6 + blur;
    blur = pow(BloomTile(5.0, float2(0.1, 0.3), uv), float3(2.2, 2.2, 2.2)) * 1.9 + blur;
    blur = pow(BloomTile(6.0, float2(0.2, 0.3), uv), float3(2.2, 2.2, 2.2)) * 2.2 + blur;
    
    return blur * ColorRange;
}

float4 Bloom_PS(Output _Input) : SV_Target0
{
    float2 TexPos = _Input.Tex.xy;
    float3 Color = pow(Tex.Sample(POINTWRAP, TexPos).rgb * ColorRange, float3(2.2, 2.2, 2.2));

    Color = pow(Color, float3(2.2, 2.2, 2.2));
    Color += pow(GetBloom(TexPos), float3(2.2, 2.2, 2.2));
    Color = pow(Color, float3(1.0 / 2.2, 1.0 / 2.2, 1.0 / 2.2));
    
    Color = JodieReinhardTonemap(Color);
    
    return float4(Color.rgb, 1.0);
}
