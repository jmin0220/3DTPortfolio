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

	PhysXSeesawGeometry_ = CreateComponent<PhysXConvexSeesawComponent>();
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

	PhysXSeesawGeometry_->AddTorque(float4(0.0f, 0.0f, 100000.0f));
}

void BigShotsStage::LevelEndEvent()
{
}

void BigShotsStage::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	
	//PhysXSeesawGeometry_->SetPhysxMaterial(FLOOR_STATICFRICTION, FLOOR_DYNAMICFRICTION, FLOOR_RESISTUTION);
	//PhysXSeesawGeometry_->SetObjectGround();

	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXSeesawGeometry_->CreatePhysXActors("BigShatsStage.FBX", _Scene, _physics, Cooking, true, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));
}
