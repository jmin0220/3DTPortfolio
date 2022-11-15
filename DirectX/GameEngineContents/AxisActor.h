#pragma once
#include "PickableActor.h"

// √‡ ∏ﬁΩ¨
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

private:

	float4 XRendererColor;
	float4 YRendererColor;
	float4 ZRendererColor;

	//AxisRotOption XAxisOption;
	//AxisRotOption YAxisOption;
	//AxisRotOption ZAxisOption;

	std::shared_ptr<GameEngineTextureRenderer> XRenderer_;
	std::shared_ptr<GameEngineTextureRenderer> YRenderer_;
	std::shared_ptr<GameEngineTextureRenderer> ZRenderer_;

	std::shared_ptr<class PickableActor> XAxis_;
	std::shared_ptr<class PickableActor> YAxis_;
	std::shared_ptr<class PickableActor> ZAxis_;

public:
	void SetPosition();
};

