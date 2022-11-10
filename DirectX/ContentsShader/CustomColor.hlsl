#include "TransformHeader.fx"
#include "RenderOption.fx"


struct Input
{
    float4 Pos : POSITION;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
};


Output Color_VS(Input _Input)
{
    // 쉐이더의 경우에는 대부분의 상황에서 형변환이 가능하다.
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    
    return NewOutPut;
}

cbuffer AxisData : register(b8)
{
    float4 RenderPos;
    float4 Color;
    bool IsRot;
}

float4 Color_PS(Output _Input) : SV_Target0
{
    if (true == IsRot)
    {
        clip(-1);
    }
    
    return Color;
}
