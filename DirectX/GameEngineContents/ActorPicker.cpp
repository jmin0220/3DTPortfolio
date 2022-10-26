#include "PreCompile.h"
#include "ActorPicker.h"
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineBase/GameEngineTransform.h>


std::set<GameEngineActor*> ActorPicker::PickedActors;
GameEngineActor* ActorPicker::PickedActor = nullptr;	// ��ŷ���� �浹�� �� �տ��ִ� ����
GameEngineActor* ActorPicker::ClickedActor = nullptr;	// ��ŷ���� �浹X���� Ŭ������ �� ����

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

	if (true == GameEngineInput::GetInst()->IsDown("VK_LBUTTON"))
	{
		ClickedActor = PickedActor;
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

	float4 MouseDir = GetLevel()->GetMainCamera()->GetMouseWorldDir();

	// �̵��ӵ�
	MouseDir *= 300;

	// x�� �̵�
	ClickedActor->GetTransform().SetWorldMove({ MouseDir.x, 0, 0 });
}
