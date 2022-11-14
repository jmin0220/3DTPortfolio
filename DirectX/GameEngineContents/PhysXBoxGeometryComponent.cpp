#include "PreCompile.h"
#include "PhysXBoxGeometryComponent.h"

PhysXBoxGeometryComponent::PhysXBoxGeometryComponent() 
{
}

PhysXBoxGeometryComponent::~PhysXBoxGeometryComponent() 
{
}

void PhysXBoxGeometryComponent::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale)
{
	// �θ� ���ͷκ��� ��ġ ����
	physx::PxTransform localTm(ParentActor_.lock()->GetTransform().GetWorldPosition().x
		, ParentActor_.lock()->GetTransform().GetWorldPosition().y
		, ParentActor_.lock()->GetTransform().GetWorldPosition().z);

	// ����, ź�����
	material_ = _physics->createMaterial(0.5f, 0.5f, 0.6f);

	// TODO::������ ������ ��� ���� �ڵ带 ���
	//float4 tmpMagnification = { SIZE_MAGNIFICATION_RATIO };
	//physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * tmpMagnification.x * 0.5f, 
	//							   _GeoMetryScale.y * tmpMagnification.y * 0.5f, 
	//							   _GeoMetryScale.z * tmpMagnification.z * 0.5f);

	physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * 0.5f,
								   _GeoMetryScale.y * 0.5f,
								   _GeoMetryScale.z * 0.5f);

	// �浹ü�� ����
	// �浹ü�� ũ��� ������ ũ�⸦ �����ϹǷ� ���� Renderer�� �������� �浹ü�� 2��� �����Ǿ�� ��
	// TODO::�θ� ������ RenderUnit���κ��� Mesh�� Scale �� WorldScale�� ������ ����� ������Ʈ���� Scale�� �����ؾ���.
	shape_ = _physics->createShape(physx::PxBoxGeometry(tmpGeoMetryScale), *material_);

	// �浹ü�� ����
	dynamic_ = _physics->createRigidDynamic(localTm);
	dynamic_->attachShape(*shape_);
	// �߷��� ������� �ʵ���
	// TODO::RigidStatic���� �����ؾ�
	dynamic_->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);

	// RigidDynamic�� �е��� ����
	physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 10.0f);

	// Scene�� ���� �߰�
	_Scene->addActor(*dynamic_);
}

void PhysXBoxGeometryComponent::Start()
{
	// �θ��� ������ ����
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetParent());
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

	ParentActor_.lock()->GetTransform().SetWorldPosition(tmpWorldPos);
	ParentActor_.lock()->GetTransform().SetWorldRotation(tmpWorldRot);
}
