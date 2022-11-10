#include "PreCompile.h"
#include "ActorPicker.h"
#include "PickableActor.h"
#include "GlobalValues.h"
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineBase/GameEngineTransform.h>

#include "AxisActor.h"


std::set<std::shared_ptr<GameEngineActor>> ActorPicker::PickedActors;
std::shared_ptr<GameEngineActor> ActorPicker::PickedActor = nullptr;	// 피킹광선 충돌시 맨 앞에있는 엑터
std::shared_ptr<GameEngineActor> ActorPicker::ClickedActor = nullptr;	// 피킹광선 충돌X여도 클릭유지 시 엑터
std::shared_ptr<GameEngineActor> ActorPicker::SelectedActor = nullptr;	// 피킹광선 충돌X여도 최종클릭 엑터
std::shared_ptr<GameEngineActor> ActorPicker::CurActor = nullptr;       // axis축을 제외한 현재 선택된 액터

ActorPicker::ActorPicker() 
{
}

ActorPicker::~ActorPicker() 
{
}

void ActorPicker::Start()
{
	Collision_Ray = CreateComponent<GameEngineCollision>();
	Collision_Ray->GetTransform().SetWorldScale({ 0.1f, 0.1f, 200000 });
	Collision_Ray->ChangeOrder(CollisionGroup::Ray);
	Collision_Ray->SetDebugSetting(CollisionType::CT_OBB, float4(1.0f, 0, 0, 0.2f));

	Axis = GetLevel()->CreateActor<AxisActor>();
	Axis->SetPosition();
	Axis->Off();
}

void ActorPicker::Update(float _DeltaTime)
{
	
	// 카메라와 동일한 위치 
	CamPos = GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition() + GetLevel()->GetMainCameraActor()->GetTransform().GetForwardVector() * 20.0f;
	GetTransform().SetWorldPosition(CamPos);

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
	ClickCheck();

	// 마우스 조작
	//현재 클릭한 액터의 콜리전타입 확인
	if (CurActor != nullptr)
	{
		if (std::dynamic_pointer_cast<PickableActor>(ClickedActor)->GetCurPickingCol() != nullptr)
		{
			if (std::dynamic_pointer_cast<PickableActor>(ClickedActor)->GetCurPickingCol()->GetOrder() == static_cast<int>(CollisionGroup::Axis))
			{
				ClickAxisControl();
			}
			else if (std::dynamic_pointer_cast<PickableActor>(ClickedActor)->GetCurPickingCol()->GetOrder() == static_cast<int>(CollisionGroup::Picking))
			{
				ClickPickableActor();
			}
		}
	}
	else
	{
		UnSelect();
	}
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
		PickedActor = nullptr;
		return;
	}

	std::shared_ptr<GameEngineActor> Nearest = nullptr;
	for (std::shared_ptr<GameEngineActor> Actor : PickedActors)
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
	Nearest = nullptr;



}

void ActorPicker::UnSelect()
{
	//여기까지왔는데 PickedActor가 nullptr 이라는건 처음에 아무것도 클릭하지않았거나 허공을 클릭했다는 뜻
	if (PickedActor == nullptr)
	{
		//SelectedActor가 null이면 처음시작이거나 허공을 이미 클릭한 상태
		if (SelectedActor == nullptr)
		{
			return;
		}

		std::dynamic_pointer_cast<PickableActor>(SelectedActor)->GetPickingCol()->On();
		Axis->Off();
	}
}


void ActorPicker::ClickCheck()
{
	// 화면 밖이면 피킹X
	float4 MouseScreenPos = GetLevel()->GetMainCamera()->GetMouseScreenPosition();
	float ScaleX = GameEngineWindow::GetScale().x;
	float ScaleY = GameEngineWindow::GetScale().y;
	if ( ScaleX < MouseScreenPos.x || ScaleY < MouseScreenPos.y)
	{
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("VK_LBUTTON"))
	{

		ClickedActor = PickedActor;


		if (ClickedActor != nullptr)
		{
			if (std::dynamic_pointer_cast<PickableActor>(ClickedActor)->GetPickingCol()->GetOrder() == static_cast<int>(CollisionGroup::Axis))
			{
				return;
			}
		}


		CurActor = ClickedActor;

		if (nullptr != ClickedActor)
		{
			if (SelectedActor != nullptr)
			{

				std::dynamic_pointer_cast<PickableActor>(SelectedActor)->GetPickingCol()->On();


			}




			SelectedActor = ClickedActor;
		}


		return;
	}

	if (true == GameEngineInput::GetInst()->IsFree("VK_LBUTTON"))
	{

		ClickedActor = nullptr;
		
		return;
	}

}

void ActorPicker::ClickPickableActor()
{
	PickableActor::GetCurPickingCol()->Off();
	Axis->GetTransform().SetWorldPosition(PickableActor::GetCurPickingCol()->GetActor()->GetTransform().GetWorldPosition());
	Axis->On();
}

// x축 이동만 간단히 구현해봄
void ActorPicker::ClickAxisControl()
{
	if (nullptr == ClickedActor)
	{
		return;
	}


	float4 MouseDir = GetLevel()->GetMainCamera()->GetMouseWorldDir();

	float CamZ = 0;
	 //이동속도
	if (GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().z <= 0)
	{
		CamZ = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().z * -1;
	}
	else
	{
		CamZ = GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().z;
	}

	MouseDir *= CamZ;


	std::shared_ptr<PickableActor> AxisVector = std::dynamic_pointer_cast<PickableActor>(ClickedActor);

	if (AxisVector->GetAxisDir().x >= 1.0f)
	{
		dynamic_cast<AxisActor*>(ClickedActor->GetParent())->GetTransform().SetWorldMove({ MouseDir.x,0,0 });
		CurActor->GetTransform().SetWorldMove({ MouseDir.x,0,0 });

	}
	if (AxisVector->GetAxisDir().y >= 1.0f)
	{
		dynamic_cast<AxisActor*>(ClickedActor->GetParent())->GetTransform().SetWorldMove({ 0,MouseDir.y,0 });
		CurActor->GetTransform().SetWorldMove({ 0,MouseDir.y,0 });

	}
	//일단은 한뱡향으로만
	//TODO :: 카메라 회전방향에 따른 z값 변경
	if (AxisVector->GetAxisDir().z >= 1.0f)
	{
		dynamic_cast<AxisActor*>(ClickedActor->GetParent())->GetTransform().SetWorldMove({ 0,0,MouseDir.x });
		CurActor->GetTransform().SetWorldMove({ 0,0,MouseDir.x });

	}

}
