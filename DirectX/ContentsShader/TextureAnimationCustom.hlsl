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

// ��
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
    // 1�� ���߷��� �ൿ.
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
    
    // �븻���� ~
    // 1. ���� ��� ���� ���� ��� + ����ȭ
    NewOutPut.NORMAL = mul(_Input.NORMAL, WorldWorldMatrix);
    NewOutPut.NORMAL = normalize(NewOutPut.NORMAL);
    
    // 2. ���� ��� ���� ���� ��� + ����ȭ
    NewOutPut.TANGENT = mul(_Input.TANGENT, WorldWorldMatrix);
    NewOutPut.TANGENT = normalize(NewOutPut.TANGENT);
    
    // 3. ���� ��� �� ��ȿ ���� ��� + ����ȭ
    NewOutPut.BINORMAL = mul(_Input.BINORMAL, WorldWorldMatrix);
    NewOutPut.BINORMAL = normalize(NewOutPut.BINORMAL);
    
    return NewOutPut;
}



float4 TextureAnimation_PS(Output _Input) : SV_Target0
{
    
    float2 TexPos = _Input.TEXCOORD.xy;
    float3 TexColor = DiffuseTexture.Sample(LINEARWRAP, TexPos);

    // ����ŷ
    // ��
    float3 MaskColor = FaceEyeMskTexture.Sample(LINEARWRAP, TexPos);
    if (MaskColor.r > 0 )
    {
        //TexColor = SkinTexture.Sample(LINEARWRAP, TexPos + float2(0, 0.8));
        TexColor = float3(0, 0, 0);
        
    }
    // ��
    if (MaskColor.g > 0)
    {
        TexColor = float3(1, 1, 1);
    }
    // ��
    if (MaskColor.b > 0)
    {
        // ���    ����(DiffuseTex)  +   ������Է�
        TexColor.r = TexColor.r - 1 + TextureColor.r;
        TexColor.g = TexColor.g - 1 + TextureColor.g;
        TexColor.b = TexColor.b - 1 + TextureColor.b;

    }
    
    return float4(TexColor.rgb, 1.0);
}




//// �� ����
//float4 LightDir;
//float LightIntensity;

//float4 BumpMap = NormalTexture.Sample(LINEARWRAP, _Input.TEXCOORD.xy);
    
//    // ������ UV��ǥ�� 0 ~ 1 �� -1 ~ 1�� Ȯ��
//    BumpMap = (BumpMap * 2.0f) - 1.0f;
    
//    // �����ʿ��� ���� ���
//float4 BumpNormal = (BumpMap.x * _Input.TANGENT) + (BumpMap.y * _Input.BINORMAL) + (BumpMap.z * _Input.NORMAL);
    
//    // ��� ��� ����ȭ
//    BumpNormal = normalize(BumpNormal);
    
//    // ����� ���� �� ���� ����
//    LightDir = -LightDirection;
    
//    // ������ ����� ������� �ȼ��� �� �� ���
//    LightIntensity = saturate(dot(BumpNormal, LightDir));
    
//    // Ȯ�� ��, ������ ���� ���� Ȯ�� �� ����
//    TexColor = saturate(DiffuseColor * LightIntensity) * TexColor;