#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class CameraArm : public GameEngineActor
{
public:
	void SetFollowCamera(std::shared_ptr<GameEngineCameraActor> _Camera, std::shared_ptr<GameEngineActor> _Character);
	void SetArmLength(float _Depth, float _Height);
	
	static GameEngineActor* GetCameraArmCamera()
	{
		return CameraArm_;
	}

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
	void End() override;

	void OnEvent() override;
	void OffEvent() override;

private:
	void GetCursurInput();
	void FollowCharacterPosition();
	void CameraLookPlayer();
	void HorizontalOrbitCamera();
	void VerticalOrbitCamera();
	void ZoomInOut();

private:
	std::shared_ptr<GameEngineCameraActor> Camera_;
	std::shared_ptr<GameEngineActor> Character_;

	// ArmVector : ���� ī�޶� �ǹ���ġ
	float4 ArmVector_;
	float ArmRatio_;
	float4 PosCamHolder_;
	float4 PosCharacter_;
	float4 PosHead_;

	// ī�޶� ������Ű�� ��ġ(���� �ε����� �뵵)
	std::shared_ptr<GameEngineCollision> CamHolderCollision_;
	std::shared_ptr<GameEngineCollision> CamAxisX_;
	std::shared_ptr<GameEngineCollision> CamAxisY_;


	// Mouseȸ��
	float4 PrevMousePos_;
	float4 CurMousePos_;
	float PrevMoveLength_;
	float CurMoveLength_;
	float4 MouseMove_;
	float4 ScreenCenterPos_;

	// �����
	void GuIDebugFunc();
	class std::shared_ptr<CustomableGUI> GUI;
	float4 DebugValue;

	// CameraArm �ܺο��� ���� �˰� �ʹ�
	static GameEngineActor* CameraArm_;
};

