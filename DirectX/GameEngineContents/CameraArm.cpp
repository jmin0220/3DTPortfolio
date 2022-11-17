#include "PreCompile.h"
#include "CameraArm.h"

// ī�޶� ������ �ӵ�
float SPEED_CAM_X = 0.5f;
float SPEED_CAM_Y = 0.5f;

const float4 DEFAULT_ARMVEC(0, 1.2f, -1.5f);
const float4 DEFAULT_POSHEAD(0, 2.0f, 0);

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
	SetParent(_Character);

	Camera_ = _Camera;
	if (true == Camera_->IsFreeCameraMode())
	{
		Camera_->FreeCameraModeOnOff();
	}

	// ī�޶� �� �ǹ� ����
	ArmVector_ = DEFAULT_ARMVEC * ArmRatio_;

	// ĳ���ͺ��� ���� ���� �ٶ󺻴�
	PosHead_ = DEFAULT_POSHEAD;


}

void CameraArm::SetArmLength(float _Depth, float _Height)
{
	ArmVector_ = float4(0, _Height, _Depth);
}

void CameraArm::Update(float _DeltaTime)
{
	if (false == GameEngineWindow::GetInst()->IsMouseCurApp())
	{
		return;
	}

	if (nullptr == Camera_ )
	{
		return;
	}

	if (true == Camera_->IsFreeCameraMode())
	{
		return;
	}

	// ���콺 �Է� ����
	CurMouseInput_ = Camera_->GetCameraComponent()->GetMouseScreenPosition();
	MouseMove_ = CurMouseInput_ - PrevMouseInput_;

	// ī�޶� Ȧ�� ��ġ ����
	PosCamHolder_ = CamHolderCollision_->GetTransform().GetWorldPosition();
	PosCharacter_ = GetTransform().GetWorldPosition();

	// ī�޶� Ȧ�� ��ġ�� ī�޶� ���󰡵���
	Camera_->GetTransform().SetWorldPosition(PosCamHolder_);

	// ī�޶� �÷��̾ �ٶ󺸵��� �������
	CameraLookPlayer();

	// ���콺 ����/���� �Է�
	VerticalOrbitCamera();
	HorizontalOrbitCamera();

	// ���콺 �Է� �ʱ�ȭ
	PrevMouseInput_ = CurMouseInput_;

	ZoomInOut();
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

	DebugValue = Angle;
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

	// ī�޶� ���� ���� ����
	float Rot = CamAxisX_->GetTransform().GetLocalRotation().x + MouseMove_.y * SPEED_CAM_Y;
	float ClampRot = std::clamp(Rot, -40.0f, 40.0f);

	CamAxisX_->GetTransform().SetLocalRotation({ ClampRot, 0, 0 });
}

void CameraArm::ZoomInOut()
{
	// ī�޶� �� ����
	int Wheel = GameEngineInput::GetInst()->GetMouseWheel();

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
		std::string Name = "TargetDegree : " + std::to_string(Pos.x) + " | " + std::to_string(Pos.y) + " | " + std::to_string(Pos.z) + " | " + std::to_string(Pos.w);
		ImGui::Text(Name.c_str());
	}

}