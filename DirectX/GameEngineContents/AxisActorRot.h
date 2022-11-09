#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "PickableActor.h"




// 설명 :
class XAxisRot;
class YAxisRot;
class ZAxisRot;
class GlobalValues;
// 축 메쉬
class AxisActorRot :	public GameEngineActor
{
public:
	// constrcuter destructer
	AxisActorRot();
	~AxisActorRot();

	// delete Function
	AxisActorRot(const AxisActorRot& _Other) = delete;
	AxisActorRot(AxisActorRot&& _Other) noexcept = delete;
	AxisActorRot& operator=(const AxisActorRot& _Other) = delete;
	AxisActorRot& operator=(AxisActorRot&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	//void End() override;


private:
	GameEngineTextureRenderer* XRenderer;
	GameEngineTextureRenderer* YRenderer;
	GameEngineTextureRenderer* ZRenderer;

	float4 XResultColor;
	float4 YResultColor;
	float4 ZResultColor;

	XAxisRot* XAxisRot_;
	YAxisRot* YAxisRot_;
	ZAxisRot* ZAxisRot_;

	RenderOption Option;

public:
	void SetPosition();
};

