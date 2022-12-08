#include "PreCompile.h"
#include "HoopsScythe.h"
#include "VirtualPhysXLevel.h"

HoopsScythe::HoopsScythe() 
{
}

HoopsScythe::~HoopsScythe() 
{
}

void HoopsScythe::Start()
{
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("HoopsScythe.FBX", "Texture");

	//PhysXConvexGeometry_ = CreateComponent<PhysXConvexDynamicComponent>();
	//PhysXTriGeometry_ = CreateComponent<PhysXTriMeshGeometryComponent>();
	PhysXBoxGeometry_ = CreateComponent<PhysXBoxGeometryComponent>();
}

void HoopsScythe::Update(float _DeltaTime)
{
	GetTransform().SetLocalRotate({ 0,0,20.0f * _DeltaTime });
}

void HoopsScythe::LevelStartEvent()
{
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void HoopsScythe::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	MeshBoundScale.y *= 3;

	//PhysXConvexGeometry_->CreatePhysXActors("HoopsScythe.fbx", _Scene, _physics, Cooking,false, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z) ,0.0f , true);
	//PhysXConvexGeometry_->SetStaticFriction(FLOOR_STATICFRICTION);
	//PhysXConvexGeometry_->SetDynamicFriction(FLOOR_DYNAMICFRICTION);

	PhysXBoxGeometry_->CreatePhysXActors(_Scene, _physics, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y + 3.0f, MeshBoundScale.z));
	PhysXBoxGeometry_->SetPositionSetFromParentFlag(true);
	//PhysXTriGeometry_->CreatePhysXActors("HoopsScythe.fbx", _Scene, _physics, Cooking, false, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z), 0.0f);
}
