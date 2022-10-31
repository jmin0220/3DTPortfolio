#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "PickableActor.h"

// 설명 :
class XAxis;
class YAxis;
class ZAxis;
// 축 메쉬
class AxisActor	:	public GameEngineActor
{
public:
	// constrcuter destructer
	AxisActor();
	~AxisActor();

	// delete Function
	AxisActor(const AxisActor& _Other) = delete;
	AxisActor(AxisActor&& _Other) noexcept = delete;
	AxisActor& operator=(const AxisActor& _Other) = delete;
	AxisActor& operator=(AxisActor&& _Other) noexcept = delete;

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

	XAxis* XAxis_;
	YAxis* YAxis_;
	ZAxis* ZAxis_;

public:
	void SetPosition();
};

