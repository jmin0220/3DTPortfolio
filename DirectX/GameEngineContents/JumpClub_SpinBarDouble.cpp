#include "PreCompile.h"
#include "JumpClub_SpinBarDouble.h"
#include "VirtualPhysXLevel.h"

JumpClub_SpinBarDouble::JumpClub_SpinBarDouble() 
{
}

JumpClub_SpinBarDouble::~JumpClub_SpinBarDouble() 
{
}

void JumpClub_SpinBarDouble::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("SpinBarDouble.FBX", "Texture");

	PhysXTriMeshDynamicGeometry_ = CreateComponent<PhysXTriMeshDynamicGeometryComponent>();
}

void JumpClub_SpinBarDouble::Update(float _DeltaTime)
{
}

void JumpClub_SpinBarDouble::End()
{
}

void JumpClub_SpinBarDouble::LevelStartEvent()
{
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void JumpClub_SpinBarDouble::LevelEndEvent()
{
}

void JumpClub_SpinBarDouble::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXTriMeshDynamicGeometry_->CreatePhysXActors("SpinBarDouble.fbx", _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));
}
