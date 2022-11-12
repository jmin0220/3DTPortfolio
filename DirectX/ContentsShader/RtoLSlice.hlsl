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

cbuffer SliceData : register(b0)//내가 원하는 자르기용
{
    float4 SlicePos;
}

Texture2D Tex : register(t0);//이미지
SamplerState LINEARWRAP : register(s0);//이미지 송출법(도트or안티)

float4 TextureCustom_PS(Output _Input) : SV_Target0
{
     float2 TexPos = _Input.Tex.xy;

     if (TexPos.x > SlicePos.x)//슬라이스 포스보다 텍스포스가 작다면 클립(이거 따로 빼서 따로쉐이더 만들어야할듯
     {
         //현재 오른쪽에서 왼쪽으로 사라짐
         //<로 바꾸고 해당 렌더러에 포스 0으로한 후 +해주면 왼쪽에서 오른쪽으로 사라짐
         clip(-1);
     }

     float4 Color = Tex.Sample(LINEARWRAP, TexPos);

     return Color;
}