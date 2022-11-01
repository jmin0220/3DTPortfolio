#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class TestActor_Character : public GameEngineActor
{
public:
	// constrcuter destructer
	TestActor_Character();
	~TestActor_Character();

	// delete Function
	TestActor_Character(const TestActor_Character& _Other) = delete;
	TestActor_Character(TestActor_Character&& _Other) noexcept = delete;
	TestActor_Character& operator=(const TestActor_Character& _Other) = delete;
	TestActor_Character& operator=(TestActor_Character&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void PlayerInputController();
	void ApplyGravity();
	void RotateCharacterForward();

private:
	// FBX 캐릭터
	GameEngineFBXRenderer* FBXRenderer_;

	// 큐브 캐릭터
	GameEngineTextureRenderer* BoxRenderer_;
	GameEngineCollision* Collision_;
	float4 BoxColor_;

	// 카메라 암
	class CameraArm* CameraArm_;

	// 정보
	float4 MoveDir_;

};

