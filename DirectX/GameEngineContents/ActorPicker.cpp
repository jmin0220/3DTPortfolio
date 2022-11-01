#include "PreCompile.h"
#include "ActorPicker.h"
#include "PickableActor.h"
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineBase/GameEngineTransform.h>

#include "AxisActor.h"


std::set<GameEngineActor*> ActorPicker::PickedActors;
GameEngineActor* ActorPicker::PickedActor = nullptr;	// ��ŷ���� �浹�� �� �տ��ִ� ����
GameEngineActor* ActorPicker::ClickedActor = nullptr;	// ��ŷ���� �浹X���� Ŭ������ �� ����
GameEngineActor* ActorPicker::SelectedActor = nullptr;	// ��ŷ���� �浹X���� ����Ŭ�� ����

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

	
	// ī�޶�� ������ ��ġ 
	CamPos = GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition();
	GetTransform().SetWorldPosition(CamPos);

	// ��ŷ�� �ݸ���(Ray) ȸ��
	float4 MouseVectorFromCam = GetLevel()->GetMainCamera()->GetMouseWorldPosition();
	float4 PickerAngle = float4(MouseVectorFromCam.y * GameEngineMath::RadianToDegree * -1,
		MouseVectorFromCam.x * GameEngineMath::RadianToDegree,
		MouseVectorFromCam.z * GameEngineMath::RadianToDegree);

	float4 Rot = GetLevel()->GetMainCameraActor()->GetTransform().GetLocalRotation();
	GetTransform().SetWorldRotation(Rot + PickerAngle);

	// Ray�� �浹Ȯ��
	SelectPickedActor();

	// ��ŷ ������Ʈ Ŭ��üũ
	ClickCheck();

	// ���콺 ����
	ClickControl();
}

void ActorPicker::End()
{
}

// �������� ���͵��� ���� ������ ��
// ī�޶󺸴ٴ� �տ� �־����
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
	// ȭ�� ���̸� ��ŷX
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

// x�� �̵��� ������ �����غ�
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

	 //�̵��ӵ�
	MouseDir *= 300;

	// x�� �̵�
	AxisActor* Axis = dynamic_cast<AxisActor*>(ClickedActor->GetParent());
	if (nullptr != Axis)
	{
		Axis->GetTransform().SetWorldMove({ MouseDir.x, 0, 0 });
	}
	
	// Box �̵� Test
	ClickedActor->GetTransform().SetWorldMove({ MouseDir.x, 0, 0 });

}
