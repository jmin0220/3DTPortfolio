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
	Renderer2_ = CreateComponent<GameEngineFBXStaticRenderer>();
	//Renderer_->SetFBXMesh("HoopsBox.FBX", "Texture");


	PhysXTriGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();
	PhysXTriGeometry2_ = CreateComponent<PhysXTriMeshGeometryComponent>();
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

	PhysXTriGeometry_->SetPhysxMaterial(0, 0, 0);
	PhysXTriGeometry_->CreatePhysXActors(Name_, _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z), 0.0f);
	PhysXTriGeometry_->SetPositionSetFromParentFlag(true);



	physx::PxCooking* Cooking2 = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	float4 MeshBoundScale2 = Renderer2_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;

	PhysXTriGeometry2_->SetPhysxMaterial(FLOOR_STATICFRICTION, 1.5f, FLOOR_RESISTUTION);
	PhysXTriGeometry2_->CreatePhysXActors(Name2_, _Scene, _physics, Cooking2, true, physx::PxVec3(MeshBoundScale2.x, MeshBoundScale2.y, MeshBoundScale2.z), 0.0f);
	PhysXTriGeometry2_->SetPositionSetFromParentFlag(true);
}
