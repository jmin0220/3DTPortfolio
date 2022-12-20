// #include "myshader.hlsli"

// SV_POSITION 시맨틱
// 그래픽카드에게 이녀석은 이런 부류니까 니가 자동으로 처리하는 녀석이 있으면 하고.

// t1

// Create("TransformData");
#include "TransformHeader.fx"
#include "LightHeader.fx"
#include "DeferredHeader.fx"

// cbuffer Color : 
// TestColor;
struct Input
{
    float4 Pos : POSITION;
    float4 Normal : NORMAL;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 ViewPos : POSITION;
    float4 ViewNormal : NORMAL;
    float4 Tex : TEXCOORD;
};


//cbuffer ResultColor : register(b2)
//{
//    float4 PlusColor;
//    float4 MultyplyColor;
//}



// 1000
// 0100
// 2010
// 0301

// 1020
// 0103
// 0010
// 0001

Output Color_VS(Input _Input)
{
    // 쉐이더의 경우에는 대부분의 상황에서 형변환이 가능하다.
    Output NewOutPut = (Output)0;
    
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.ViewPos = mul(_Input.Pos, WorldView);
    NewOutPut.Tex = _Input.Tex;
    
    _Input.Normal.w = 0.0f;
    NewOutPut.ViewNormal = normalize(mul(_Input.Normal, WorldView));
    NewOutPut.ViewNormal.w = 0.0f;
    
    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
SamplerState LINEARWRAP : register(s0);
DeferredOutPut Color_PS(Output _Input) : SV_Target0
{
   float4 TexColor = DiffuseTexture.Sample(LINEARWRAP, _Input.Tex.xy);
    
    DeferredOutPut OutPut;
    
    OutPut.Dif = TexColor;
    OutPut.Pos = _Input.ViewPos;
    OutPut.Nor = _Input.ViewNormal;
   // OutPut.Tex = DiffuseTexture.Sample(LINEARWRAP, _Input.Tex.xy);
    OutPut.Nor.w = 1.0f;
    
    
    return OutPut;
}
