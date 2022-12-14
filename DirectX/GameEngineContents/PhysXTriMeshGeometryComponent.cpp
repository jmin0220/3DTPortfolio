#include "PreCompile.h"
#include "PhysXTriMeshGeometryComponent.h"

PhysXTriMeshGeometryComponent::PhysXTriMeshGeometryComponent() 
{
}

PhysXTriMeshGeometryComponent::~PhysXTriMeshGeometryComponent() 
{
}

//_MeshName(�ҷ��� �Ž��� �̸�), _Scene, _Physics, _Cooking (InitPhysics ���� �ҷ��� ��), _InverseIndex(Index�� �������� ������ ���� bool��), 
// _GeoMetryScale(�����ϰ�), _GeoMetryRot(�����̼ǰ�)
void PhysXTriMeshGeometryComponent::CreatePhysXActors(const std::string& _MeshName, physx::PxScene* _Scene, physx::PxPhysics* _physics, 
	physx::PxCooking* _cooking, bool _InverseIndex, physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot)
{
	CustomFBXLoad(_MeshName, _InverseIndex);
	float4 tmpQuat = _GeoMetryRot.DegreeRotationToQuaternionReturn();

	// �θ� ���ͷκ��� ��ġ ����
	physx::PxTransform localTm(physx::PxVec3(ParentActor_.lock()->GetTransform().GetWorldPosition().x
		, ParentActor_.lock()->GetTransform().GetWorldPosition().y
		, ParentActor_.lock()->GetTransform().GetWorldPosition().z),
		physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w));

	// ����, ź�����
	//material_ = _physics->createMaterial(staticfriction_, dynamicfriction_, resitution_);
	material_ = _physics->createMaterial(0.7f, 1.5f, resitution_);


	// �浹ü�� ����
	rigidStatic_ = _physics->createRigidStatic(localTm);
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

	int RenderinfoCount = Mesh->GetRenderUnitCount();

	for (size_t i = 0; i < RenderinfoCount; i++)
	{
		//Vertex�� ���� Desc�� �־��ش�
		//Size, ������ ����Ʈ������, �������� ���۰�
		physx::PxTriangleMeshDesc meshDesc;
		meshDesc.points.count = VertexVec[i].size();
		meshDesc.points.stride = sizeof(physx::PxVec3);
		meshDesc.points.data = &VertexVec[i][0];

		unsigned int IndexVecSize = IndexVec[i].size() / 3;

		//Index�� ���� Desc�� �־��ش�
		//Triangle�� ����(Index�� 1/3����), ������ ����Ʈ������, �������� ���۰�
		meshDesc.triangles.count = IndexVecSize;
		meshDesc.triangles.stride = 3 * sizeof(physx::PxU32);
		meshDesc.triangles.data = &IndexVec[i][0];

		physx::PxDefaultMemoryOutputStream writeBuffer;
		physx::PxTriangleMeshCookingResult::Enum* result = nullptr;
		bool status = _cooking->cookTriangleMesh(meshDesc, writeBuffer, result);
		if (!status)
		{
			MsgBox("�Ž��� �ҷ��� ������X �浹ü�� ����µ� �����߽��ϴ� TriMesh");
		}


		physx::PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
		physx::PxTriangleMesh* TriangleMesh = _physics->createTriangleMesh(readBuffer);
		//createExclusiveShapefh RigidStatic�� Shape�� �־��ش�.
		shape_ = physx::PxRigidActorExt::createExclusiveShape(*rigidStatic_, physx::PxTriangleMeshGeometry(TriangleMesh), *material_);

		//�ǹ� ����
		physx::PxVec3 Pivot(DynamicPivot_.x, DynamicPivot_.y, DynamicPivot_.z);
		shape_->setLocalPose(physx::PxTransform(Pivot));

		// invalid parameter : PxShape::setFlag(s): triangle mesh and heightfield triggers are not supported!
		// Triangle������ Trigger�� ����� �� ����
		//shape_->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);

		// �浹���� �ݹ��� ���� ����
		shape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::Ground)
															, static_cast<physx::PxU32>(PhysXFilterGroup::Player), 0, 0));

		//�ݹ��ǹ� ����
		shape_->setLocalPose(physx::PxTransform(Pivot));

			
	}
	


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

	//rigidStatic_->attachShape(*shape_);

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
	if (true == PositionSetFromParentFlag_)
	{
		float4 tmpQuat = ParentActor_.lock()->GetTransform().GetWorldRotation().DegreeRotationToQuaternionReturn();

		physx::PxTransform tmpPxTransform(ParentActor_.lock()->GetTransform().GetWorldPosition().x,
			ParentActor_.lock()->GetTransform().GetWorldPosition().y,
			ParentActor_.lock()->GetTransform().GetWorldPosition().z, physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w));

		// �θ��� Transform������ �������� PhysX Actor�� Ʈ�������� ����
		rigidStatic_->setGlobalPose(tmpPxTransform);
		// TODO::ȸ���� ó���ؾ���. DegreeToQuat
	}
}

void PhysXTriMeshGeometryComponent::CustomFBXLoad(const std::string& _MeshName, bool _InverseIndex)
{

	GameEngineDirectory Dir;

	Dir.MoveParentToExitsChildDirectory(DIR_RESOURCES);
	Dir.Move(DIR_RESOURCES);
	Dir.Move(DIR_PHYSXMESH);
	std::string Path = Dir.PlusFilePath(_MeshName);

	//�Ž��� ã�´�
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_MeshName);
	if (FindFBXMesh == nullptr)
	{
		//���� �Žð� ������� �ε��Ѵ�
		Mesh = GameEngineFBXMesh::Load(Path);
	}
	else
	{
		//���� �Žð� �����Ұ��� �״�� ���´�.
		Mesh = FindFBXMesh;
	}
	
	//��������ī��Ʈ�� �ҷ��� ���Ϳ� reserve�� �Ѵ�
	int RenderinfoCount = Mesh->GetRenderUnitCount();

	VertexVec.reserve(RenderinfoCount + 1);
	IndexVec.reserve(RenderinfoCount + 1);

	for (size_t i = 0; i < RenderinfoCount; i++)
	{
		//i ��° GetRenderUnit���� RenderUnitInfo�� Get�Ѵ�
		FbxRenderUnitInfo* RenderUnitInfo = Mesh->GetRenderUnit(i);

		std::vector<GameEngineVertex> MeshVertexs = RenderUnitInfo->Vertexs;
		std::vector<unsigned int> Indexes = RenderUnitInfo->Indexs[0];

		int VertexSize = MeshVertexs.size();
		int IndexSize = Indexes.size();
		std::vector<physx::PxVec3> InstVertVec;
		std::vector<unsigned int> InstIndexVec;
		//Vertex�� Index ������ VertexVec, IndexVec�� �����Ѵ�
		for (size_t j = 0; j < VertexSize; j++)
		{
			InstVertVec.push_back(physx::PxVec3(MeshVertexs[j].POSITION.x, MeshVertexs[j].POSITION.y, MeshVertexs[j].POSITION.z));
		}

		if (_InverseIndex == true)
		{
			for (size_t j = 0; j < IndexSize; j++)
			{
				InstIndexVec.push_back(physx::PxU32(Indexes[j]));
			}
		}
		if (_InverseIndex == false)
		{
			for (int j = IndexSize - 1; j >= 0; --j)
			{
				InstIndexVec.push_back(physx::PxU32(Indexes[j]));
			}
		}


		VertexVec.push_back(InstVertVec);
		IndexVec.push_back(InstIndexVec);
	}
	

	//Mesh->UserLoad();
}
