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
	// 카메라 암 엑터와 캐릭터를 연결
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

	// 마우스입력
	PosCharacter_ = Character_->GetTransform().GetWorldPosition();

	CameraLookPlayer();
	HorizontalOrbitCamera(_DeltaTime);


}

// 필요없을 예정
void CameraArm::FollowCharacterPosition()
{
	GetTransform().SetWorldPosition(PosCharacter_);
}


void CameraArm::CameraLookPlayer()
{
	//Camera_->GetTransform().SetWorldPosition(PosCameraArm_);

	// 카메라 방향벡터
	float4 Forward = ArmCollision_->GetTransform().GetForwardVector().Normalize3DReturn();

	// 카메라로부터 캐릭터로 향하는 방향벡터
	float4 Target = (PosCharacter_ - ArmCollision_->GetTransform().GetWorldPosition());

	// 내적
	float XAngle = acosf(float4::DotProduct3D(Forward, Target.Normalize3DReturn())) * GameEngineMath::RadianToDegree;

	// 카메라 암의 회전각
	float4 Rot = GetTransform().GetLocalRotation();

	//Camera_->GetTransform().SetWorldRotation({ XAngle, Rot.y, 0 });

}

// 마우스가 화면 가로축 끝에 있으면 입력할 값이 부족한 문제 있음
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

