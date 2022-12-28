#include "PreCompile.h"
#include "HoopsStageObjects.h"
#include "VirtualPhysXLevel.h"

HoopsStageObjects::HoopsStageObjects()
{
}

HoopsStageObjects::~HoopsStageObjects()
{
}

void HoopsStageObjects::Start()
{
	// 2. 메쉬세팅 Static renderer
	FloorRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	FloorRenderer_->SetFBXMesh("HoopsFloor.FBX", "CustomDefferedColor");

	PlatformRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	PlatformRenderer_->SetFBXMesh("HoopsObjectPlatform.FBX", "CustomDefferedColor");


	WallRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	WallRenderer_->SetFBXMesh("HoopsObjectWall.FBX", "CustomDefferedColor");

	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("HoopsBackGround.FBX", "CustomDefferedColor");


	WallPhysXTriMeshGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();
	FloorPhysXTriMeshGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();
	PlatformPhysXTriMeshGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();
}

void HoopsStageObjects::Update(float _DeltaTime)
{
}

void HoopsStageObjects::End()
{
}

void HoopsStageObjects::LevelStartEvent()
{
	// 4. CreatePhysXActors를 호출하여 PhysX 객체를 생성
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void HoopsStageObjects::LevelEndEvent()
{
}

void HoopsStageObjects::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	// Tip..3번째 매개변수인 GeometryScale은 액터가 가질 물리강체의 크기
	float4 MeshBoundScale = WallRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	WallPhysXTriMeshGeometry_->CreatePhysXActors("HoopsObjectWall.fbx", _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));


	float4 MeshBoundScale2 = PlatformRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PlatformPhysXTriMeshGeometry_->SetPhysxMaterial(1.5f, 1.0f, FLOOR_RESISTUTION);
	PlatformPhysXTriMeshGeometry_->SetObjectGround();
	PlatformPhysXTriMeshGeometry_->CreatePhysXActors("HoopsObjectPlatform.fbx", _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale2.x, MeshBoundScale2.y, MeshBoundScale2.z));


	float4 MeshBoundScale3 = FloorRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	FloorPhysXTriMeshGeometry_->SetPhysxMaterial(1.5f, 1.0f, FLOOR_RESISTUTION);
	FloorPhysXTriMeshGeometry_->SetObjectGround();
	FloorPhysXTriMeshGeometry_->CreatePhysXActors("HoopsFloor.fbx", _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale3.x, MeshBoundScale3.y, MeshBoundScale3.z));
}
