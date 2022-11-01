#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class CameraArm : public GameEngineActor
{
public:
	void SetFollowCamera(GameEngineCameraActor* _Camera, GameEngineActor* _Character);

public:
	// constrcuter destructer
	CameraArm();
	~CameraArm();

	// delete Function
	CameraArm(const CameraArm& _Other) = delete;
	CameraArm(CameraArm&& _Other) noexcept = delete;
	CameraArm& operator=(const CameraArm& _Other) = delete;
	CameraArm& operator=(CameraArm&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	void FollowCharacterPosition();
	void CameraLookPlayer();
	void HorizontalOrbitCamera(float _DeltaTime);
	void VerticalOrbitCamera();

private:
	GameEngineCameraActor* Camera_;
	GameEngineActor* Character_;

	// ArmVector : 최초 카메라 피벗위치
	float4 ArmVector_;
	float4 PosCameraArm_;
	float4 PosCharacter_;

	// 카메라를 고정시키는 위치(벽에 부딪히는 용도)
	GameEngineCollision* ArmCollision_;

	// Mouse회전
	float4 PrevMouseInput;
	float4 CurMouseInput;
};

