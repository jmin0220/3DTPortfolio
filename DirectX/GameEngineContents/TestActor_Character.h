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
	std::shared_ptr<GameEngineFBXStaticRenderer> FBXRenderer_;
	std::shared_ptr<GameEngineCollision> Collision_;

	// ī�޶� ��
	std::shared_ptr<class CameraArm> CameraArm_;

	// ����
	float4 MoveDir_;

	// ���̴� ������� �̿��غ���
	float4 TexPivot_;
	float4 FBXLocation_;
	float DragXY[2];
	float LocationXYZ[3];
	void OnGUIFunc();
	std::shared_ptr<CustomableGUI> GUI;
};

