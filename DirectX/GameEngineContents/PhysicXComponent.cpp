#include "PreCompile.h"
#include "PhysicXComponent.h"

PhysicXComponent::PhysicXComponent() 
{
}

PhysicXComponent::~PhysicXComponent() 
{
}

void PhysicXComponent::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale)
{
	// �θ� ���ͷκ��� ��ġ ����
	physx::PxTransform localTm(ParentActor_->GetTransform().GetWorldPosition().x
		, ParentActor_->GetTransform().GetWorldPosition().y
		, ParentActor_->GetTransform().GetWorldPosition().z);

	// ǥ��, ���� ��
	material_ = _physics->createMaterial(0.5f, 0.5f, 0.6f);

	// �浹ü�� ����
	// �浹ü�� ũ��� ������ ũ�⸦ �����ϹǷ� ���� Renderer�� �������� �浹ü�� 2��� �����Ǿ�� ��
	//shape_ = _physics->createShape(physx::PxBoxGeometry(2.0f, 2.0f, 2.0f), *material_);

	ParentActor_->GetTransform().SetWorldScale({ 4.0f, 4.0f, 4.0f });

	// �浹ü�� ����
	//dynamic_ = _physics->createRigidDynamic(physx::PxTransform(0.0f, 0.0f, 0.0f));
	dynamic_ = physx::PxCreateDynamic(*_physics, physx::PxTransform(0.0f, 0.0f, 0.0f), physx::PxBoxGeometry(_GeoMetryScale), *material_, 10.0f);
	//dynamic_->attachShape(*shape_);

	// �ӽ� ��
	// ȸ����
	dynamic_->setAngularDamping(0.5f);
	// �ӵ�
	dynamic_->setLinearVelocity(physx::PxVec3(0.0f, 0.0f, -200.0f));

	// Scene�� ���� �߰�
	_Scene->addActor(*dynamic_);
}

void PhysicXComponent::Start()
{
	// �θ��� ���� ����
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetParent());
}

void PhysicXComponent::Update(float _DeltaTime)
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

void PhysicXComponent::End()
{
}
