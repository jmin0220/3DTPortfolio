#include "PreCompile.h"
#include "PhysXTriMeshGeometryComponent.h"

PhysXTriMeshGeometryComponent::PhysXTriMeshGeometryComponent()
{
}

PhysXTriMeshGeometryComponent::~PhysXTriMeshGeometryComponent()
{
}

//_MeshName(불러올 매시의 이름), _Scene, _Physics, _Cooking (InitPhysics 에서 불러온 값), _InverseIndex(Index를 역순으로 할지에 대한 bool값), 
// _GeoMetryScale(스케일값), _GeoMetryRot(로테이션값)
void PhysXTriMeshGeometryComponent::CreatePhysXActors(const std::string& _MeshName, physx::PxScene* _Scene, physx::PxPhysics* _physics,
	physx::PxCooking* _cooking, bool _InverseIndex, physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot)
{
	CustomFBXLoad(_MeshName, _InverseIndex);
	float4 tmpQuat = _GeoMetryRot.DegreeRotationToQuaternionReturn();

	// 부모 액터로부터 위치 생성
	physx::PxTransform localTm(physx::PxVec3(ParentActor_.lock()->GetTransform().GetWorldPosition().x
		, ParentActor_.lock()->GetTransform().GetWorldPosition().y
		, ParentActor_.lock()->GetTransform().GetWorldPosition().z),
		physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w));

	// 마찰, 탄성계수
	material_ = _physics->createMaterial(staticfriction_, dynamicfriction_, resitution_);
	//material_ = _physics->createMaterial(0.7f, 1.5f, resitution_);


	// 충돌체의 종류
	rigidStatic_ = _physics->createRigidStatic(localTm);
	// TODO::배율을 적용할 경우 이쪽 코드를 사용
	//float4 tmpMagnification = { SIZE_MAGNIFICATION_RATIO };
	//physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * tmpMagnification.x * 0.5f, 
	//							   _GeoMetryScale.y * tmpMagnification.y * 0.5f, 
	//							   _GeoMetryScale.z * tmpMagnification.z * 0.5f);

	physx::PxVec3 tmpGeoMetryScale(_GeoMetryScale.x * 0.5f,
		_GeoMetryScale.y * 0.5f,
		_GeoMetryScale.z * 0.5f);

	// 충돌체의 형태
	// 충돌체의 크기는 절반의 크기를 설정하므로 실제 Renderer의 스케일은 충돌체의 2배로 설정되어야 함
	// TODO::부모 액터의 RenderUnit으로부터 Mesh의 Scale 과 WorldScale의 연산의 결과를 지오메트리의 Scale로 세팅해야함.
	//shape_ = _physics->createShape();

	int RenderinfoCount = Mesh->GetRenderUnitCount();

	for (size_t i = 0; i < RenderinfoCount; i++)
	{
		//Vertex의 값을 Desc에 넣어준다
		//Size, 단위의 바이트사이즈, 데이터의 시작값
		physx::PxTriangleMeshDesc meshDesc;
		meshDesc.points.count = VertexVec[i].size();
		meshDesc.points.stride = sizeof(physx::PxVec3);
		meshDesc.points.data = &VertexVec[i][0];

		unsigned int IndexVecSize = IndexVec[i].size() / 3;

		//Index의 값을 Desc에 넣어준다
		//Triangle의 갯수(Index의 1/3개수), 단위의 바이트사이즈, 데이터의 시작값
		meshDesc.triangles.count = IndexVecSize;
		meshDesc.triangles.stride = 3 * sizeof(physx::PxU32);
		meshDesc.triangles.data = &IndexVec[i][0];

		physx::PxDefaultMemoryOutputStream writeBuffer;
		physx::PxTriangleMeshCookingResult::Enum* result = nullptr;
		bool status = _cooking->cookTriangleMesh(meshDesc, writeBuffer, result);
		if (!status)
		{
			MsgBox("매쉬를 불러와 피직스X 충돌체를 만드는데 실패했습니다 TriMesh");
		}


		physx::PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
		physx::PxTriangleMesh* TriangleMesh = _physics->createTriangleMesh(readBuffer);
		//createExclusiveShapefh RigidStatic에 Shape를 넣어준다.
		shape_ = physx::PxRigidActorExt::createExclusiveShape(*rigidStatic_, physx::PxTriangleMeshGeometry(TriangleMesh), *material_);
		//피벗 설정
		physx::PxVec3 Pivot(DynamicPivot_.x, DynamicPivot_.y, DynamicPivot_.z);
		shape_->setLocalPose(physx::PxTransform(Pivot));

		// invalid parameter : PxShape::setFlag(s): triangle mesh and heightfield triggers are not supported!
		// Triangle에서는 Trigger를 사용할 수 없음
		//shape_->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);

		// 충돌시점 콜백을 위한 세팅
		if (IsObstacle_ == true)
		{
			shape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::Obstacle)
				, static_cast<physx::PxU32>(PhysXFilterGroup::PlayerDynamic), 0, 0));
		}

		else if (IsGround_ == true)
		{
			shape_->setSimulationFilterData(physx::PxFilterData(static_cast<physx::PxU32>(PhysXFilterGroup::Ground)
				, static_cast<physx::PxU32>(PhysXFilterGroup::PlayerDynamic), 0, 0));
		}

		//콜백피벗 설정
		shape_->setLocalPose(physx::PxTransform(Pivot));


	}



	//// 충돌체의 종류
	//dynamic_ = _physics->createRigidDynamic(localTm);
	//dynamic_->attachShape(*shape_);
	//// 중력이 적용되지 않도록
	//// TODO::RigidStatic으로 변경해야
	//dynamic_->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);

	//// RigidDynamic의 밀도를 설정
	//physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 10.0f);

	//// Scene에 액터 추가
	//_Scene->addActor(*dynamic_);

	//rigidStatic_->attachShape(*shape_);

	// Scene에 액터 추가
	if (true == IsAggregateObj_)
	{
		AddActorAggregate(rigidStatic_);
	}
	else
	{
		_Scene->addActor(*rigidStatic_);
	}
}

void PhysXTriMeshGeometryComponent::Start()
{
	// 부모의 정보의 저장
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

		// 부모의 Transform정보를 바탕으로 PhysX Actor의 트랜스폼을 갱신
		rigidStatic_->setGlobalPose(tmpPxTransform);
		// TODO::회전도 처리해야함. DegreeToQuat
	}
}

void PhysXTriMeshGeometryComponent::CustomFBXLoad(const std::string& _MeshName, bool _InverseIndex)
{

	GameEngineDirectory Dir;

	Dir.MoveParentToExitsChildDirectory(DIR_RESOURCES);
	Dir.Move(DIR_RESOURCES);
	Dir.Move(DIR_PHYSXMESH);
	std::string Path = Dir.PlusFilePath(_MeshName);

	//매쉬를 찾는다
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_MeshName);
	if (FindFBXMesh == nullptr)
	{
		//만약 매시가 없을경우 로드한다
		Mesh = GameEngineFBXMesh::Load(Path);
	}
	else
	{
		//만약 매시가 존재할경우는 그대로 얻어온다.
		Mesh = FindFBXMesh;
	}

	//랜더유닛카운트를 불러와 백터에 reserve를 한다
	int RenderinfoCount = Mesh->GetRenderUnitCount();

	VertexVec.reserve(RenderinfoCount + 1);
	IndexVec.reserve(RenderinfoCount + 1);

	for (size_t i = 0; i < RenderinfoCount; i++)
	{
		//i 번째 GetRenderUnit에서 RenderUnitInfo를 Get한다
		FbxRenderUnitInfo* RenderUnitInfo = Mesh->GetRenderUnit(i);

		std::vector<GameEngineVertex> MeshVertexs = RenderUnitInfo->Vertexs;
		std::vector<unsigned int> Indexes = RenderUnitInfo->Indexs[0];

		int VertexSize = MeshVertexs.size();
		int IndexSize = Indexes.size();
		std::vector<physx::PxVec3> InstVertVec;
		std::vector<unsigned int> InstIndexVec;
		//Vertex와 Index 정보를 VertexVec, IndexVec에 저장한다
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
