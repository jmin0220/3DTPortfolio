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
//	Renderer_->SetFBXMesh("HoopsRamp.FBX", "Texture");


	PhysXTriGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();
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
	MeshBoundScale = MeshBoundScale * GetTransform().GetWorldScale();

	PhysXTriGeometry_->SetPhysxMaterial(FLOOR_STATICFRICTION, 1.5f, FLOOR_RESISTUTION);
	PhysXTriGeometry_->CreatePhysXActors(Name_, _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z), 0.0f);
	PhysXTriGeometry_->SetPositionSetFromParentFlag(true);
}
