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
    // ���̴��� ��쿡�� ��κ��� ��Ȳ���� ����ȯ�� �����ϴ�.
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
