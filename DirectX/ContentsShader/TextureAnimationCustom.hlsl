#include "TransformHeader.fx"

struct Input
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 NORMAL : NORMAL;
    float4 BINORMAL : BINORMAL;
    float4 TANGENT :TANGENT;
    float4 BLENDWEIGHT : BLENDWEIGHT;
    int4 BLENDINDICES : BLENDINDICES;
};

struct Output
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 NORMAL : NORMAL;
    float4 BINORMAL : BINORMAL;
    float4 TANGENT : TANGENT;
};

struct AniMat
{
    float4x4 Mat;
};


cbuffer DiffuseData : register(b0)
{
    float4 TextureColor;
}

// 빛
//cbuffer LightData : register(b0)
//{
//    float4 DiffuseColor;
//    float4 LightDirection;
//}

Texture2D DiffuseTexture : register(t0);
Texture2D NormalTexture : register(t1);
Texture2D FaceEyeMskTexture : register(t2);
Texture2D BodyMskTexture : register(t3);

SamplerState LINEARWRAP : register(s0);

StructuredBuffer<AniMat> ArrAniMationMatrix : register(t11);

void Skinning(inout float4 _Pos, inout float4 _Weight, inout int4 _Index, StructuredBuffer<AniMat> _ArrMatrix)
{
    float4 CalPos = (float4) 0.0f;
    _Pos.w = 1.0f;
    // 1로 맞추려는 행동.
    // _Weight[3] = 1.0f - _Weight[0] - _Weight[1] - _Weight[2];
    
    for (int i = 0; i < 4; ++i)
    {
        AniMat Mat = _ArrMatrix[_Index[i]];
        CalPos += _Weight[i] * mul(_Pos, Mat.Mat);
    }
    
    _Pos = CalPos;
}

Output TextureAnimation_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    
    NewOutPut.POSITION = _Input.POSITION;
    Skinning(NewOutPut.POSITION, _Input.BLENDWEIGHT, _Input.BLENDINDICES, ArrAniMationMatrix);
    NewOutPut.POSITION.w = 1.0f;

    NewOutPut.POSITION = mul(NewOutPut.POSITION, WorldViewProjection);
    NewOutPut.TEXCOORD = _Input.TEXCOORD;
    
    // 노말맵핑 ~
    // 1. 월드 행렬 법선 벡터 계산 + 정규화
    NewOutPut.NORMAL = mul(_Input.NORMAL, WorldWorldMatrix);
    NewOutPut.NORMAL = normalize(NewOutPut.NORMAL);
    
    // 2. 월드 행렬 접선 벡터 계산 + 정규화
    NewOutPut.TANGENT = mul(_Input.TANGENT, WorldWorldMatrix);
    NewOutPut.TANGENT = normalize(NewOutPut.TANGENT);
    
    // 3. 월드 행렬 비 유효 벡터 계산 + 정규화
    NewOutPut.BINORMAL = mul(_Input.BINORMAL, WorldWorldMatrix);
    NewOutPut.BINORMAL = normalize(NewOutPut.BINORMAL);
    
    return NewOutPut;
}



float4 TextureAnimation_PS(Output _Input) : SV_Target0
{
    
    float2 TexPos = _Input.TEXCOORD.xy;
    float3 TexColor = DiffuseTexture.Sample(LINEARWRAP, TexPos);

    // 마스킹
    // 눈
    float3 MaskColor = FaceEyeMskTexture.Sample(LINEARWRAP, TexPos);
    if (MaskColor.r > 0 )
    {
        //TexColor = SkinTexture.Sample(LINEARWRAP, TexPos + float2(0, 0.8));
        TexColor = float3(0, 0, 0);
        
    }
    // 얼굴
    if (MaskColor.g > 0)
    {
        TexColor = float3(1, 1, 1);
    }
    // 몸
    if (MaskColor.b > 0)
    {
        // 결과    음영(DiffuseTex)  +   사용자입력
        TexColor.r = TexColor.r - 1 + TextureColor.r;
        TexColor.g = TexColor.g - 1 + TextureColor.g;
        TexColor.b = TexColor.b - 1 + TextureColor.b;

    }
    
    return float4(TexColor.rgb, 1.0);
}




//// 빛 관련
//float4 LightDir;
//float LightIntensity;

//float4 BumpMap = NormalTexture.Sample(LINEARWRAP, _Input.TEXCOORD.xy);
    
//    // 범프맵 UV좌표계 0 ~ 1 을 -1 ~ 1로 확장
//    BumpMap = (BumpMap * 2.0f) - 1.0f;
    
//    // 범프맵에서 법선 계산
//float4 BumpNormal = (BumpMap.x * _Input.TANGENT) + (BumpMap.y * _Input.BINORMAL) + (BumpMap.z * _Input.NORMAL);
    
//    // 계산 결과 정규화
//    BumpNormal = normalize(BumpNormal);
    
//    // 계산을 위해 빛 방향 반전
//    LightDir = -LightDirection;
    
//    // 범프맵 결과값 기반으로 픽셀의 빛 양 계산
//    LightIntensity = saturate(dot(BumpNormal, LightDir));
    
//    // 확산 색, 광량에 따라 최종 확산 색 결정
//    TexColor = saturate(DiffuseColor * LightIntensity) * TexColor;