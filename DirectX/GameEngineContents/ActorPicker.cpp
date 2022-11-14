#include "PreCompile.h"
#include "ActorPicker.h"
#include "PickableActor.h"
#include "GlobalValues.h"
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineBase/GameEngineTransform.h>

#include "AxisActor.h"


std::set<std::shared_ptr<GameEngineActor>> ActorPicker::PickedActors;
std::weak_ptr<GameEngineActor> ActorPicker::PickedActor;	// ��ŷ���� �浹�� �� �տ��ִ� ����
std::weak_ptr<GameEngineActor> ActorPicker::ClickedActor;	// ��ŷ���� �浹X���� Ŭ������ �� ����
std::weak_ptr<GameEngineActor> ActorPicker::SelectedActor;	// ��ŷ���� �浹X���� ����Ŭ�� ����
std::weak_ptr<GameEngineActor> ActorPicker::CurActor;       // axis���� ������ ���� ���õ� ����

ActorPicker::ActorPicker() 
{
}

ActorPicker::~ActorPicker() 
{
}

void ActorPicker::Start()
{
	Collision_Ray = CreateComponent<GameEngineCollision>();
	Collision_Ray.lock()->GetTransform().SetWorldScale({0.1f, 0.1f, 200000});
	Collision_Ray.lock()->ChangeOrder(CollisionGroup::Ray);
	Collision_Ray.lock()->SetDebugSetting(CollisionType::CT_OBB, float4(1.0f, 0, 0, 0.2f));

	Axis = GetLevel()->CreateActor<AxisActor>();
	Axis.lock()->SetPosition();
	Axis.lock()->Off();
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
	if (CurActor.lock() != nullptr)
	{
		if (std::dynamic_pointer_cast<PickableActor>(ClickedActor.lock())->GetCurPickingCol().lock() != nullptr)
		{
			if (std::dynamic_pointer_cast<PickableActor>(ClickedActor.lock())->GetCurPickingCol().lock()->GetOrder() == static_cast<int>(CollisionGroup::Axis))
			{
				ClickAxisControl();
			}
			else if (std::dynamic_pointer_cast<PickableActor>(ClickedActor.lock())->GetCurPickingCol().lock()->GetOrder() == static_cast<int>(CollisionGroup::Picking))
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
		PickedActor.lock() = nullptr;
		return;
	}

	std::weak_ptr<GameEngineActor> Nearest;
	for (std::weak_ptr<GameEngineActor> Actor : PickedActors)
	{
		if (nullptr == Nearest.lock())
		{
			Nearest = Actor;
		}
		else
		{
			Nearest = Nearest.lock()->GetTransform().GetWorldPosition().z < Actor.lock()->GetTransform().GetWorldPosition().z ? Nearest : Actor;
		}
	}
	PickedActor = Nearest;
	Nearest.lock() = nullptr;



}

void ActorPicker::UnSelect()
{
	//��������Դµ� PickedActor�� nullptr �̶�°� ó���� �ƹ��͵� Ŭ�������ʾҰų� ����� Ŭ���ߴٴ� ��
	if (PickedActor.lock() == nullptr)
	{
		//SelectedActor�� null�̸� ó�������̰ų� ����� �̹� Ŭ���� ����
		if (SelectedActor.lock() == nullptr)
		{
			return;
		}

		std::dynamic_pointer_cast<PickableActor>(SelectedActor.lock())->GetPickingCol().lock()->On();
		Axis.lock()->Off();
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


		if (ClickedActor.lock() != nullptr)
		{
			if (std::dynamic_pointer_cast<PickableActor>(ClickedActor.lock())->GetPickingCol().lock()->GetOrder() == static_cast<int>(CollisionGroup::Axis))
			{
				return;
			}
		}


		CurActor = ClickedActor;

		if (nullptr != ClickedActor.lock())
		{
			if (SelectedActor.lock() != nullptr)
			{

				std::dynamic_pointer_cast<PickableActor>(SelectedActor.lock())->GetPickingCol().lock()->On();


			}




			SelectedActor = ClickedActor;
		}


		return;
	}

	if (true == GameEngineInput::GetInst()->IsFree("VK_LBUTTON"))
	{

		ClickedActor.lock() = nullptr;
		
		return;
	}

}

void ActorPicker::ClickPickableActor()
{
	PickableActor::GetCurPickingCol().lock()->Off();
	Axis.lock()->GetTransform().SetWorldPosition(PickableActor::GetCurPickingCol().lock()->GetActor()->GetTransform().GetWorldPosition());
	Axis.lock()->On();
}

// x�� �̵��� ������ �����غ�
void ActorPicker::ClickAxisControl()
{
	if (nullptr == ClickedActor.lock())
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


	std::shared_ptr<PickableActor> AxisVector = std::dynamic_pointer_cast<PickableActor>(ClickedActor.lock());

	if (AxisVector->GetAxisDir().x >= 1.0f)
	{
		std::dynamic_pointer_cast<AxisActor>(ClickedActor.lock()->GetParent())->GetTransform().SetWorldMove({ MouseDir.x,0,0 });
		CurActor.lock()->GetTransform().SetWorldMove({ MouseDir.x,0,0 });

	}
	if (AxisVector->GetAxisDir().y >= 1.0f)
	{
		std::dynamic_pointer_cast<AxisActor>(ClickedActor.lock()->GetParent())->GetTransform().SetWorldMove({ 0,MouseDir.y,0 });
		CurActor.lock()->GetTransform().SetWorldMove({ 0,MouseDir.y,0 });

	}
	//�ϴ��� �ѓ������θ�
	//TODO :: ī�޶� ȸ�����⿡ ���� z�� ����
	if (AxisVector->GetAxisDir().z >= 1.0f)
	{
		std::dynamic_pointer_cast<AxisActor>(ClickedActor.lock()->GetParent())->GetTransform().SetWorldMove({ 0,0,MouseDir.x });
		CurActor.lock()->GetTransform().SetWorldMove({ 0,0,MouseDir.x });

	}

}
