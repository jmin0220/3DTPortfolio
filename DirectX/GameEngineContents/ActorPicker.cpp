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
//std::weak_ptr<GameEngineActor> ActorPicker::CurActor;       // axis축을 제외한 현재 선택된 액터

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
	Axis_->SetParent(shared_from_this());
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
	ClickCheck();

	// 마우스 조작
	//현재 클릭한 액터의 콜리전타입 확인
	//if (CurActor.lock() != nullptr)
	//{
	//	if (std::dynamic_pointer_cast<PickableActor>(ClickedActor.lock())->GetCurPickingCol().lock() != nullptr)
	//	{
	//		if (std::dynamic_pointer_cast<PickableActor>(ClickedActor.lock())->GetCurPickingCol().lock()->GetOrder() == static_cast<int>(CollisionGroup::Axis))
	//		{
	//			ClickAxisControl();
	//		}
	//		else if (std::dynamic_pointer_cast<PickableActor>(ClickedActor.lock())->GetCurPickingCol().lock()->GetOrder() == static_cast<int>(CollisionGroup::Picking))
	//		{
	//			ClickPickableActor();
	//		}
	//	}
	//}
	//else
	//{
	//	UnSelect();
	//}


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

		//std::dynamic_pointer_cast<PickableActor>(SelectedActor.lock())->GetPickingCol().lock()->On();
		//Axis.lock()->Off();
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

	// 클릭했음
	if (true == GameEngineInput::GetInst()->IsDown("VK_LBUTTON"))
	{
		// 허공을 클릭 Axis를 클릭
		if (nullptr == PickedActor)
		{
			Axis_->Off();
			SelectedActor.reset();
		}
		// 엑터를 클릭함
		else
		{
			ClickedActor = PickedActor;
			SelectedActor = ClickedActor;
			Axis_->On();
		}
		


		//ClickedActor = PickedActor;

		//if (ClickedActor.lock() != nullptr)
		//{
		//	//if (std::dynamic_pointer_cast<PickableActor>(ClickedActor.lock())->GetPickingCol().lock()->GetOrder() == static_cast<int>(CollisionGroup::Axis))
		//	//{
		//	//	return;
		//	//}
		//}


		////CurActor = ClickedActor;

		//if (nullptr != ClickedActor.lock())
		//{
		//	if (SelectedActor.lock() != nullptr)
		//	{

		//		//std::dynamic_pointer_cast<PickableActor>(SelectedActor.lock())->GetPickingCol().lock()->On();


		//	}




		//	SelectedActor = ClickedActor;
		//}


		return;
	}

	if (true == GameEngineInput::GetInst()->IsUp("VK_LBUTTON"))
	{
		ClickedActor.reset();
		
		return;
	}

}

void ActorPicker::ClickPickableActor()
{
	//PickableActor::GetCurPickingCol().lock()->Off();
	//Axis.lock()->GetTransform().SetWorldPosition(PickableActor::GetCurPickingCol().lock()->GetActor()->GetTransform().GetWorldPosition());
	//Axis.lock()->On();
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

	// 이동속도 : TODO 이거 고쳐야됨
	if (GetLevel()->GetMainCamera()->GetTransform().GetWorldPosition().z <= 0)
	{
		CamZ = GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition().z * -1;
	}
	else
	{
		CamZ = GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition().z;
	}

	MouseDir *= CamZ;


	std::shared_ptr<PickableActor> AxisVector = std::dynamic_pointer_cast<PickableActor>(ClickedActor);

	//if (AxisVector->GetAxisDir().x >= 1.0f)
	//{
	//	std::dynamic_pointer_cast<AxisActor>(ClickedActor.lock()->GetParent())->GetTransform().SetWorldMove({ MouseDir.x,0,0 });
	//	CurActor.lock()->GetTransform().SetWorldMove({ MouseDir.x,0,0 });

	//}
	//if (AxisVector->GetAxisDir().y >= 1.0f)
	//{
	//	std::dynamic_pointer_cast<AxisActor>(ClickedActor.lock()->GetParent())->GetTransform().SetWorldMove({ 0,MouseDir.y,0 });
	//	CurActor.lock()->GetTransform().SetWorldMove({ 0,MouseDir.y,0 });

	//}
	////일단은 한뱡향으로만
	//if (AxisVector->GetAxisDir().z >= 1.0f)
	//{
	//	std::dynamic_pointer_cast<AxisActor>(ClickedActor.lock()->GetParent())->GetTransform().SetWorldMove({ 0,0,MouseDir.x });
	//	CurActor.lock()->GetTransform().SetWorldMove({ 0,0,MouseDir.x });

	//}

}
