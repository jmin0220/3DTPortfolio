#include "PreCompile.h"
#include "CameraArm.h"

// 카메라 움직임 속도
float SPEED_CAM_X = 1.0f;
float SPEED_CAM_Y = 1.0f;

const float4 DEFAULT_ARMVEC(0, 4.2f, -4.5f);
const float4 DEFAULT_POSHEAD(0, 8.0f, 0);

const float4 SIZE_MENUBAR(8, 31, 0); // 마우스를 화면 가운데로 고정하기 위한 오차
//const float4 SIZE_MENUBAR(0, 0, 0); // 마우스를 화면 가운데로 고정하기 위한 오차

CameraArm::CameraArm()
	: Camera_(nullptr)
	, Character_(nullptr)
	, ArmRatio_(1.0f)
{
}

CameraArm::~CameraArm() 
{
}

void CameraArm::Start()
{

	// 자이로스코프
	CamHolderCollision_ = CreateComponent<GameEngineCollision>();
	CamAxisX_ = CreateComponent<GameEngineCollision>();
	CamAxisY_ = CreateComponent<GameEngineCollision>();

	CamHolderCollision_->SetParent(std::dynamic_pointer_cast<GameEngineUpdateObject>(CamAxisX_));
	CamAxisX_->SetParent(CamAxisY_);
	CamAxisY_->SetParent(shared_from_this());

	CamAxisY_->GetTransform().SetWorldScale({ 10, 10, 10 });
	CamAxisY_->SetDebugSetting(CollisionType::CT_OBB, float4(0, 1.0f, 0, 0.2f));

	CamAxisX_->GetTransform().SetWorldScale({ 10, 10, 10 });
	CamAxisX_->SetDebugSetting(CollisionType::CT_OBB, float4(1.0f, 0, 0, 0.4f));

	CamHolderCollision_->GetTransform().SetWorldScale({ 2, 2, 5 });
	CamHolderCollision_->SetDebugSetting(CollisionType::CT_OBB, float4(0.8f, 0.8f, 0.8f, 0.5f));

	// DEBUG GUI사용
	GUI = GameEngineGUI::CreateGUIWindow<CustomableGUI>("CustomableGUI", nullptr);
	GUI->SetGUIDebugFunc([=]() {GuIDebugFunc(); });
	GUI->Off();

}

void CameraArm::SetFollowCamera(std::shared_ptr<GameEngineCameraActor> _Camera, std::shared_ptr<GameEngineActor> _Character)
{
	// 카메라 암 엑터와 캐릭터를 연결
	Camera_ = _Camera;
	
	// 카메라암은 프리카메라 모드 아님
	Camera_->OffFreeCameraMode();

	GetTransform().SetWorldPosition(_Character->GetTransform().GetWorldPosition());
	
	Character_ = _Character;
	//SetParent(_Character);

	// 카메라 암 피벗 정도
	ArmVector_ = DEFAULT_ARMVEC * ArmRatio_;

	// 캐릭터보다 조금 위를 바라본다
	PosHead_ = DEFAULT_POSHEAD;


	// 마우스 게임중일 때 화면 가운데 위치를 유지
	ScreenCenterPos_ = GameEngineWindow::GetScale() / 2.0f;
	PrevMousePos_ = ScreenCenterPos_;
	SetCursorPos(ScreenCenterPos_.ix(), ScreenCenterPos_.iy());

	Camera_->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
	if (true == Camera_->IsFreeCameraMode())
	{
		Camera_->FreeCameraModeOnOff();
	}
	Camera_->GetTransform().SetWorldPosition(PosCamHolder_);
	CamHolderCollision_->GetTransform().SetLocalPosition(ArmVector_ * ArmRatio_);

}

void CameraArm::SetArmLength(float _Depth, float _Height)
{
	ArmVector_ = float4(0, _Height, _Depth);
}

void CameraArm::Update(float _DeltaTime)
{
	if (nullptr == Character_)
	{
		return;
	}

	// 카메라암은 플레이어를 따라다닌다
	GetTransform().SetWorldPosition(Character_->GetTransform().GetWorldPosition());

	if (false == GameEngineWindow::GetInst()->IsMouseCurApp())
	{
		return;
	}

	if (true == Camera_->IsFreeCameraMode())
	{
		return;
	}



	ZoomInOut();

	GetCursurInput();

	// 카메라 홀더 위치 받음
	PosCamHolder_ = CamHolderCollision_->GetTransform().GetWorldPosition();
	PosCharacter_ = GetTransform().GetWorldPosition();

	// 카메라 홀더 위치에 카메라 따라가도록
	Camera_->GetTransform().SetWorldPosition(PosCamHolder_);
	DebugValue = PosCamHolder_;

	// 카메라가 플레이어를 바라보도록 각도계산
	CameraLookPlayer();

	// 마우스 수직/수평 입력
	VerticalOrbitCamera();
	HorizontalOrbitCamera();

}

void CameraArm::End()
{
}

void CameraArm::OnEvent()
{
	GUI->On();
}

void CameraArm::OffEvent()
{
	GUI->Off();
}

// 마우스 커서 화면 중심으로 고정
void CameraArm::GetCursurInput()
{
	// 커서, 화면 중심으로부터 멀어지면 움직이고, 중심으로 되돌아가는거면 안움직이는 방식
	CurMousePos_ = Camera_->GetCameraComponent()->GetMouseScreenPosition();

	float4 MouseDelta = CurMousePos_ - ScreenCenterPos_ + SIZE_MENUBAR;
	MouseMove_.x = abs(MouseDelta.x) > 0.01f ? MouseDelta.x : 0.0f;
	MouseMove_.y = abs(MouseDelta.y) > 0.01f ? MouseDelta.y : 0.0f;

	SetCursorPos(ScreenCenterPos_.ix(), ScreenCenterPos_.iy());
	CurMousePos_ = ScreenCenterPos_;
}

// 필요없을 예정
void CameraArm::FollowCharacterPosition()
{
	GetTransform().SetWorldPosition(PosCharacter_);
}


void CameraArm::CameraLookPlayer()
{
	Camera_->GetTransform().SetWorldRotation(CamHolderCollision_->GetTransform().GetWorldRotation());

	// 카메라 방향벡터
	float4 Forward = Camera_->GetTransform().GetForwardVector().Normalize3DReturn();

	// 카메라로부터 캐릭터로 향하는 방향벡터
	float4 Target = ((PosCharacter_ + PosHead_) - PosCamHolder_).Normalize3DReturn();

	// 내적
	float Angle = acosf(float4::DotProduct3D(Forward, Target)) * GameEngineMath::RadianToDegree;

	Camera_->GetTransform().SetAddWorldRotation({ Angle, 0, 0 });

}

// 마우스 가로 움직임
void CameraArm::HorizontalOrbitCamera()
{
	CamAxisY_->GetTransform().SetAddWorldRotation({ 0,  MouseMove_.x * SPEED_CAM_X, 0 });
}

// 마우스 세로 움직임
void CameraArm::VerticalOrbitCamera()
{
	// 카메라 떨림 현상 제거 -> Clamp
	float Rot = CamAxisX_->GetTransform().GetLocalRotation().x + MouseMove_.y * SPEED_CAM_Y;
	float ClampRot = std::clamp(Rot, -30.0f, 30.0f);

	CamAxisX_->GetTransform().SetLocalRotation({ ClampRot, 0, 0 });
}

void CameraArm::ZoomInOut()
{
	// 카메라 암 갱신
	int Wheel = GameEngineInput::GetInst()->GetMouseWheel();
	
	if (Wheel == 0)
	{
		return;
	}

	if (Wheel < 0)
	{
		ArmRatio_ *= 1.1f;
	}
	else if (Wheel > 0)
	{
		ArmRatio_ *= 0.9f;
	}

	ArmRatio_ = std::clamp(ArmRatio_, 0.5f, 1.5f);

	CamHolderCollision_->GetTransform().SetLocalPosition(ArmVector_ * ArmRatio_);
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
		std::string Name = "MouseVec : " + std::to_string(Pos.x) + " | " + std::to_string(Pos.y) + " | " + std::to_string(Pos.z) + " | " + std::to_string(Pos.w);
		ImGui::Text(Name.c_str());
	}

}