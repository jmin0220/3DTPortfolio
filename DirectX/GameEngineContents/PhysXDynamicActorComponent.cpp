#include "PreCompile.h"
#include "PhysXDynamicActorComponent.h"

PhysXDynamicActorComponent::PhysXDynamicActorComponent() 
{
}

PhysXDynamicActorComponent::~PhysXDynamicActorComponent() 
{
}

void PhysXDynamicActorComponent::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot)
{
	float4 tmpQuat = _GeoMetryRot.DegreeRotationToQuaternionReturn();

	// �θ� ���ͷκ��� ��ġ ����
	physx::PxTransform localTm(physx::PxVec3(ParentActor_.lock()->GetTransform().GetWorldPosition().x
		, ParentActor_.lock()->GetTransform().GetWorldPosition().y
		, ParentActor_.lock()->GetTransform().GetWorldPosition().z),
		physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w));

	// ����, ź�����
	material_ = _physics->createMaterial(0.5f, 0.5f, 0.001f);

	// TODO::������ ������ ��� ���� �ڵ带 ���
	//float4 tmpMagnification = { SIZE_MAGNIFICATION_RATIO };
	//physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * tmpMagnification.x * 0.5f, 
	//							   _GeoMetryScale.y * tmpMagnification.y * 0.5f, 
	//							   _GeoMetryScale.z * tmpMagnification.z * 0.5f);

	GeoMetryScale_ = _GeoMetryScale;

	physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * 0.5f,
		_GeoMetryScale.y * 0.5f,
		_GeoMetryScale.z * 0.5f);

	//// �浹ü�� ����
	dynamic_ = _physics->createRigidDynamic(localTm);

	// �浹ü�� ����
	// �浹ü�� ũ��� ������ ũ�⸦ �����ϹǷ� ���� Renderer�� �������� �浹ü�� 2��� �����Ǿ�� ��
	// TODO::�θ� ������ RenderUnit���κ��� Mesh�� Scale �� WorldScale�� ������ ����� ������Ʈ���� Scale�� �����ؾ���.
	//shape_ = _physics->createShape(physx::PxBoxGeometry(tmpGeoMetryScale), *material_);
	shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.x * 0.5f * 0.25f), *material_);
	shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.x * 0.5f * 0.25f, 0)));
	shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.x * 0.5f * 0.25f), *material_);
	shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.x * 0.5f * 0.75f, 0)));
	shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.x * 0.5f * 0.25f), *material_);
	shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.x * 0.5f * 1.25f, 0)));
	shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxSphereGeometry(_GeoMetryScale.x * 0.5f * 0.25f), *material_);
	shape_->setLocalPose(physx::PxTransform(physx::PxVec3(0, _GeoMetryScale.x * 0.5f * 1.75f, 0)));



	dynamic_->attachShape(*shape_);

	// RigidDynamic�� �е��� ����
	physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 10.0f);

	// Scene�� ���� �߰�
	_Scene->addActor(*dynamic_);
}

void PhysXDynamicActorComponent::Start()
{
	// �θ��� ������ ����
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetParent());
}

void PhysXDynamicActorComponent::Update(float _DeltaTime)
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


	dynamic_->setLinearVelocity(physx::PxVec3(0.01f * _DeltaTime, 0.0f, 0.0f));
	// physx::PxRigidBodyExt::addForceAtLocalPos(*dynamic_, physx::PxVec3(0.01f, 0.01f, 0.0f), physx::PxVec3(GeoMetryScale_.x * 0.5f, 0, 0), physx::PxForceMode::eIMPULSE);
}