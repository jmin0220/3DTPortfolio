#include "PreCompile.h"
#include "PhysXBoxGeometryComponent.h"

PhysXBoxGeometryComponent::PhysXBoxGeometryComponent() 
{
}

PhysXBoxGeometryComponent::~PhysXBoxGeometryComponent() 
{
}

void PhysXBoxGeometryComponent::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	// �θ� ���ͷκ��� ��ġ ����
	physx::PxTransform localTm(ParentActor_->GetTransform().GetWorldPosition().x
		, ParentActor_->GetTransform().GetWorldPosition().y
		, ParentActor_->GetTransform().GetWorldPosition().z);

	// ����, ź�����
	material_ = _physics->createMaterial(0.5f, 0.5f, 0.6f);

	// �浹ü�� ����
	// �浹ü�� ũ��� ������ ũ�⸦ �����ϹǷ� ���� Renderer�� �������� �浹ü�� 2��� �����Ǿ�� ��
	// TODO::�θ� ������ RenderUnit���κ��� Mesh�� Scale �� WorldScale�� ������ ����� ������Ʈ���� Scale�� �����ؾ���.
	shape_ = _physics->createShape(physx::PxBoxGeometry(2.0f, 2.0f, 2.0f), *material_);

	// �浹ü�� ����
	dynamic_ = _physics->createRigidDynamic(localTm);
	dynamic_->attachShape(*shape_);

	// RigidDynamic�� �е��� ����
	physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 10.0f);

	// Scene�� ���� �߰�
	_Scene->addActor(*dynamic_);
}

void PhysXBoxGeometryComponent::Start()
{
	// �θ��� ������ ����
	ParentActor_ = static_cast<GameEngineActor*>(GetParent());
}

void PhysXBoxGeometryComponent::Update(float _DeltaTime)
{
	// PhysX Actor�� ���¿� ���缭 �θ��� Transform������ ����
	float4 tmpWorldPos = { dynamic_->getGlobalPose().p.x
	,dynamic_->getGlobalPose().p.y
	, dynamic_->getGlobalPose().p.z };

	float4 tmpWorldRot = { dynamic_->getGlobalPose().q.x
	,dynamic_->getGlobalPose().q.y
	, dynamic_->getGlobalPose().q.z };

	ParentActor_->GetTransform().SetWorldPosition(tmpWorldPos);
	ParentActor_->GetTransform().SetWorldRotation(tmpWorldRot);
}
