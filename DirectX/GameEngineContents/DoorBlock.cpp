#include "PreCompile.h"
#include "DoorBlock.h"
#include "VirtualPhysXLevel.h"

DoorBlock::DoorBlock() 
{
}

DoorBlock::~DoorBlock() 
{
}

void DoorBlock::Start()
{

	PhysXBoxGeometry_ = CreateComponent<PhysXBoxGeometryComponent>();

	// 2. 메쉬세팅 Static renderer
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("DoorBlock.FBX", "Texture");
}

void DoorBlock::Update(float _DeltaTime)
{


}

void DoorBlock::LevelStartEvent()
{
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
		static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());
}

void DoorBlock::OffEvent()
{
}

void DoorBlock::OnEvent()
{
}

void DoorBlock::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXBoxGeometry_->CreatePhysXActors(_Scene, _physics, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));

	PhysXBoxGeometry_->SetPositionSetFromParentFlag(true);
}
