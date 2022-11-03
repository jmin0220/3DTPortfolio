#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class CameraArm : public GameEngineActor
{
public:
	void SetFollowCamera(GameEngineCameraActor* _Camera, GameEngineActor* _Character);
	void SetArmLength(float _Depth, float _Height);

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

	void OnEvent() override;
	void OffEvent() override;

private:
	void FollowCharacterPosition();
	void CameraLookPlayer();
	void HorizontalOrbitCamera();
	void VerticalOrbitCamera();

private:
	GameEngineCameraActor* Camera_;
	GameEngineActor* Character_;

	// ArmVector : 최초 카메라 피벗위치
	float4 ArmVector_;
	float4 PosCamHolder_;
	float4 PosCharacter_;

	// 카메라를 고정시키는 위치(벽에 부딪히는 용도)
	GameEngineCollision* CamHolderCollision_;

	// Mouse회전
	float4 PrevMouseInput_;
	float4 CurMouseInput_;
	float4 MouseMove_;

	// 디버깅
	void GuIDebugFunc();
	class CustomableGUI* GUI;
	float4 DebugValue;
};

