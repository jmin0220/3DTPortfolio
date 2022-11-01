#include "PreCompile.h"
#include "ActorPicker.h"
#include "PickableActor.h"
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineBase/GameEngineTransform.h>

#include "AxisActor.h"


std::set<GameEngineActor*> ActorPicker::PickedActors;
GameEngineActor* ActorPicker::PickedActor = nullptr;	// 피킹광선 충돌시 맨 앞에있는 엑터
GameEngineActor* ActorPicker::ClickedActor = nullptr;	// 피킹광선 충돌X여도 클릭유지 시 엑터
GameEngineActor* ActorPicker::SelectedActor = nullptr;	// 피킹광선 충돌X여도 최종클릭 엑터

ActorPicker::ActorPicker() 
{
}

ActorPicker::~ActorPicker() 
{
}

void ActorPicker::Start()
{
	Collision_Ray = CreateComponent<GameEngineCollision>();
	Collision_Ray->GetTransform().SetWorldScale({ 0.0002f, 0.0002f, 100000 });
	Collision_Ray->ChangeOrder(CollisionGroup::Ray);
	Collision_Ray->SetDebugSetting(CollisionType::CT_OBB, float4(1.0f, 0, 0, 0.2f));
}

void ActorPicker::Update(float _DeltaTime)
{
	CurMousePos = GetLevel()->GetMainCamera()->GetMouseWorldPosition();

	float4x4 ProjectionInvers = GetLevel()->GetMainCamera()->GetProjectionMatrix().InverseReturn();

	float4x4 ViewPort;
	ViewPort.ViewPort(GameEngineWindow::GetScale().x, GameEngineWindow::GetScale().y, 0, 0, 0, 1);

	CurMousePos = CurMousePos * ViewPort;
	CurMousePos /= CurMousePos.w;

	//CurMousePos = CurMousePos * ProjectionInvers;

	
	// 카메라와 동일한 위치 
	CamPos = GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition();
	GetTransform().SetWorldPosition(CamPos);

	// 피킹용 콜리전(Ray) 회전
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
	ClickControl();
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

	GameEngineActor* Nearest = nullptr;
	for (GameEngineActor* Actor : PickedActors)
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


void ActorPicker::ClickCheck()
{
	// 화면 밖이면 피킹X
	float4 MouseScreenPos = GetLevel()->GetMainCamera()->GetMouseScreenPosition();
	float ScaleX = GameEngineWindow::GetScale().ix();
	float ScaleY = GameEngineWindow::GetScale().iy();
	if ( ScaleX < MouseScreenPos.x || ScaleY < MouseScreenPos.y)
	{
		return;
	}


	if (true == GameEngineInput::GetInst()->IsDown("VK_LBUTTON"))
	{
		ClickedActor = PickedActor;
		PrevMousePos = CurMousePos;

		if (nullptr != ClickedActor)
		{
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

// x축 이동만 간단히 구현해봄
void ActorPicker::ClickControl()
{
	if (nullptr == ClickedActor)
	{
		return;
	}
	//float4 MouseDir = CurMousePos - PrevMousePos;


	//if (dynamic_cast<PickableActor*>(ClickedActor)->GetAxisDir().x == 1.0f)
	//{
	//	ClickedActor->GetTransform().SetWorldPosition({ ClickedActor->GetTransform().GetWorldPosition().x + MouseDir.x ,
	//												   ClickedActor->GetTransform().GetWorldPosition().y ,
	//												   ClickedActor->GetTransform().GetWorldPosition().z });


	//}
	//else if (dynamic_cast<PickableActor*>(ClickedActor)->GetAxisDir().y == 1.0f)
	//{
	//	ClickedActor->GetTransform().SetWorldPosition({ ClickedActor->GetTransform().GetWorldPosition().x ,
	//												   ClickedActor->GetTransform().GetWorldPosition().y + MouseDir.y,
	//												   ClickedActor->GetTransform().GetWorldPosition().z });


	//}
	//else if (dynamic_cast<PickableActor*>(ClickedActor)->GetAxisDir().z == 1.0f)
	//{
	//	ClickedActor->GetTransform().SetWorldPosition({ ClickedActor->GetTransform().GetWorldPosition().x ,
	//												   ClickedActor->GetTransform().GetWorldPosition().y ,
	//												   ClickedActor->GetTransform().GetWorldPosition().z + MouseDir.z});

	//}

	//PrevMousePos = CurMousePos;

	float4 MouseDir = GetLevel()->GetMainCamera()->GetMouseWorldDir();

	 //이동속도
	MouseDir *= 300;

	// x축 이동
	AxisActor* Axis = dynamic_cast<AxisActor*>(ClickedActor->GetParent());
	if (nullptr != Axis)
	{
		Axis->GetTransform().SetWorldMove({ MouseDir.x, 0, 0 });
	}
	
	// Box 이동 Test
	ClickedActor->GetTransform().SetWorldMove({ MouseDir.x, 0, 0 });

}
