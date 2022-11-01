#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PhysXTestBox : public GameEngineActor
{
public:
	// constrcuter destructer
	PhysXTestBox();
	~PhysXTestBox();

	// delete Function
	PhysXTestBox(const PhysXTestBox& _Other) = delete;
	PhysXTestBox(PhysXTestBox&& _Other) noexcept = delete;
	PhysXTestBox& operator=(const PhysXTestBox& _Other) = delete;
	PhysXTestBox& operator=(PhysXTestBox&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineTextureRenderer* Renderer;
	float4 ResultColor;

};

