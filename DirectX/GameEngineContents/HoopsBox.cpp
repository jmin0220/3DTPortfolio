#include "PreCompile.h"
#include "VirtualPhysXLevel.h"
#include "HoopsBox.h"

HoopsBox::HoopsBox() 
{
}

HoopsBox::~HoopsBox() 
{
}

void HoopsBox::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	//Renderer_->SetFBXMesh("HoopsBox.FBX", "Texture");


	PhysXTriGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();
	//PhysXBoxGeometry_ = CreateComponent<PhysXBoxGeometryComponent>();

}

void HoopsBox::Update(float _DeltaTime)
{

}

void HoopsBox::LevelStartEvent()
{
	float4 Rot = GetTransform().GetLocalRotation();
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void HoopsBox::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	MeshBoundScale = MeshBoundScale * GetTransform().GetWorldScale();
	PhysXTriGeometry_->SetPhysxMaterial(FLOOR_STATICFRICTION, 3.0f, FLOOR_RESISTUTION);
	PhysXTriGeometry_->CreatePhysXActors(Name_, _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z), 0.0f);
	PhysXTriGeometry_->SetPositionSetFromParentFlag(true);

	//float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	//MeshBoundScale = MeshBoundScale * GetTransform().GetWorldScale();
	//PhysXBoxGeometry_->CreatePhysXActors(_Scene, _physics, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z), 0.0f);
	//PhysXBoxGeometry_->SetPhysxMaterial(FLOOR_STATICFRICTION, FLOOR_DYNAMICFRICTION, FLOOR_RESISTUTION);
	////PhysXTriGeometry_->SetPositionSetFromParentFlag(true);
}
