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


// �׷���ī�忡�� �̷����°�.
Output TextureCustom_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;

    return NewOutPut;
}

cbuffer SliceData : register(b0)//���� ���ϴ� �ڸ����
{
    float4 SlicePos;
}

Texture2D Tex : register(t0);//�̹���
SamplerState LINEARWRAP : register(s0);//�̹��� �����(��Ʈor��Ƽ)

float4 TextureCustom_PS(Output _Input) : SV_Target0
{
     float2 TexPos = _Input.Tex.xy;

     if (TexPos.x > SlicePos.x)//�����̽� �������� �ؽ������� �۴ٸ� Ŭ��(�̰� ���� ���� ���ν��̴� �������ҵ�
     {
         //���� �����ʿ��� �������� �����
         //<�� �ٲٰ� �ش� �������� ���� 0������ �� +���ָ� ���ʿ��� ���������� �����
         clip(-1);
     }

     float4 Color = Tex.Sample(LINEARWRAP, TexPos);

     return Color;
}