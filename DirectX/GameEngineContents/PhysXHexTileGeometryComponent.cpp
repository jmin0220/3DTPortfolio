#include "PreCompile.h"
#include "PhysXHexTileGeometryComponent.h"

PhysXHexTileGeometryComponent::PhysXHexTileGeometryComponent() 
{
}

PhysXHexTileGeometryComponent::~PhysXHexTileGeometryComponent() 
{
}

void PhysXHexTileGeometryComponent::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxCooking* _cooking, physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot)
{
	float4 tmpQuat = _GeoMetryRot.DegreeRotationToQuaternionReturn();

	// �θ� ���ͷκ��� ��ġ ����
	physx::PxTransform localTm(physx::PxVec3(ParentActor_.lock()->GetTransform().GetWorldPosition().x
		, ParentActor_.lock()->GetTransform().GetWorldPosition().y
		, ParentActor_.lock()->GetTransform().GetWorldPosition().z),
		physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w));

	// ����, ź�����
	material_ = _physics->createMaterial(0.0f, 0.0f, 0.0f);

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
	//shape_ = _physics->createShape();

	const physx::PxVec3 convexVerts[] = { physx::PxVec3(0,1,0),physx::PxVec3(1,0,0),physx::PxVec3(-1,0,0),physx::PxVec3(0,0,1),
	physx::PxVec3(0,0,-1) };

	physx::PxConvexMeshDesc convexDesc;
	convexDesc.points.count = 5;
	convexDesc.points.stride = sizeof(physx::PxVec3);
	convexDesc.points.data = convexVerts;
	convexDesc.flags = physx::PxConvexFlag::eCOMPUTE_CONVEX;

	physx::PxDefaultMemoryOutputStream buf;
	physx::PxConvexMeshCookingResult::Enum result;
	if (!_cooking->cookConvexMesh(convexDesc, buf, &result))
	{
		MsgBox("�Ž��� �ҷ��� ������X �浿ü�� ����µ� �����߽��ϴ�");
	}
	physx::PxDefaultMemoryInputData input(buf.getData(), buf.getSize());
	physx::PxConvexMesh* convexMesh = _physics->createConvexMesh(input);

	shape_ = _physics->createShape(physx::PxConvexMeshGeometry(convexMesh), *material_);

	//// �浹ü�� ����
	//dynamic_ = _physics->createRigidDynamic(localTm);
	//dynamic_->attachShape(*shape_);
	//// �߷��� ������� �ʵ���
	//// TODO::RigidStatic���� �����ؾ�
	//dynamic_->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);

	//// RigidDynamic�� �е��� ����
	//physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 10.0f);

	//// Scene�� ���� �߰�
	//_Scene->addActor(*dynamic_);

	// �浹ü�� ����
	rigidStatic_ = _physics->createRigidStatic(localTm);

	rigidStatic_->attachShape(*shape_);

	// Scene�� ���� �߰�
	_Scene->addActor(*rigidStatic_);
}

void PhysXHexTileGeometryComponent::Start()
{
	// �θ��� ������ ����
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetRoot());

	//Mesh->UserLoad();
}

void PhysXHexTileGeometryComponent::Update(float _DeltaTime)
{
	// TODO::static�� ������� ������ Update�� �ʿ䰡 ��������
	// PhysX Actor�� ���¿� ���缭 �θ��� Transform������ ����
	//float4 tmpWorldPos = { rigidStatic_->getGlobalPose().p.x
	//, rigidStatic_->getGlobalPose().p.y
	//, rigidStatic_->getGlobalPose().p.z };

	//float4 tmpWorldRot = { rigidStatic_->getGlobalPose().q.x
	//, rigidStatic_->getGlobalPose().q.y
	//, rigidStatic_->getGlobalPose().q.z };

	//ParentActor_.lock()->GetTransform().SetWorldPosition(tmpWorldPos);
	//ParentActor_.lock()->GetTransform().SetWorldRotation(tmpWorldRot);
}
