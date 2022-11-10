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
	std::shared_ptr<GameEngineFBXStaticRenderer> FBXRenderer_;
	std::shared_ptr<GameEngineCollision> Collision_;

	// 카메라 암
	std::shared_ptr<class CameraArm> CameraArm_;

	// 정보
	float4 MoveDir_;

	// 쉐이더 상수버퍼 이용해보기
	float4 TexPivot_;
	float4 FBXLocation_;
	float DragXY[2];
	float LocationXYZ[3];
	void OnGUIFunc();
	std::shared_ptr<CustomableGUI> GUI;
};

