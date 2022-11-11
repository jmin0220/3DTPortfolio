#include "PreCompile.h"
#include "PhysXActor.h"
#include "VirtualPhysXLevel.h"

PhysXActor::PhysXActor() 
{
}

PhysXActor::~PhysXActor() 
{
}

void PhysXActor::Start()
{

}

void PhysXActor::LevelStartEvent()
{
	// 1. ����� PhysX������Ʈ�� Create
	PhysXBoxGeometry_ = CreateComponent<PhysXBoxGeometryComponent>();

	// 2. ���� Actor�� �������� ����
	this->GetTransform().SetWorldPosition({ 0.0f });

	// 3. CreatePhysXActors�� ȣ���Ͽ� PhysX ��ü�� ����
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
					  static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());

}

void PhysXActor::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	// 4. ����� ������Ʈ�� CreatePhysXActors�Լ��� ȣ��
	// Component�� ������ ���� �Լ��� �Ű������� �޶��� �� ����.

	// Tip..3��° �Ű������� GeometryScale�� ���Ͱ� ���� ������ü�� ũ��
	// PhysX�� Geometry�� ������ ���� ������ ��������Ƿ�, ���� �޽��� ���� RenderUnit�� Scale�� WorldScale���� ���Ѱ��� ������ �־������.
	// TODO::RenderUnit�� Scale���� �־��ָ� �ǰ� ��������
	PhysXBoxGeometry_->CreatePhysXActors(_Scene, _physics, physx::PxVec3(10.0f, 10.0f, 10.0f));
}