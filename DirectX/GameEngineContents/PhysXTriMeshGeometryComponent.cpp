#include "PreCompile.h"
#include "PhysXTriMeshGeometryComponent.h"

PhysXTriMeshGeometryComponent::PhysXTriMeshGeometryComponent() 
{
}

PhysXTriMeshGeometryComponent::~PhysXTriMeshGeometryComponent() 
{
}

void PhysXTriMeshGeometryComponent::CreatePhysXActors(const std::string& _MeshName, physx::PxScene* _Scene, physx::PxPhysics* _physics, 
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

	// �浹ü�� ����
	// �浹ü�� ũ��� ������ ũ�⸦ �����ϹǷ� ���� Renderer�� �������� �浹ü�� 2��� �����Ǿ�� ��
	// TODO::�θ� ������ RenderUnit���κ��� Mesh�� Scale �� WorldScale�� ������ ����� ������Ʈ���� Scale�� �����ؾ���.
	//shape_ = _physics->createShape();

	const physx::PxVec3 convexVerts[] = { physx::PxVec3(0,1,0),physx::PxVec3(1,0,0),physx::PxVec3(-1,0,0),physx::PxVec3(0,0,1),
	physx::PxVec3(0,0,-1) };

	physx::PxTriangleMeshDesc meshDesc;
	meshDesc.points.count = VertexVec.size();
	meshDesc.points.stride = sizeof(physx::PxVec3);
	meshDesc.points.data = &VertexVec[0];

	unsigned int IndexVecSize = IndexVec.size() / 3;

	meshDesc.triangles.count = IndexVecSize;
	meshDesc.triangles.stride = 3 * sizeof(physx::PxU32);
	meshDesc.triangles.data = &IndexVec[0];

	physx::PxDefaultMemoryOutputStream writeBuffer;
	physx::PxTriangleMeshCookingResult::Enum* result = nullptr;
	bool status = _cooking->cookTriangleMesh(meshDesc, writeBuffer, result);
	if (!status)
	{
		MsgBox("�Ž��� �ҷ��� ������X �浹ü�� ����µ� �����߽��ϴ� TriMesh");
	}


	physx::PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
	physx::PxTriangleMesh* TriangleMesh = _physics->createTriangleMesh(readBuffer);
	shape_ = _physics->createShape(physx::PxTriangleMeshGeometry(TriangleMesh), *material_);


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

void PhysXTriMeshGeometryComponent::Start()
{
	// �θ��� ������ ����
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetRoot());
}

void PhysXTriMeshGeometryComponent::Update(float _DeltaTime)
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

void PhysXTriMeshGeometryComponent::CustomFBXLoad(const std::string& _MeshName)
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
	std::vector<unsigned int> Indexes = RenderUnitInfo->Indexs[0];

	size_t VertexSize = MeshVertexs.size();
	size_t IndexSize = Indexes.size();

	VertexVec.reserve(VertexSize + 1);
	IndexVec.reserve(IndexSize +1);
	for (size_t i = 0; i < VertexSize; i++)
	{
		VertexVec.push_back(physx::PxVec3(MeshVertexs[i].POSITION.x, MeshVertexs[i].POSITION.y, MeshVertexs[i].POSITION.z));
	}

	for (size_t i = 0; i < IndexSize; i++)
	{
		IndexVec.push_back(physx::PxU32(Indexes[i]));
	}


	//Mesh->UserLoad();
}
