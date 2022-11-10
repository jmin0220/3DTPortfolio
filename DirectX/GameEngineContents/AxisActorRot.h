#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "PickableActor.h"

// 설명 :
class XAxisRot;
class YAxisRot;
class ZAxisRot;
class GlobalValues;
// 축 메쉬
class AxisActorRot : public GameEngineActor
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
	std::shared_ptr<GameEngineTextureRenderer> XRenderer;
	std::shared_ptr<GameEngineTextureRenderer> YRenderer;
	std::shared_ptr<GameEngineTextureRenderer> ZRenderer;

	float4 XResultColor;
	float4 YResultColor;
	float4 ZResultColor;

	std::shared_ptr<XAxisRot> XAxisRot_;
	std::shared_ptr<YAxisRot> YAxisRot_;
	std::shared_ptr<ZAxisRot> ZAxisRot_;

	AxisRotOption Option;

public:
	void SetPosition();
};

