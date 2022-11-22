#include "PreCompile.h"
#include "ActorPicker.h"
#include "PickableActor.h"
#include "GlobalValues.h"
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineBase/GameEngineTransform.h>

#include "AxisActor.h"
#include "ActorAxis.h"


std::set<std::shared_ptr<PickableActor>> ActorPicker::PickedActors;
std::shared_ptr<PickableActor> ActorPicker::PickedActor;	// 피킹광선 충돌시 맨 앞에있는 엑터
std::shared_ptr<PickableActor> ActorPicker::ClickedActor;	// 피킹광선 충돌X여도 클릭유지 시 엑터
std::shared_ptr<PickableActor> ActorPicker::SelectedActor;	// 피킹광선 충돌X여도 최종클릭 엑터

ActorPicker::ActorPicker() 
{
}

ActorPicker::~ActorPicker() 
{
}

void ActorPicker::Start()
{
	Collision_Ray_ = CreateComponent<GameEngineCollision>();
	Collision_Ray_->GetTransform().SetWorldScale({0.1f, 0.1f, 200000});
	Collision_Ray_->ChangeOrder(CollisionGroup::Ray);
	Collision_Ray_->SetDebugSetting(CollisionType::CT_OBB, float4(1.0f, 0, 0, 0.2f));

	Axis_ = GetLevel()->CreateActor<ActorAxis>();
}

void ActorPicker::Update(float _DeltaTime)
{
	
	// 카메라와 동일한 위치 
	CamPos_ = GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition() + GetLevel()->GetMainCameraActor()->GetTransform().GetForwardVector() * 20.0f;
	GetTransform().SetWorldPosition(CamPos_);

	// 피킹용 콜리전(Ray) 회전
	// -1 과 1 사이가 아니라 화면 비율에 따라 달라지는거 적용안했음
	float4 MouseVectorFromCam = GetLevel()->GetMainCamera()->GetMouseWorldPosition();
	float4 PickerAngle = float4(MouseVectorFromCam.y * GameEngineMath::RadianToDegree * -1,
		MouseVectorFromCam.x * GameEngineMath::RadianToDegree,
		MouseVectorFromCam.z * GameEngineMath::RadianToDegree);

	float4 Rot = GetLevel()->GetMainCameraActor()->GetTransform().GetLocalRotation();
	GetTransform().SetWorldRotation(Rot + PickerAngle);

	// Ray와 충돌확인
	SelectPickedActor();

	// 피킹 오브젝트 클릭체크
	// 화면 밖이면 피킹X
	float4 MouseScreenPos = GetLevel()->GetMainCamera()->GetMouseScreenPosition();
	float ScaleX = GameEngineWindow::GetScale().x;
	float ScaleY = GameEngineWindow::GetScale().y;
	if (ScaleX < MouseScreenPos.x || ScaleY < MouseScreenPos.y)
	{
		ClickedActor.reset();
		return;
	}

	ClickCheck();

	ClickAxisControl();
}

void ActorPicker::End()
{
}

// 일직선상 엑터들중 가장 가까운거 고름
// 카메라보다는 앞에 있어야함
void ActorPicker::SelectPickedActor()
{
	if (0 == PickedActors.size())
	{
		PickedActor.reset();
		return;
	}

	std::shared_ptr<PickableActor> Nearest;
	for (std::shared_ptr<PickableActor> Actor : PickedActors)
	{
		if (nullptr == Nearest)
		{
			Nearest = Actor;
		}
		else
		{
			Nearest = Nearest->GetTransform().GetWorldPosition().z < Actor->GetTransform().GetWorldPosition().z ? Nearest : Actor;
		}
	}
	PickedActor = Nearest;
	Nearest.reset();

}

void ActorPicker::ClickCheck()
{
	// 클릭했음
	if (true == GameEngineInput::GetInst()->IsDown("VK_LBUTTON"))
	{
		if (nullptr == SelectedActor)
		{
			Axis_->Off();
		}

		// 허공을 클릭
		if (nullptr == PickedActor)
		{
			SelectedActor.reset();
		}
		// 엑터를 클릭함 -> 엑터/Axis 구분
		else
		{
			ClickedActor = PickedActor;
			
			// Axis클릭
			if (true == ClickedActor->IsAxis())
			{
				return;
			}
			// 새로운 엑터 클릭
			else
			{
				SelectedActor = ClickedActor;
				Axis_->On();
			}
	
		}

		return;
	}

	if (true == GameEngineInput::GetInst()->IsUp("VK_LBUTTON"))
	{
		ClickedActor.reset();
		
		return;
	}

}

void ActorPicker::ClickAxisControl()
{

	if (nullptr == ClickedActor)
	{
		return;
	}

	float4 MouseDir = GetLevel()->GetMainCamera()->GetMouseWorldDir();

	// 이동속도
	float CamZ = ClickedActor->GetTransform().GetWorldPosition().z
		- GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition().z;



	float4 MoveVec = float4::ZERO;
	bool IsFront;
	
	std::shared_ptr<PickableActor> ClickedAxis = std::dynamic_pointer_cast<PickableActor>(ClickedActor);
	if (ClickedAxis->GetMoveDir().x > 0)
	{
		IsFront = CheckFront(ClickedActor->GetTransform().GetForwardVector(),
			GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition().Normalize3DReturn());

		MoveVec.x = IsFront ? CamZ : CamZ;
		MoveVec *= MouseDir.x;
	}
	else if (ClickedAxis->GetMoveDir().y > 0)
	{
		IsFront = CheckFront(ClickedActor->GetTransform().GetForwardVector(),
			GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition().Normalize3DReturn());

		MoveVec.y = IsFront ? CamZ * -1 : CamZ;
		MoveVec *= MouseDir.y;
	}
	else if (ClickedAxis->GetMoveDir().z > 0)
	{
		float4 ActorPos = ClickedActor->GetTransform().GetWorldPosition();
		float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition();
		IsFront = CheckFront(ClickedActor->GetTransform().GetRightVector(),
			(ActorPos - CamPos).Normalize3DReturn());

		float Reverse = ActorPos.z - CamPos.z > 0 ? -1 : 1;

		MoveVec.z = IsFront ? CamZ : CamZ * -1;
		MoveVec *= MouseDir.x * Reverse;
	}

	SelectedActor->GetTransform().SetWorldMove(MoveVec);


}

// 정규화된 벡터 필요
bool ActorPicker::CheckFront(float4 _Forward, float4 _Target)
{
	// 엑터의 앞인지 뒤인지 판단(내적)
	float Angle = acosf(float4::DotProduct3D(_Forward, _Target)) * GameEngineMath::RadianToDegree;
	return Angle < 90 ? true : false;
}