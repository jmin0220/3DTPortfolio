#include "PreCompile.h"
#include "CameraArm.h"

// ī�޶� ������ �ӵ�
const float CamSpeedX = 1.0f;
const float CamSpeedY = 2.0f;

// ī�޶� Ŭ���� ����
const float ClampHeightMin = 400;
const float ClampHeightMax = 1800;

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
	CamHolderCollision_ = CreateComponent<GameEngineCollision>();
	CamHolderCollision_->GetTransform().SetWorldScale({ 50, 50, 200 });
	CamHolderCollision_->SetDebugSetting(CollisionType::CT_OBB, float4(0.0f, 0.0f, 0.8f, 0.5f));

	// DEBUG GUI���
	GUI = GameEngineGUI::CreateGUIWindow<CustomableGUI>("CustomableGUI", nullptr);
	GUI->SetGUIDebugFunc([=]() {GuIDebugFunc(); });
	GUI->Off();
}

void CameraArm::SetFollowCamera(GameEngineCameraActor* _Camera, GameEngineActor* _Character)
{
	// ī�޶� �� ���Ϳ� ĳ���͸� ����
	SetParent(_Character);

	Camera_ = _Camera;
	Character_ = _Character;
	ArmVector_ = float4(0, 600, -2000);

	CamHolderCollision_->GetTransform().SetLocalPosition(ArmVector_);
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

	// ���콺�Է�
	CurMouseInput_ = Camera_->GetCameraComponent()->GetMouseScreenPosition();
	MouseMove_ = CurMouseInput_ - PrevMouseInput_;

	PosCamHolder_ = CamHolderCollision_->GetTransform().GetWorldPosition();
	PosCharacter_ = Character_->GetTransform().GetWorldPosition();

	CameraLookPlayer();
	HorizontalOrbitCamera();
	VerticalOrbitCamera();

	// ���콺 �Է�
	PrevMouseInput_ = CurMouseInput_;
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
	Camera_->GetTransform().SetWorldPosition(PosCamHolder_);

	// ī�޶� ���⺤��
	float4 Forward = CamHolderCollision_->GetTransform().GetForwardVector().Normalize3DReturn();

	// ī�޶�κ��� ĳ���ͷ� ���ϴ� ���⺤��
	float4 Target = (PosCharacter_ - CamHolderCollision_->GetTransform().GetWorldPosition());

	// ����
	float LookDownAngle = acosf(float4::DotProduct3D(Forward, Target.Normalize3DReturn())) * GameEngineMath::RadianToDegree;

	// ī�޶� ���� ȸ����
	float Rot = GetTransform().GetLocalRotation().y;

	Camera_->GetTransform().SetWorldRotation({ LookDownAngle, Rot, 0 });

}

// ���콺 ���� ������
void CameraArm::HorizontalOrbitCamera()
{
	GetTransform().SetAddWorldRotation({ 0, MouseMove_.x * CamSpeedX, 0 });
}

// ���콺 ���� ������
void CameraArm::VerticalOrbitCamera()
{
	float DiffHeight = PosCamHolder_.y - PosCharacter_.y;
	
	if (ClampHeightMin > DiffHeight)
	{
		CamHolderCollision_->GetTransform().SetLocalMove(float4::UP);
		return;
	}

	if (ClampHeightMax < DiffHeight)
	{
		CamHolderCollision_->GetTransform().SetLocalMove(float4::DOWN);
		return;
	}
	CamHolderCollision_->GetTransform().SetLocalMove({ 0, MouseMove_.y * CamSpeedY, 0 });
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