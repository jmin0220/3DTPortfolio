#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "PickableActor.h"

// ���� :
class XAxisRot;
class YAxisRot;
class ZAxisRot;
class GlobalValues;
// �� �޽�
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
	std::shared_ptr<GameEngineTextureRenderer> XRenderer_;
	std::shared_ptr<GameEngineTextureRenderer> YRenderer_;
	std::shared_ptr<GameEngineTextureRenderer> ZRenderer_;

	float4 XResultColor;
	float4 YResultColor;
	float4 ZResultColor;

	std::shared_ptr<PickableActor> XAxisRot_;
	std::shared_ptr<PickableActor> YAxisRot_;
	std::shared_ptr<PickableActor> ZAxisRot_;

	//AxisRotOption Option;

public:
	void SetPosition();
};

