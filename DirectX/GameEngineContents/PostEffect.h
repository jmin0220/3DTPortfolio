#pragma once

// Ό³Έν :
class PostEffect : public GameEnginePostEffect
{
public:
	// constrcuter destructer
	PostEffect();
	~PostEffect();

	// delete Function
	PostEffect(const PostEffect& _Other) = delete;
	PostEffect(PostEffect&& _Other) noexcept = delete;
	PostEffect& operator=(const PostEffect& _Other) = delete;
	PostEffect& operator=(PostEffect&& _Other) noexcept = delete;

protected:
	std::shared_ptr<GameEngineRenderTarget> CopyTarget;
	std::shared_ptr<GameEngineRenderUnit> EffectSet;

};

