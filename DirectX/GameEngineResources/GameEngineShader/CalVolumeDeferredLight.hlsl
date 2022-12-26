#include "TransformHeader.fx"
#include "LightHeader.fx"

// SV_POSITION 시맨틱
// 그래픽카드에게 이녀석은 이런 부류니까 니가 자동으로 처리하는 녀석이 있으면 하고.


struct Input
{
    float4 Pos : POSITION;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 UvPos : POSITION;
};


// 그래픽카드에서 이뤄지는것.
Output CalDeferredLight_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.UvPos = NewOutPut.Pos;
    return NewOutPut;
}

// 디렉션 라이트에는 볼륨이 필요없습니다.
// 포인트 라이트랑 스폿라이트같은 

Texture2D PositionTex : register(t0);
Texture2D NormalTex : register(t1);
Texture2D ShadowTex : register(t2);
SamplerState POINTWRAP : register(s0);
SamplerState LINEARWRAP : register(s1);

struct LightOutPut
{
    float4 DifLight : SV_Target0;
    float4 SpcLight : SV_Target1;
    float4 AmbLight : SV_Target2;
};

LightOutPut CalDeferredLight_PS(Output _Input)
{
    //                    -1        1               
    float2 UV = float2(_Input.UvPos.x / _Input.UvPos.w, _Input.UvPos.y / _Input.UvPos.w);
    
    //             0~1
    UV = float2(UV.x * 0.5f + 0.5f, UV.y * -0.5f + 0.5f);
    
    float4 Position = PositionTex.Sample(POINTWRAP, UV);
    float4 Normal = NormalTex.Sample(POINTWRAP, UV);
    
    if (Position.a <= 0.0f)
    {
        clip(-1);
    }
    
    Normal.w = 0.0f;
    
    LightOutPut Out = (LightOutPut) 0.0f;
    
    Out.DifLight = CalDiffuseLights(Position, Normal);
    Out.SpcLight = CalSpacularLight(Position, Normal);
    Out.AmbLight = CalAmbientLight();
    
    int Count = 0;
    
        if (Out.DifLight.x > 0.0f)
        {
            // 카메라의 view에서 왔죠 ViewPosition
            // 빛의 view 카메라의 view공간은 둘다.
            // 둘다 각자의 view공간에 있습니다.
            // 서로의 view의 역행렬을 곱해줘야.
            // 월드 -> 뷰 -> 프로젝션 -> 뷰포트(SV_POSTION)
            
            // Position 월드 * 카메라view
            
            // ViewPosition카메라 공간에 있기 때문에 카메라의 역행렬을 얻어와야 한다.
            float4 WorldPosition = mul(float4(Position.xyz, 1.0f), Lights[0].CameraViewInverseMatrix);
            
            // WorldPosition 카메라의 공간ㅇ => 빛의 투영으로 끌어들여야 합니다.
            float4 LightPos = mul(WorldPosition, Lights[0].LightViewProjectionMatrix);
            
            float fDepth = LightPos.z / LightPos.w; // 0 ~ 1 
            float fUvX = LightPos.x / LightPos.w; // -1 1
            float fUvY = LightPos.y / LightPos.w; // -1 1
            
            // fUvX -1 1
            // fUvY -1 1
            // ShaodwPos
            
            // 그림자를 가져오기 위한 uv값
            float2 ShadowUv = float2(fUvX * 0.5f + 0.5f, fUvY * -0.5f + 0.5f);
            
            // UV공간 외부라면 굳이 가져오지 않는다.
            if (
                0.001f < ShadowUv.x && 0.999f > ShadowUv.x &&
                0.001f < ShadowUv.y && 0.999f > ShadowUv.y
                )
            {
                // Texture2DArray.Sample
                
                float fShadowDepth = ShadowTex.Sample(LINEARWRAP, float2(ShadowUv.x, ShadowUv.y)).r;
                
                if (0.0f < fShadowDepth && fDepth > fShadowDepth + 0.001f)
                {
                    Out.DifLight = 0.01f;
                    Out.SpcLight = 0.01f;
                }
            }
        }
    
    return Out;
}