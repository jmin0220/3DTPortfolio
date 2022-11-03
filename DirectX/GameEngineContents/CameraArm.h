#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
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

	// ArmVector : ���� ī�޶� �ǹ���ġ
	float4 ArmVector_;
	float4 PosCamHolder_;
	float4 PosCharacter_;

	// ī�޶� ������Ű�� ��ġ(���� �ε����� �뵵)
	GameEngineCollision* CamHolderCollision_;

	// Mouseȸ��
	float4 PrevMouseInput_;
	float4 CurMouseInput_;
	float4 MouseMove_;

	// �����
	void GuIDebugFunc();
	class CustomableGUI* GUI;
	float4 DebugValue;
};

