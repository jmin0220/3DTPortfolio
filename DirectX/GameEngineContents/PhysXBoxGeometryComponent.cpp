#include "PreCompile.h"
#include "PhysXBoxGeometryComponent.h"

PhysXBoxGeometryComponent::PhysXBoxGeometryComponent() 
	: PositionSetFromParentFlag_(false)
{
}

PhysXBoxGeometryComponent::~PhysXBoxGeometryComponent() 
{
}

void PhysXBoxGeometryComponent::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot)
{
	float4 tmpQuat = _GeoMetryRot.DegreeRotationToQuaternionReturn();

	// �θ� ���ͷκ��� ��ġ ����
	physx::PxTransform localTm(physx::PxVec3(ParentActor_.lock()->GetTransform().GetWorldPosition().x
		, ParentActor_.lock()->GetTransform().GetWorldPosition().y
		, ParentActor_.lock()->GetTransform().GetWorldPosition().z),
		physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w));

	// ����, ź�����
	material_ = _physics->createMaterial(0.0f, 0.0f, 0.3f);

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
	rigidDynamic_ = _physics->createRigidDynamic(localTm);
	rigidDynamic_->attachShape(*shape_);

	// �߷��� ������� �ʵ���
	// TODO::RigidStatic���� �����ؾ�
	rigidDynamic_->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);

	// RigidDynamic�� �е��� ����
	physx::PxRigidBodyExt::updateMassAndInertia(*rigidDynamic_, 10.0f);

	// Scene�� ���� �߰�
	_Scene->addActor(*rigidDynamic_);

	//// �浹ü�� ����
	//rigidStatic_ = _physics->createRigidStatic(localTm);
	//rigidStatic_->attachShape(*shape_);

	//// Scene�� ���� �߰�
	//_Scene->addActor(*rigidStatic_);
}

void PhysXBoxGeometryComponent::Start()
{
	// �θ��� ������ ����
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetRoot());
}

void PhysXBoxGeometryComponent::Update(float _DeltaTime)
{
	if (false == PositionSetFromParentFlag_)
	{
		// PhysX Actor�� ���¿� ���缭 �θ��� Transform������ ����
		float4 tmpWorldPos = { rigidDynamic_->getGlobalPose().p.x
		, rigidDynamic_->getGlobalPose().p.y
		, rigidDynamic_->getGlobalPose().p.z };

		float4 tmpWorldRot = { rigidDynamic_->getGlobalPose().q.x
		, rigidDynamic_->getGlobalPose().q.y
		, rigidDynamic_->getGlobalPose().q.z };

		ParentActor_.lock()->GetTransform().SetWorldPosition(tmpWorldPos);
		ParentActor_.lock()->GetTransform().SetWorldRotation(tmpWorldRot);
	}
	else
	{
		physx::PxTransform tmpPxTransform(ParentActor_.lock()->GetTransform().GetWorldPosition().x,
			ParentActor_.lock()->GetTransform().GetWorldPosition().y,
			ParentActor_.lock()->GetTransform().GetWorldPosition().z);

		// �θ��� Transform������ �������� PhysX Actor�� Ʈ�������� ����
		rigidDynamic_->setGlobalPose(tmpPxTransform);

		// TODO::ȸ���� ó���ؾ���. DegreeToQuat
	}
}
