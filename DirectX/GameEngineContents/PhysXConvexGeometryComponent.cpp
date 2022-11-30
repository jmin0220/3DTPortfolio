#include "PreCompile.h"
#include "PhysXConvexGeometryComponent.h"

PhysXConvexGeometryComponent::PhysXConvexGeometryComponent() 
{
}

PhysXConvexGeometryComponent::~PhysXConvexGeometryComponent() 
{
}

void PhysXConvexGeometryComponent::CreatePhysXActors(const std::string& _MeshName, physx::PxScene* _Scene, physx::PxPhysics* _physics, 
	physx::PxCooking* _cooking, physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot)
{
	CustomFBXLoad(_MeshName);
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

	const physx::PxVec3 convexVerts[] = { physx::PxVec3(0,1,0),physx::PxVec3(1,0,0),physx::PxVec3(-1,0,0),physx::PxVec3(0,0,1),
	physx::PxVec3(0,0,-1) };

	physx::PxConvexMeshDesc convexDesc;
	convexDesc.points.count = VertexVec.size();
	convexDesc.points.stride = sizeof(physx::PxVec3);
	convexDesc.points.data = &VertexVec[0];
	convexDesc.flags = physx::PxConvexFlag::eCOMPUTE_CONVEX;

	physx::PxDefaultMemoryOutputStream buf;
	physx::PxConvexMeshCookingResult::Enum result;
	if (!_cooking->cookConvexMesh(convexDesc, buf, &result))
	{
		MsgBox("�Ž��� �ҷ��� ������X �浿ü�� ����µ� �����߽��ϴ�");
	}
	physx::PxDefaultMemoryInputData input(buf.getData(), buf.getSize());
	physx::PxConvexMesh* convexMesh = _physics->createConvexMesh(input);

	// �浹ü�� ����
	rigidStatic_ = _physics->createRigidStatic(localTm);

	// �浹ü�� ����
	// �浹ü�� ũ��� ������ ũ�⸦ �����ϹǷ� ���� Renderer�� �������� �浹ü�� 2��� �����Ǿ�� ��
	shape_ = physx::PxRigidActorExt::createExclusiveShape(*rigidStatic_, physx::PxConvexMeshGeometry(convexMesh), *material_);

	shape_->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);

	//createExclusiveShapefh RigidStatic�� Shape�� �־��ش�.
	// Scene�� ���� �߰�
	_Scene->addActor(*rigidStatic_);
}

void PhysXConvexGeometryComponent::Start()
{
	// �θ��� ������ ����
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetRoot());
}

void PhysXConvexGeometryComponent::Update(float _DeltaTime)
{
}

void PhysXConvexGeometryComponent::CustomFBXLoad(const std::string& _MeshName)
{
	GameEngineDirectory Dir;

	Dir.MoveParentToExitsChildDirectory(DIR_RESOURCES);
	Dir.Move(DIR_RESOURCES);
	Dir.Move(DIR_PHYSXMESH);
	std::string Path = Dir.PlusFilePath(_MeshName);

	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_MeshName);
	if (FindFBXMesh == nullptr)
	{
		Mesh = GameEngineFBXMesh::Load(Path);
	}
	else
	{
		Mesh = FindFBXMesh;
	}

	FbxRenderUnitInfo* RenderUnitInfo = Mesh->GetRenderUnit(0);

	std::vector<GameEngineVertex> MeshVertexs = RenderUnitInfo->Vertexs;

	size_t VertexSize = MeshVertexs.size();

	VertexVec.reserve(VertexSize + 1);

	for (size_t i = 0; i < VertexSize; i++)
	{
		VertexVec.push_back(physx::PxVec3(MeshVertexs[i].POSITION.x, MeshVertexs[i].POSITION.y, MeshVertexs[i].POSITION.z));
	}

}
