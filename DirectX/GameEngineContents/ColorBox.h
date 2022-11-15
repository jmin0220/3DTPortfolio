#pragma once
#include "PickableActor.h"

// Ό³Έν :
class ColorBox : public GameEngineActor
{
public:
	// constrcuter destructer
	ColorBox();
	~ColorBox();

	// delete Function
	ColorBox(const ColorBox& _Other) = delete;
	ColorBox(ColorBox&& _Other) noexcept = delete;
	ColorBox& operator=(const ColorBox& _Other) = delete;
	ColorBox& operator=(ColorBox&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	std::shared_ptr<GameEngineTextureRenderer> Renderer;
	std::shared_ptr<GameEngineCollision> Collision;
	float4 ResultColor;

};

