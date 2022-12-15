#include "PreCompile.h"
#include "VirtualPhysXLevel.h"
#include "HoopsRamp.h"

HoopsRamp::HoopsRamp() 
{
}

HoopsRamp::~HoopsRamp() 
{
}

void HoopsRamp::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer2_ = CreateComponent<GameEngineFBXStaticRenderer>();
//	Renderer_->SetFBXMesh("HoopsRamp.FBX", "Texture");


	PhysXTriGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();

	PhysXTriGeometry2_ = CreateComponent<PhysXTriMeshGeometryComponent>();
}

void HoopsRamp::Update(float _DeltaTime)
{
}

void HoopsRamp::LevelStartEvent()
{
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void HoopsRamp::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;

	PhysXTriGeometry_->SetPhysxMaterial(0, 0, 0);
	PhysXTriGeometry_->CreatePhysXActors(Name_, _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z), 0.0f);
	PhysXTriGeometry_->SetPositionSetFromParentFlag(true);



	physx::PxCooking* Cooking2 = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	float4 MeshBoundScale2 = Renderer2_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;

	PhysXTriGeometry2_->SetPhysxMaterial(1.5f, 1.0f, FLOOR_RESISTUTION);
	PhysXTriGeometry2_->CreatePhysXActors(Name2_, _Scene, _physics, Cooking2, true, physx::PxVec3(MeshBoundScale2.x, MeshBoundScale2.y, MeshBoundScale2.z), 0.0f);
	PhysXTriGeometry2_->SetPositionSetFromParentFlag(true);
}
