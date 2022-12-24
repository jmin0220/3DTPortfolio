#include "PreCompile.h"
#include "BigShotsStage.h"
#include "VirtualPhysXLevel.h"

BigShotsStage::BigShotsStage() 
{
}

BigShotsStage::~BigShotsStage() 
{
}

void BigShotsStage::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("BigShatsStage.FBX", "CustomDefferedColor");

	PhysXSeesawGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();
}

void BigShotsStage::Update(float _DeltaTime)
{
}

void BigShotsStage::End()
{
}

void BigShotsStage::LevelStartEvent()
{
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void BigShotsStage::LevelEndEvent()
{
}

void BigShotsStage::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXSeesawGeometry_->CreatePhysXActors("BigShatsStage.FBX", _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));
}
