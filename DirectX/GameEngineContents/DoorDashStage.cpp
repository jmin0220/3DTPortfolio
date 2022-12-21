#include "PreCompile.h"
#include "DoorDashStage.h"
#include "VirtualPhysXLevel.h"

DoorDashStage::DoorDashStage() 
{
}

DoorDashStage::~DoorDashStage() 
{
}

void DoorDashStage::Start()
{
	// 2. �޽����� Static renderer
	PlatformRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	PlatformRenderer_->SetFBXMesh("DoorDashPlatformCollisionMesh.FBX", "CustomDefferedColor");

	WallRenderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	WallRenderer_->SetFBXMesh("DoorDashWallCollisionMesh.FBX", "CustomDefferedColor");

	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("DoodrDashEnv.FBX", "CustomDefferedColor");


	WallPhysXTriMeshGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();

	PlatformPhysXTriMeshGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();
}

void DoorDashStage::Update(float _DeltaTime)
{
}

void DoorDashStage::End()
{
}

void DoorDashStage::LevelStartEvent()
{
	// 4. CreatePhysXActors�� ȣ���Ͽ� PhysX ��ü�� ����
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void DoorDashStage::LevelEndEvent()
{
}

void DoorDashStage::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	// Tip..3��° �Ű������� GeometryScale�� ���Ͱ� ���� ������ü�� ũ��
	float4 MeshBoundScale = WallRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	WallPhysXTriMeshGeometry_->SetPhysxMaterial(0, 0, 0);
	WallPhysXTriMeshGeometry_->CreatePhysXActors("DoorDashWallCollisionMesh.fbx", _Scene, _physics, Cooking, false, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));


	float4 MeshBoundScale2 = PlatformRenderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PlatformPhysXTriMeshGeometry_->SetPhysxMaterial(FLOOR_STATICFRICTION, FLOOR_DYNAMICFRICTION, FLOOR_RESISTUTION);
	PlatformPhysXTriMeshGeometry_->CreatePhysXActors("DoorDashPlatformCollisionMesh.fbx", _Scene, _physics, Cooking, false, physx::PxVec3(MeshBoundScale2.x, MeshBoundScale2.y, MeshBoundScale2.z));
}
