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
	// 2. 메쉬세팅 Static renderer
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("TestStage01.FBX", "Texture");

	PhysXTriMeshGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();
}

void DoorDashStage::Update(float _DeltaTime)
{
}

void DoorDashStage::End()
{
}

void DoorDashStage::LevelStartEvent()
{
	// 4. CreatePhysXActors를 호출하여 PhysX 객체를 생성
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void DoorDashStage::LevelEndEvent()
{
}

void DoorDashStage::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	// Tip..3번째 매개변수인 GeometryScale은 액터가 가질 물리강체의 크기
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXTriMeshGeometry_->CreatePhysXActors("TestStage01.fbx", _Scene, _physics, Cooking, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));

}
