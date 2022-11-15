#include "PreCompile.h"
#include "ActorPicker.h"
#include "PickableActor.h"
#include "GlobalValues.h"
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineBase/GameEngineTransform.h>

#include "AxisActor.h"
#include "ActorAxis.h"


std::set<std::shared_ptr<PickableActor>> ActorPicker::PickedActors;
std::shared_ptr<PickableActor> ActorPicker::PickedActor;	// ��ŷ���� �浹�� �� �տ��ִ� ����
std::shared_ptr<PickableActor> ActorPicker::ClickedActor;	// ��ŷ���� �浹X���� Ŭ������ �� ����
std::shared_ptr<PickableActor> ActorPicker::SelectedActor;	// ��ŷ���� �浹X���� ����Ŭ�� ����
//std::weak_ptr<GameEngineActor> ActorPicker::CurActor;       // axis���� ������ ���� ���õ� ����

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
	
	// ī�޶�� ������ ��ġ 
	CamPos_ = GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition() + GetLevel()->GetMainCameraActor()->GetTransform().GetForwardVector() * 20.0f;
	GetTransform().SetWorldPosition(CamPos_);

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

// �������� ���͵��� ���� ������ ��
// ī�޶󺸴ٴ� �տ� �־����
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
	//��������Դµ� PickedActor�� nullptr �̶�°� ó���� �ƹ��͵� Ŭ�������ʾҰų� ����� Ŭ���ߴٴ� ��
	if (PickedActor == nullptr)
	{
		//SelectedActor�� null�̸� ó�������̰ų� ����� �̹� Ŭ���� ����
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
	// ȭ�� ���̸� ��ŷX
	float4 MouseScreenPos = GetLevel()->GetMainCamera()->GetMouseScreenPosition();
	float ScaleX = GameEngineWindow::GetScale().x;
	float ScaleY = GameEngineWindow::GetScale().y;
	if ( ScaleX < MouseScreenPos.x || ScaleY < MouseScreenPos.y)
	{
		return;
	}

	// Ŭ������
	if (true == GameEngineInput::GetInst()->IsDown("VK_LBUTTON"))
	{
		// ����� Ŭ�� Axis�� Ŭ��
		if (nullptr == PickedActor)
		{
			Axis_->Off();
			SelectedActor.reset();
		}
		// ���͸� Ŭ����
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

// x�� �̵��� ������ �����غ�
void ActorPicker::ClickAxisControl()
{
	if (nullptr == ClickedActor)
	{
		return;
	}


	float4 MouseDir = GetLevel()->GetMainCamera()->GetMouseWorldDir();

	float CamZ = 0;

	// �̵��ӵ� : TODO �̰� ���ľߵ�
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
	////�ϴ��� �ѓ������θ�
	//if (AxisVector->GetAxisDir().z >= 1.0f)
	//{
	//	std::dynamic_pointer_cast<AxisActor>(ClickedActor.lock()->GetParent())->GetTransform().SetWorldMove({ 0,0,MouseDir.x });
	//	CurActor.lock()->GetTransform().SetWorldMove({ 0,0,MouseDir.x });

	//}

}
