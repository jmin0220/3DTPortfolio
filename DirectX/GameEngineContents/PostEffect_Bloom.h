#pragma once
#include "PostEffect.h"

class PostEffect_Bloom : public PostEffect
{
public:
	// constrcuter destructer
	PostEffect_Bloom();
	~PostEffect_Bloom();

	// delete Function
	PostEffect_Bloom(const PostEffect_Bloom& _Other) = delete;
	PostEffect_Bloom(PostEffect_Bloom&& _Other) noexcept = delete;
	PostEffect_Bloom& operator=(const PostEffect_Bloom& _Other) = delete;
	PostEffect_Bloom& operator=(PostEffect_Bloom&& _Other) noexcept = delete;

	virtual void EffectInit() override;
	virtual void Effect(std::shared_ptr<GameEngineRenderTarget> _Target) override;

private:

};

