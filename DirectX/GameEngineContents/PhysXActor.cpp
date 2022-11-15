#include "PreCompile.h"
#include "PhysXActor.h"
#include "VirtualPhysXLevel.h"

PhysXActor::PhysXActor() 
{
}

PhysXActor::~PhysXActor() 
{
}

void PhysXActor::Start()
{

}

void PhysXActor::LevelStartEvent()
{
	// 1. 사용할 PhysX컴포넌트를 Create
	PhysXBoxGeometry_ = CreateComponent<PhysXBoxGeometryComponent>();

	// 2. 메쉬세팅 Static renderer
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("floor.FBX", "Texture");

	// 3. 현재 Actor의 포지션을 설정
	this->GetTransform().SetWorldPosition({ 0.0f });

	// 4. CreatePhysXActors를 호출하여 PhysX 객체를 생성
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
					  static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());

}

void PhysXActor::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics)
{
	// 5. 사용할 컴포넌트의 CreatePhysXActors함수를 호출
	// Component의 종류에 따라 함수의 매개변수가 달라질 수 있음.

	// Tip..3번째 매개변수인 GeometryScale은 액터가 가질 물리강체의 크기
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXBoxGeometry_->CreatePhysXActors(_Scene, _physics, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));
}