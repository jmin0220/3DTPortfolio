#include "TransformHeader.fx"
#include "LightHeader.fx"
#include "DeferredHeader.fx"
#include "AnimationHeader.fx"
#include "RenderOption.fx"

struct Input
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 NORMAL : NORMAL;
    float4 TANGENT : TANGENT;
    float4 BINORMAL : BINORMAL;
    float4 BLENDWEIGHT : BLENDWEIGHT;
    int4 BLENDINDICES : BLENDINDICES;
};

struct Output
{
    float4 POSITION : SV_POSITION;
    float4 VIEWPOSITION : POSITION;
    float4 VIEWNORMAL : NORMAL;
    float4 TEXCOORD : TEXCOORD;
    float4 VIEWTANGENT : TANGENT;
    float4 VIEWBINORMAL : BINORMAL;
};


// 그래픽카드에서 이뤄지는것.
Output TextureAnimation_VS(Input _Input)
{
    Output NewOutPut = (Output)0;

    NewOutPut.POSITION = _Input.POSITION;
    Skinning(NewOutPut.POSITION, _Input.BLENDWEIGHT, _Input.BLENDINDICES, ArrAniMationMatrix);
    NewOutPut.POSITION.w = 1.0f;

    //_Input.NORMAL.w = 0.0f;
    //Skinning(_Input.NORMAL, _Input.BLENDWEIGHT, _Input.BLENDINDICES, ArrAniMationMatrix);
    //_Input.NORMAL.w = 0.0f;

    // 자신의 로컬공간에서 애니메이션을 시키고
    // NewOutPut.POSITION = mul(_Input.POSITION, ArrAniMationMatrix[_Input.BLENDINDICES[0]].Mat);
    NewOutPut.POSITION = mul(NewOutPut.POSITION, WorldViewProjection);
    NewOutPut.TEXCOORD = _Input.TEXCOORD;

    NewOutPut.VIEWPOSITION = normalize(mul(_Input.POSITION, WorldView));

    _Input.NORMAL.w = 0.0f;
    NewOutPut.VIEWNORMAL = normalize(mul(_Input.NORMAL, WorldView));
    NewOutPut.VIEWNORMAL.w = 0.0f;

    _Input.TANGENT.w = 0.0f;
    NewOutPut.VIEWTANGENT = normalize(mul(_Input.TANGENT, WorldView));
    NewOutPut.VIEWTANGENT.w = 0.0f;

    _Input.BINORMAL.w = 0.0f;
    NewOutPut.VIEWBINORMAL = normalize(mul(_Input.BINORMAL, WorldView));
    NewOutPut.VIEWBINORMAL.w = 0.0f;

    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
Texture2D NormalTexture : register(t1);
SamplerState LINEARWRAP : register(s0);

DeferredOutPut TextureAnimation_PS(Output _Input) : SV_Target0
{
    float4 Color = DiffuseTexture.Sample(LINEARWRAP, _Input.TEXCOORD.xy);

    if (Color.a <= 0.0f)
    {
        clip(-1);
    }

    DeferredOutPut OutPut;

    OutPut.Dif = Color;
    OutPut.Pos = _Input.VIEWPOSITION;
    OutPut.Nor = _Input.VIEWNORMAL;
    OutPut.Nor.w = 1.0f;

    if (0 != IsNormal)
    {
        OutPut.Nor = BumpNormalCalculate(NormalTexture, LINEARWRAP, _Input.TEXCOORD, _Input.VIEWTANGENT, _Input.VIEWBINORMAL, _Input.VIEWNORMAL);
        OutPut.Nor.w = 1.0f;
    }

    return OutPut;
}
