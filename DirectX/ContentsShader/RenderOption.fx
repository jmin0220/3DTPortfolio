cbuffer RenderOption : register(b10)
{
    float DeltaTime;
    float SumDeltaTime;
    int IsAnimation;
    int IsNormal;
};

float4 BumpNormalCalculate(Texture2D NormalTex, SamplerState Smp, float4 UV, float4 _Tangent, float4 _BiNormal, float4 _Normal)
{
    float4 TexNormal = NormalTex.Sample(Smp, UV.xy);
    TexNormal = TexNormal * 2.0f - 1.0f;
    TexNormal.w = 0.0f;
    TexNormal = normalize(TexNormal);

    float4 Result = (float4) 0.0f;
    float3x3 TangentSpace = float3x3(_Tangent.xyz, _BiNormal.xyz, _Normal.xyz);
    // TangentSpace  = transpose(TangentSpace);
    Result.xyz = mul(TexNormal.xyz, TangentSpace);

    return Result;

}