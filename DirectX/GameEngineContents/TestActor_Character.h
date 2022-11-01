#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
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
	// FBX ĳ����
	GameEngineFBXRenderer* FBXRenderer_;

	// ť�� ĳ����
	GameEngineTextureRenderer* BoxRenderer_;
	GameEngineCollision* Collision_;
	float4 BoxColor_;

	// ī�޶� ��
	class CameraArm* CameraArm_;

	// ����
	float4 MoveDir_;

};

