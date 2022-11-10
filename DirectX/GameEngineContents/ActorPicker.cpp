#include "PreCompile.h"
#include "ActorPicker.h"
#include "PickableActor.h"
#include "GlobalValues.h"
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineBase/GameEngineTransform.h>

#include "AxisActor.h"


std::set<std::shared_ptr<GameEngineActor>> ActorPicker::PickedActors;
std::shared_ptr<GameEngineActor> ActorPicker::PickedActor = nullptr;	// ��ŷ���� �浹�� �� �տ��ִ� ����
std::shared_ptr<GameEngineActor> ActorPicker::ClickedActor = nullptr;	// ��ŷ���� �浹X���� Ŭ������ �� ����
std::shared_ptr<GameEngineActor> ActorPicker::SelectedActor = nullptr;	// ��ŷ���� �浹X���� ����Ŭ�� ����
std::shared_ptr<GameEngineActor> ActorPicker::CurActor = nullptr;       // axis���� ������ ���� ���õ� ����

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
	
	// ī�޶�� ������ ��ġ 
	CamPos = GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition() + GetLevel()->GetMainCameraActor()->GetTransform().GetForwardVector() * 20.0f;
	GetTransform().SetWorldPosition(CamPos);

	// ��ŷ�� �ݸ���(Ray) ȸ��
	// -1 �� 1 ���̰� �ƴ϶� ȭ�� ������ ���� �޶����°� ���������
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
	//���� Ŭ���� ������ �ݸ���Ÿ�� Ȯ��
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

// �������� ���͵��� ���� ������ ��
// ī�޶󺸴ٴ� �տ� �־����
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
	//��������Դµ� PickedActor�� nullptr �̶�°� ó���� �ƹ��͵� Ŭ�������ʾҰų� ����� Ŭ���ߴٴ� ��
	if (PickedActor == nullptr)
	{
		//SelectedActor�� null�̸� ó�������̰ų� ����� �̹� Ŭ���� ����
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
	// ȭ�� ���̸� ��ŷX
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

// x�� �̵��� ������ �����غ�
void ActorPicker::ClickAxisControl()
{
	if (nullptr == ClickedActor)
	{
		return;
	}


	float4 MouseDir = GetLevel()->GetMainCamera()->GetMouseWorldDir();

	float CamZ = 0;
	 //�̵��ӵ�
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
	//�ϴ��� �ѓ������θ�
	//TODO :: ī�޶� ȸ�����⿡ ���� z�� ����
	if (AxisVector->GetAxisDir().z >= 1.0f)
	{
		dynamic_cast<AxisActor*>(ClickedActor->GetParent())->GetTransform().SetWorldMove({ 0,0,MouseDir.x });
		CurActor->GetTransform().SetWorldMove({ 0,0,MouseDir.x });

	}

}
