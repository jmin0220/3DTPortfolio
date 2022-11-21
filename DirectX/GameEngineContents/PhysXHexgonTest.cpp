#include "PreCompile.h"
#include "PhysXHexgonTest.h"
#include "VirtualPhysXLevel.h"

PhysXHexgonTest::PhysXHexgonTest() 
{
}

PhysXHexgonTest::~PhysXHexgonTest() 
{
}

void PhysXHexgonTest::Start()
{

}

void PhysXHexgonTest::LevelStartEvent()
{
	// 1. 사용할 PhysX컴포넌트를 Create
	PhysXHexTileGeometry_ = CreateComponent<PhysXHexTileGeometryComponent>();

	// 2. 메쉬세팅 Static renderer
	Renderer_ = CreateComponent<GameEngineFBXStaticRenderer>();
	Renderer_->SetFBXMesh("HexTile.FBX", "Texture");

	// 3. 현재 Actor의 포지션을 설정
	this->GetTransform().SetWorldPosition({ 0.0f });

	// 4. CreatePhysXHexgonTests를 호출하여 PhysX 객체를 생성
	CreatePhysXActors(static_cast<VirtualPhysXLevel*>(GetLevel())->GetScene(),
					  static_cast<VirtualPhysXLevel*>(GetLevel())->GetPhysics());

}

void PhysXHexgonTest::CreatePhysXActors(physx::PxScene* _Scene, physx::PxPhysics* _physics) 
{
	// 5. 사용할 컴포넌트의 CreatePhysXHexgonTests함수를 호출
	// Component의 종류에 따라 함수의 매개변수가 달라질 수 있음.

	physx::PxCooking* Cooking = static_cast<VirtualPhysXLevel*>(GetLevel())->GetCooking();
	// Tip..3번째 매개변수인 GeometryScale은 액터가 가질 물리강체의 크기
	float4 MeshBoundScale = Renderer_->GetFBXMesh()->GetRenderUnit(0)->BoundScaleBox;
	PhysXHexTileGeometry_->CreatePhysXActors(_Scene, _physics, Cooking, physx::PxVec3(MeshBoundScale.x, MeshBoundScale.y, MeshBoundScale.z));
}

void CreateHexaTileActor(physx::PxScene* _Scene, physx::PxPhysics* _physics, physx::PxVec3 _GeoMetryScale, float4 _GeoMetryRot)
{

}