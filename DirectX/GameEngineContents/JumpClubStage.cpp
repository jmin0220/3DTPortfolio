#include "PreCompile.h"
#include "JumpClubStage.h"
#include "VirtualPhysXLevel.h"

JumpClubStage::JumpClubStage() 
{
}

JumpClubStage::~JumpClubStage() 
{
}

void JumpClubStage::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("JumpClubStage.FBX", "CustomDefferedColor");

	PhysXTriMeshGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();
}

void JumpClubStage::Update(float _DeltaTime)
{
}

void JumpClubStage::End()
{
}

void JumpClubStage::LevelStartEvent()
{
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void JumpClubStage::LevelEndEvent()
{
}

void JumpClubStage::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();

	PhysXTriMeshGeometry_->SetPhysxMaterial(FLOOR_STATICFRICTION, FLOOR_DYNAMICFRICTION, FLOOR_RESISTUTION);
	PhysXTriMeshGeometry_->SetObjectGround();

	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	//PhysXTriMeshGeometry_->SetPhysxMaterial(FLOOR_STATICFRICTION, FLOOR_DYNAMICFRICTION, FLOOR_RESISTUTION);
	PhysXTriMeshGeometry_->CreatePhysXActors("JumpClubStage.fbx", _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));
}
