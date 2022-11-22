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

	// 부모 액터로부터 위치 생성
	physx::PxTransform localTm(physx::PxVec3(ParentActor_.lock()->GetTransform().GetWorldPosition().x
		, ParentActor_.lock()->GetTransform().GetWorldPosition().y
		, ParentActor_.lock()->GetTransform().GetWorldPosition().z),
		physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w));

	// 마찰, 탄성계수
	material_ = _physics->createMaterial(0.0f, 0.0f, 0.0f);

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
		MsgBox("매쉬를 불러와 피직스X 충돌체를 만드는데 실패했습니다 TriMesh");
	}


	physx::PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
	physx::PxTriangleMesh* TriangleMesh = _physics->createTriangleMesh(readBuffer);
	shape_ = _physics->createShape(physx::PxTriangleMeshGeometry(TriangleMesh), *material_);


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

	// 충돌체의 종류
	rigidStatic_ = _physics->createRigidStatic(localTm);

	rigidStatic_->attachShape(*shape_);

	// Scene에 액터 추가
	_Scene->addActor(*rigidStatic_);
}

void PhysXTriMeshGeometryComponent::Start()
{
	// 부모의 정보의 저장
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetRoot());
}

void PhysXTriMeshGeometryComponent::Update(float _DeltaTime)
{
	// TODO::static은 변경되지 않으니 Update할 필요가 없을지도
	// PhysX Actor의 상태에 맞춰서 부모의 Transform정보를 갱신
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
