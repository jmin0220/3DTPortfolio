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

	// DEBUG GUI사용
	GUI = GameEngineGUI::CreateGUIWindow<CustomableGUI>("CustomableGUI", nullptr);
	GUI->On();
	GUI->SetGUIDebugFunc([=]() {GuIDebugFunc(); });
}

void CameraArm::SetFollowCamera(GameEngineCameraActor* _Camera, GameEngineActor* _Character)
{
	// 카메라 암 엑터와 캐릭터를 연결
	SetParent(_Character);

	Camera_ = _Camera;
	Character_ = _Character;
	ArmVector_ = float4(0, 600, -2000);

	ArmCollision_->GetTransform().SetLocalPosition(ArmVector_);
}

void CameraArm::SetArmLength(float _Depth, float _Height)
{
	ArmVector_ = float4(0, _Height, _Depth);
}

void CameraArm::Update(float _DeltaTime)
{
	if (nullptr == Camera_ || nullptr == Character_)
	{
		return;
	}

	// 마우스입력
	CurMouseInput_ = Camera_->GetCameraComponent()->GetMouseScreenPosition();
	MouseMove_ = CurMouseInput_ - PrevMouseInput_;

	PosCameraArm_ = ArmCollision_->GetTransform().GetWorldPosition();
	PosCharacter_ = Character_->GetTransform().GetWorldPosition();

	PosCharacter_ = Character_->GetTransform().GetWorldPosition();

	CameraLookPlayer();
	HorizontalOrbitCamera();
	VerticalOrbitCamera();

	// 마우스 입력
	PrevMouseInput_ = CurMouseInput_;
}

// 필요없을 예정
void CameraArm::FollowCharacterPosition()
{
	GetTransform().SetWorldPosition(PosCharacter_);
}


void CameraArm::CameraLookPlayer()
{
	Camera_->GetTransform().SetWorldPosition(PosCameraArm_);

	// 카메라 방향벡터
	float4 Forward = ArmCollision_->GetTransform().GetForwardVector().Normalize3DReturn();

	// 카메라로부터 캐릭터로 향하는 방향벡터
	float4 Target = (PosCharacter_ - ArmCollision_->GetTransform().GetWorldPosition());


	// 디버깅용
	{
		DebugValue = acosf(float4::DotProduct3D(Forward, Target.Normalize3DReturn())) * GameEngineMath::RadianToDegree;
	}

	// 내적
	float XAngle = acosf(float4::DotProduct3D(Forward, Target.Normalize3DReturn())) * GameEngineMath::RadianToDegree;

	// 카메라 암의 회전각
	float4 Rot = GetTransform().GetLocalRotation();

	Camera_->GetTransform().SetWorldRotation({ XAngle, Rot.y, 0 });

}

// Y축 돌리기
void CameraArm::HorizontalOrbitCamera()
{

	GetTransform().SetAddWorldRotation({ 0, MouseMove_.x, 0 });
}

// X축 돌리기
void CameraArm::VerticalOrbitCamera()
{
	ArmCollision_->GetTransform().SetLocalMove({ 0, MouseMove_.y, 0 });
	
}


// DEBUG GUI
void CameraArm::GuIDebugFunc()
{
	if (true == ImGui::Button("FreeCameaOnOff"))
	{
		GetLevel()->GetMainCameraActor()->FreeCameraModeOnOff();
	}

	ImGui::SameLine();
	if (true == ImGui::Button("CollisionDebugSwtich"))
	{
		GEngine::CollisionDebugSwitch();
	}

	{
		float4 Pos = DebugValue;
		std::string Name = "TargetDegree : " + std::to_string(Pos.x) + " | " + std::to_string(Pos.y) + " | " + std::to_string(Pos.z) + " | " + std::to_string(Pos.w);
		ImGui::Text(Name.c_str());
	}
}