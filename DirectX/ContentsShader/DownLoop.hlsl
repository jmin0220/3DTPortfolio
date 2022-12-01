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

cbuffer SliceData : register(b0)//이거 따로 뺴야함
{
    float4 SlicePos;
}

Texture2D Tex : register(t0);//무늬 움직이기 쉐이더
Texture2D Mask : register(t1);//마스킹 쉐이더
SamplerState LINEARWRAP : register(s0);

float4 TextureCustom_PS(Output _Input) : SV_Target0
{
    float2 TexPos = _Input.Tex.xy;

    float4 MaskColor = Mask.Sample(LINEARWRAP, TexPos);//마스크 이미지의 범위(sample)를 가져온다

    if (TexPos.x > SlicePos.x)//슬라이스 포스보다 텍스포스가 작다면 클립(이거 따로 빼서 따로쉐이더 만들어야할듯
    {
        //현재 오른쪽에서 왼쪽으로 사라짐
        //<로 바꾸고 해당 렌더러에 포스 0으로한 후 +해주면 왼쪽에서 오른쪽으로 사라짐
        clip(-1);
    }

    if (MaskColor.a != 1)//알파가1이 아니라면 클립
    {
        clip(-1);
    }

    TexPos.y += SumDeltaTime;//sum델타에 따라 움직인다(미러 적용되 있음)

    float4 Color = Tex.Sample(LINEARWRAP, TexPos);

    return Color;
}