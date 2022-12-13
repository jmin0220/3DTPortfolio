#include "PreCompile.h"
#include "PhysXConvexDynamicComponent.h"

PhysXConvexDynamicComponent::PhysXConvexDynamicComponent() 
{
}

PhysXConvexDynamicComponent::~PhysXConvexDynamicComponent() 
{
}



void PhysXConvexDynamicComponent::CreatePhysXActors(const std::string& _MeshName, physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxCooking* _cooking, bool _InverseIndex, physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot ,bool _Gravity)
{
	CustomFBXLoad(_MeshName);
	float4 tmpQuat = _GeoMetryRot.DegreeRotationToQuaternionReturn();

	physics_ = _physics;
	scene_ = _Scene;

	// 시소 위치 고정
	SeesawPos_ = physx::PxVec3(ParentActor_.lock()->GetTransform().GetWorldPosition().x
		, ParentActor_.lock()->GetTransform().GetWorldPosition().y
		, ParentActor_.lock()->GetTransform().GetWorldPosition().z);

	// 부모 액터로부터 위치 생성
	physx::PxTransform localTm(SeesawPos_,
		physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w));

	// 마찰, 탄성계수
	//material_ = _physics->createMaterial(0.0f, 0.0f, 0.0f);	

	material_ = _physics->createMaterial(staticfriction_, dynamicfriction_, resitution_);

	// TODO::배율을 적용할 경우 이쪽 코드를 사용
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
		MsgBox("매쉬를 불러와 피직스X 충동체를 만드는데 실패했습니다");
	}
	physx::PxDefaultMemoryInputData input(buf.getData(), buf.getSize());
	physx::PxConvexMesh* convexMesh = _physics->createConvexMesh(input);

	// 충돌체의 종류
	dynamic_ = _physics->createRigidDynamic(localTm);
	//중력 flag // true시 중력받지않음
	dynamic_->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, _Gravity);
	// 충돌체의 형태
	// 충돌체의 크기는 절반의 크기를 설정하므로 실제 Renderer의 스케일은 충돌체의 2배로 설정되어야 함
	shape_ = physx::PxRigidActorExt::createExclusiveShape(*dynamic_, physx::PxConvexMeshGeometry(convexMesh), *material_);

	//피벗 설정
	physx::PxVec3 Pivot(DynamicPivot_.x, DynamicPivot_.y, DynamicPivot_.z);
	shape_->setLocalPose(physx::PxTransform(Pivot));

	// 밀도 설정
	physx::PxRigidBodyExt::updateMassAndInertia(*dynamic_, 10.0f);

	shape_->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, true);

	// 축을 Lock 걸어놓음
	dynamic_->setAngularDamping(physx::PxReal(0.1f));

	// Scene에 액터 추가
	_Scene->addActor(*dynamic_);

	//// 시소를 받칠 발판 생성
	//physx::PxRigidStatic* PlaneStatic = _physics->createRigidStatic(physx::PxTransform(physx::PxVec3(0.0f, -15.0f, 0.0f)));
	//physx::PxRigidActorExt::createExclusiveShape(*PlaneStatic, physx::PxBoxGeometry(physx::PxVec3(30.0f, 0.5f, 3.0f)), *material_);

	//// Scene에 액터 추가
	//_Scene->addActor(*PlaneStatic);
}

void PhysXConvexDynamicComponent::AddForce(float4 _Force)
{
	dynamic_->addForce(physx::PxVec3(_Force.x, _Force.y, _Force.z), physx::PxForceMode::eIMPULSE);
}

void PhysXConvexDynamicComponent::AddAngularVelocity(float4 _Velocity)
{
	dynamic_->setAngularVelocity(physx::PxVec3(_Velocity.x, _Velocity.y, _Velocity.z));
}

void PhysXConvexDynamicComponent::Start()
{
	// 부모의 정보의 저장
	ParentActor_ = std::dynamic_pointer_cast<GameEngineActor>(GetRoot());
}

void PhysXConvexDynamicComponent::Update(float _DeltaTime)
{
	if (PositionSetFromParentFlag_ == true)
	{
		float4 tmpQuat = ParentActor_.lock()->GetTransform().GetWorldRotation().DegreeRotationToQuaternionReturn();

		physx::PxTransform tmpPxTransform(ParentActor_.lock()->GetTransform().GetWorldPosition().x,
			ParentActor_.lock()->GetTransform().GetWorldPosition().y,
			ParentActor_.lock()->GetTransform().GetWorldPosition().z, physx::PxQuat(tmpQuat.x, tmpQuat.y, tmpQuat.z, tmpQuat.w));

		// 부모의 Transform정보를 바탕으로 PhysX Actor의 트랜스폼을 갱신
		dynamic_->setGlobalPose(tmpPxTransform);
	}
	else
	{
		// PhysX Actor의 상태에 맞춰서 부모의 Transform정보를 갱신
		float4 tmpWorldPos = { dynamic_->getGlobalPose().p.x
		,dynamic_->getGlobalPose().p.y
		, dynamic_->getGlobalPose().p.z };

		float4 EulerRot = PhysXCommonFunc::GetQuaternionEulerAngles(dynamic_->getGlobalPose().q) * GameEngineMath::RadianToDegree;

		ParentActor_.lock()->GetTransform().SetWorldRotation(float4{ EulerRot.x, EulerRot.y, EulerRot.z });

		ParentActor_.lock()->GetTransform().SetWorldPosition(tmpWorldPos);
	}



}

void PhysXConvexDynamicComponent::CustomFBXLoad(const std::string& _MeshName)
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
