#include "PreCompile.h"
#include "CameraArm.h"


CameraArm::CameraArm()
	: Camera_(nullptr)
	, Character_(nullptr)
{
}

CameraArm::~CameraArm() 
{
}

void CameraArm::Start()
{
	ArmCollision_ = CreateComponent<GameEngineCollision>();
	ArmCollision_->GetTransform().SetWorldScale({ 50, 50, 200 });
	ArmCollision_->SetDebugSetting(CollisionType::CT_OBB, float4(0.0f, 0.0f, 0.8f, 0.5f));
}

void CameraArm::SetFollowCamera(GameEngineCameraActor* _Camera, GameEngineActor* _Character)
{
	// ī�޶� �� ���Ϳ� ĳ���͸� ����
	SetParent(_Character);

	Camera_ = _Camera;
	Character_ = _Character;
	ArmVector_ = float4(0, 200, -1000);

	ArmCollision_->GetTransform().SetLocalPosition(ArmVector_);
}

void CameraArm::Update(float _DeltaTime)
{
	if (nullptr == Camera_ || nullptr == Character_)
	{
		return;
	}

	PosCameraArm_ = ArmCollision_->GetTransform().GetWorldPosition();
	PosCharacter_ = Character_->GetTransform().GetWorldPosition();

	// ���콺�Է�
	PosCharacter_ = Character_->GetTransform().GetWorldPosition();

	CameraLookPlayer();
	HorizontalOrbitCamera(_DeltaTime);


}

// �ʿ���� ����
void CameraArm::FollowCharacterPosition()
{
	GetTransform().SetWorldPosition(PosCharacter_);
}


void CameraArm::CameraLookPlayer()
{
	//Camera_->GetTransform().SetWorldPosition(PosCameraArm_);

	// ī�޶� ���⺤��
	float4 Forward = ArmCollision_->GetTransform().GetForwardVector().Normalize3DReturn();

	// ī�޶�κ��� ĳ���ͷ� ���ϴ� ���⺤��
	float4 Target = (PosCharacter_ - ArmCollision_->GetTransform().GetWorldPosition());

	// ����
	float XAngle = acosf(float4::DotProduct3D(Forward, Target.Normalize3DReturn())) * GameEngineMath::RadianToDegree;

	// ī�޶� ���� ȸ����
	float4 Rot = GetTransform().GetLocalRotation();

	//Camera_->GetTransform().SetWorldRotation({ XAngle, Rot.y, 0 });

}

// ���콺�� ȭ�� ������ ���� ������ �Է��� ���� ������ ���� ����
void CameraArm::HorizontalOrbitCamera(float _DeltaTime)
{
	CurMouseInput = Camera_->GetCameraComponent()->GetMouseScreenPosition();
	
	float Rot = CurMouseInput.x - PrevMouseInput.x;
	GetTransform().SetLocalRotate({ 0, Rot, 0 });

	PrevMouseInput = CurMouseInput;
}

void CameraArm::VerticalOrbitCamera()
{
}

