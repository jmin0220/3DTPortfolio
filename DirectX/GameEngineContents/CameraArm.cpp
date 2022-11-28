#include "PreCompile.h"
#include "CameraArm.h"

// ī�޶� ������ �ӵ�
float SPEED_CAM_X = 1.0f;
float SPEED_CAM_Y = 1.0f;

const float4 DEFAULT_ARMVEC(0, 4.2f, -4.5f);
const float4 DEFAULT_POSHEAD(0, 8.0f, 0);

const float4 SIZE_MENUBAR(8, 31, 0); // ���콺�� ȭ�� ����� �����ϱ� ���� ����
//const float4 SIZE_MENUBAR(0, 0, 0); // ���콺�� ȭ�� ����� �����ϱ� ���� ����

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

	// ���̷ν�����
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

	// DEBUG GUI���
	GUI = GameEngineGUI::CreateGUIWindow<CustomableGUI>("CustomableGUI", nullptr);
	GUI->SetGUIDebugFunc([=]() {GuIDebugFunc(); });
	GUI->Off();

}

void CameraArm::SetFollowCamera(std::shared_ptr<GameEngineCameraActor> _Camera, std::shared_ptr<GameEngineActor> _Character)
{
	// ī�޶� �� ���Ϳ� ĳ���͸� ����
	Camera_ = _Camera;
	
	// ī�޶���� ����ī�޶� ��� �ƴ�
	Camera_->OffFreeCameraMode();

	GetTransform().SetWorldPosition(_Character->GetTransform().GetWorldPosition());
	
	Character_ = _Character;
	//SetParent(_Character);

	// ī�޶� �� �ǹ� ����
	ArmVector_ = DEFAULT_ARMVEC * ArmRatio_;

	// ĳ���ͺ��� ���� ���� �ٶ󺻴�
	PosHead_ = DEFAULT_POSHEAD;


	// ���콺 �������� �� ȭ�� ��� ��ġ�� ����
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

	// ī�޶���� �÷��̾ ����ٴѴ�
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

	// ī�޶� Ȧ�� ��ġ ����
	PosCamHolder_ = CamHolderCollision_->GetTransform().GetWorldPosition();
	PosCharacter_ = GetTransform().GetWorldPosition();

	// ī�޶� Ȧ�� ��ġ�� ī�޶� ���󰡵���
	Camera_->GetTransform().SetWorldPosition(PosCamHolder_);
	DebugValue = PosCamHolder_;

	// ī�޶� �÷��̾ �ٶ󺸵��� �������
	CameraLookPlayer();

	// ���콺 ����/���� �Է�
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

// ���콺 Ŀ�� ȭ�� �߽����� ����
void CameraArm::GetCursurInput()
{
	// Ŀ��, ȭ�� �߽����κ��� �־����� �����̰�, �߽����� �ǵ��ư��°Ÿ� �ȿ����̴� ���
	CurMousePos_ = Camera_->GetCameraComponent()->GetMouseScreenPosition();

	float4 MouseDelta = CurMousePos_ - ScreenCenterPos_ + SIZE_MENUBAR;
	MouseMove_.x = abs(MouseDelta.x) > 0.01f ? MouseDelta.x : 0.0f;
	MouseMove_.y = abs(MouseDelta.y) > 0.01f ? MouseDelta.y : 0.0f;

	SetCursorPos(ScreenCenterPos_.ix(), ScreenCenterPos_.iy());
	CurMousePos_ = ScreenCenterPos_;
}

// �ʿ���� ����
void CameraArm::FollowCharacterPosition()
{
	GetTransform().SetWorldPosition(PosCharacter_);
}


void CameraArm::CameraLookPlayer()
{
	Camera_->GetTransform().SetWorldRotation(CamHolderCollision_->GetTransform().GetWorldRotation());

	// ī�޶� ���⺤��
	float4 Forward = Camera_->GetTransform().GetForwardVector().Normalize3DReturn();

	// ī�޶�κ��� ĳ���ͷ� ���ϴ� ���⺤��
	float4 Target = ((PosCharacter_ + PosHead_) - PosCamHolder_).Normalize3DReturn();

	// ����
	float Angle = acosf(float4::DotProduct3D(Forward, Target)) * GameEngineMath::RadianToDegree;

	Camera_->GetTransform().SetAddWorldRotation({ Angle, 0, 0 });

}

// ���콺 ���� ������
void CameraArm::HorizontalOrbitCamera()
{
	CamAxisY_->GetTransform().SetAddWorldRotation({ 0,  MouseMove_.x * SPEED_CAM_X, 0 });
}

// ���콺 ���� ������
void CameraArm::VerticalOrbitCamera()
{
	// ī�޶� ���� ���� ���� -> Clamp
	float Rot = CamAxisX_->GetTransform().GetLocalRotation().x + MouseMove_.y * SPEED_CAM_Y;
	float ClampRot = std::clamp(Rot, -30.0f, 30.0f);

	CamAxisX_->GetTransform().SetLocalRotation({ ClampRot, 0, 0 });
}

void CameraArm::ZoomInOut()
{
	// ī�޶� �� ����
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