#pragma once
#include "PickableActor.h"

// ���� :
class ColorBox : public PickableActor
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
	GameEngineTextureRenderer* Renderer;
	GameEngineCollision* Collision;
	float4 ResultColor;

};

