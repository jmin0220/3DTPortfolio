#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
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

	// ArmVector : ���� ī�޶� �ǹ���ġ
	float4 ArmVector_;
	float4 PosCameraArm_;
	float4 PosCharacter_;

	// ī�޶� ������Ű�� ��ġ(���� �ε����� �뵵)
	GameEngineCollision* ArmCollision_;

	// Mouseȸ��
	float4 PrevMouseInput;
	float4 CurMouseInput;
};

