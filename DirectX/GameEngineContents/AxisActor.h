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
	std::shared_ptr<GameEngineTextureRenderer> XRenderer;
	std::shared_ptr<GameEngineTextureRenderer> YRenderer;
	std::shared_ptr<GameEngineTextureRenderer> ZRenderer;


	float4 XRendererColor;
	float4 YRendererColor;
	float4 ZRendererColor;

	AxisRotOption XAxisOption;
	AxisRotOption YAxisOption;
	AxisRotOption ZAxisOption;

	std::shared_ptr<XAxis> XAxis_;
	std::shared_ptr<YAxis> YAxis_;
	std::shared_ptr<ZAxis> ZAxis_;

public:
	void SetPosition();
};

