#include "PreCompile.h"
#include "PhysicXStackComponent.h"

PhysicXStackComponent::PhysicXStackComponent() 
{
}

PhysicXStackComponent::~PhysicXStackComponent() 
{
	
}

void PhysicXStackComponent::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale)
{
	// �θ� ���ͷκ��� ��ġ ����
	physx::PxTransform localTm(ParentActor_->GetTransform().GetWorldPosition().x
		, ParentActor_->GetTransform().GetWorldPosition().y
		, ParentActor_->GetTransform().GetWorldPosition().z);

	// ǥ��, ���� ��
	material_ = _physics->createMaterial(0.5f, 0.5f, 0.6f);

	// �浹ü�� ����
	// �浹ü�� ũ��� ������ ũ�⸦ �����ϹǷ� ���� Renderer�� �������� �浹ü�� 2��� �����Ǿ�� ��
	shape_ = _physics->createShape(physx::PxBoxGeometry(_GeoMetryScale), *material_);

	// �浹ü�� ����
	dynamic_ = _physics->createRigidDynamic(localTm);
	dynamic_->attachShape(*shape_);
	// �߷��� ������� �ʵ���
	dynamic_->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);

	// RigidDynamic�� �е��� ����
	physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 10.0f);

	// Scene�� ���� �߰�
	_Scene->addActor(*dynamic_);
}

void PhysicXStackComponent::Start()
{
	// �θ��� ������ ����
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetParent());

	//ParentActor_ = std::static_pointer_cast<GameEngineActor>(GetParent());

	//std::string tmpStackPosition = "StackPosition >> x : " + std::to_string(ParentActor_->GetTransform().GetWorldPosition().x)
	//									   + " / y : " + std::to_string(ParentActor_->GetTransform().GetWorldPosition().y);
	//GameEngineDebug::OutPutString(tmpStackPosition);
}

void PhysicXStackComponent::Update(float _DeltaTime)
{
	// TODO::����׿� �ӽ��ڵ�
	//if (nullptr == dynamic_)
	//{
	//	return;
	//}

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

void PhysicXStackComponent::End()
{
}
